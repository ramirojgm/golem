/*
	Copyright (C) 2016 Ramiro Jose Garcia Moraga

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with the this software.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "golem.h"
#include "signal.h"

G_DEFINE_ABSTRACT_TYPE(GolemStatement,golem_statement,G_TYPE_OBJECT)

static gboolean
_golem_statement_execute_real(GolemStatement * self,GolemContext * context,GError ** error)
{
  golem_throw(error,
      GOLEM_NOT_IMPLEMENTED_ERROR,
      "not implement"
  );
  return FALSE;
}

static void
golem_statement_init(GolemStatement * self)
{
  golem_statement_get_instance_private(self);
}

static void
golem_statement_class_init(GolemStatementClass * klass)
{
  klass->execute = _golem_statement_execute_real;
}


gboolean
golem_statement_execute(GolemStatement * self,GolemContext * context,GError ** error)
{
  GolemStatementClass * klass = GOLEM_STATEMENT_GET_CLASS(self);
  return klass->execute(self,context,error);
}


GolemStatement *
golem_statement_parse(GolemParser * parser,GError ** error)
{
  if(golem_builder_class_check(parser))
      return GOLEM_STATEMENT(golem_builder_class_parse(parser,error));
  else if(golem_shared_object_check(parser))
      return GOLEM_STATEMENT(golem_shared_object_parse(parser,error));
  else if(golem_builder_extern_check(parser))
    return GOLEM_STATEMENT(golem_builder_extern_parse(parser,error));
  else if(golem_declaration_check(parser))
    return GOLEM_STATEMENT(golem_declaration_parse(parser,error));
  else if(golem_block_check(parser))
    return GOLEM_STATEMENT(golem_block_parse(parser,error));
  else if(golem_if_check(parser))
    return GOLEM_STATEMENT(golem_if_parse(parser,error));
  else if(golem_while_check(parser))
      return GOLEM_STATEMENT(golem_while_parse(parser,error));
  else
    {
      GolemExpression * exp = golem_expression_parse(parser,error);
      return GOLEM_STATEMENT(exp);
    }

}
