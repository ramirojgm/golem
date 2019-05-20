/*
	Copyright (C) 2018 Ramiro Jose Garcia Moraga

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with the this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <golem.h>

GOLEM_DEFINE_STATEMENT(GolemAccessor,golem_accessor)

static void
golem_accessor_init(GolemAccessor * acc)
{
  acc->attribute_name = NULL;
  acc->value = NULL;
  acc->parent.base = NULL;
}

static GolemMetadata *
golem_accessor_value_type(GolemAccessor * acc,
			  GolemScopeBuilder *scope_builder,
			  GError ** error)
{
  GolemMetadata * owner_type = golem_statement_value_type(acc->parent.base,
							  scope_builder,
							  error);

  if (owner_type)
    {
      GolemMetadata * type = golem_metadata_get_attribute(owner_type,
							  acc->attribute_name);
      if (type)
	{
	  return type;
	}
      else
	{
	  g_propagate_error(error,
			    g_error_new(g_quark_from_static_string("golem"),
					0,
					"the type \"%s\" no have a attribute named \"%s\"",
					golem_metadata_get_name(owner_type),
					acc->attribute_name));
	  return NULL;
	}
    }
  else
    {
      return NULL;
    }
}


static gboolean
golem_accessor_compile(GolemAccessor * acc,
		       GolemVMBody * body,
		       GolemScopeBuilder * scope_builder,
		       GError ** error)
{
  gboolean done = TRUE;
  GolemMetadata * member = golem_accessor_value_type(acc,scope_builder,error);

  if (member)
    {
      if ((done = golem_statement_compile(acc->parent.base,
     					      body,
     					      scope_builder,
     					      error)))
	{
	  if (GOLEM_IS_ATTRIBUTE(member))
	    {
	      GolemAttribute * attr = GOLEM_ATTRIBUTE(member);
	      if (acc->value)
		{
		  if ((done = golem_statement_compile(acc->value,
						      body,
						      scope_builder,
						      error)))
		    {
		      golem_vm_body_write_op(body,GOLEM_OP_DUP);
		      golem_vm_body_write_ops(body,
					      GOLEM_OP_PSET,
					      0,
					      golem_attribute_get_offset(attr),
					      golem_attribute_get_length(attr));
		    }
		}
	      else
		{
		  golem_vm_body_write_ops(body,
					  GOLEM_OP_PGET,
					  0,
					  golem_attribute_get_offset(attr),
					  golem_attribute_get_length(attr));
		}
	    }
	}
    }
  else
    {
      golem_vm_body_write_op(body,GOLEM_OP_ZERO);
    }
  return done;
}


static gboolean
golem_accessor_parse(GolemAccessor * acc,
		      GolemParser * parser,
		      GolemExpressionLimit limit,
		      GError ** error)
{
  gboolean done = TRUE;
  if ((done = golem_parser_check(parser,".")))
    {
      acc->attribute_name = g_strdup(golem_parser_next_word(parser,TRUE));
    }
  else
    {
      g_propagate_error(error,
      g_error_new(g_quark_from_static_string("golem"),
		  0,
		  "'.' was expected"));
    }
  return done;
}

static void
golem_accessor_dispose(GolemAccessor * acc)
{
  g_free(acc->attribute_name);
  if(acc->parent.base)
    golem_statement_free(acc->parent.base);
}

static gboolean
golem_accessor_check(GolemParser * parser)
{
  gboolean result = FALSE;
  golem_parser_save_point(parser);
  result =  golem_parser_check(parser,".") &&
	    golem_parser_check_is_named(parser);
  golem_parser_restore_point(parser);
  return result;
}
