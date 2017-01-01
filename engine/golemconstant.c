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
#include <stdlib.h>
#include <stdio.h>

struct _GolemConstantPrivate
{
  GValue value;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemConstant,golem_constant,GOLEM_TYPE_EXPRESSION)

static void
_golem_constant_dispose(GObject * object)
{
  GolemConstant * self = GOLEM_CONSTANT(object);
  g_value_unset(&(self->priv->value));
  G_OBJECT_CLASS(golem_constant_parent_class)->dispose(object);
}

gboolean
_golem_constant_evaluate(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error)
{
  GolemConstant * self = GOLEM_CONSTANT(expression);
  if(!G_VALUE_HOLDS(result,G_VALUE_TYPE(&(self->priv->value))))
    {
      g_value_unset(result);
      g_value_init(result,G_VALUE_TYPE(&(self->priv->value)));
    }
  g_value_copy(&(self->priv->value),result);
  return TRUE;
}

static void
golem_constant_init(GolemConstant * self)
{
  self->priv = golem_constant_get_instance_private(self);
}

static void
golem_constant_class_init(GolemConstantClass * klass)
{
  GOLEM_EXPRESSION_CLASS(klass)->evaluate = _golem_constant_evaluate;
  G_OBJECT_CLASS(klass)->dispose = _golem_constant_dispose;
}

gboolean
golem_constant_check(GolemParser * parser)
{
  return golem_parser_check_is_const(parser);
}

GolemExpression *
golem_constant_parse(GolemParser * parser,GError ** error)
{
  GolemConstant * self = GOLEM_CONSTANT(g_object_new(GOLEM_TYPE_CONSTANT,NULL));
  if(golem_parser_check_is_number(parser))
    {
      const gchar * number = golem_parser_next_word(parser,NULL,TRUE);
      if(golem_parser_next_word_check(parser,"."))
	{
	  gchar buff[256];
	  sprintf(buff,"%s.%s",number,golem_parser_next_word(parser,NULL,TRUE));
	  if(g_str_has_suffix(number,"f"))
	    {
	      g_value_init(&(self->priv->value),G_TYPE_FLOAT);
	      g_value_set_float(&(self->priv->value),g_ascii_strtod(buff,NULL));
	    }
	  else
	    {
	      g_value_init(&(self->priv->value),G_TYPE_DOUBLE);
	      g_value_set_double(&(self->priv->value),g_ascii_strtod(buff,NULL));
	    }
	}
      else
	{
	  if(g_str_has_suffix(number,"l"))
	    {
	      g_value_init(&(self->priv->value),G_TYPE_LONG);
	      g_value_set_long(&(self->priv->value),g_ascii_strtoll(number,NULL,10));
	    }
	  else if(g_str_has_suffix(number,"b"))
	    {
	      g_value_init(&(self->priv->value),G_TYPE_CHAR);
	      g_value_set_schar(&(self->priv->value),atoi(number));
	    }
	  if(g_str_has_suffix(number,"ul"))
	    {
	      g_value_init(&(self->priv->value),G_TYPE_ULONG);
	      g_value_set_ulong(&(self->priv->value),g_ascii_strtoull(number,NULL,10));
	    }
	  else if(g_str_has_suffix(number,"ub"))
	    {
	      g_value_init(&(self->priv->value),G_TYPE_UCHAR);
	      g_value_set_uchar(&(self->priv->value),atoi(number));
	    }
	  else if(g_str_has_suffix(number,"u"))
	    {
	      g_value_init(&(self->priv->value),G_TYPE_UINT);
	      g_value_set_uint(&(self->priv->value),atoi(number));
	    }
	  else
	    {
	      g_value_init(&(self->priv->value),G_TYPE_INT);
	      g_value_set_int(&(self->priv->value),atoi(number));
	    }
	}
    }
  else if(golem_parser_check_is_hex(parser))
    {
      const gchar * hex = golem_parser_next_word(parser,NULL,TRUE);
      gint64 value = g_ascii_strtoll(hex + 2,NULL,16);
      g_value_init(&(self->priv->value),G_TYPE_UINT64);
      g_value_set_int64(&(self->priv->value),value);
    }
  else if(golem_parser_check_is_string(parser))
    {
      const gchar * str = golem_parser_next_word(parser,NULL,TRUE);
      gchar * new_str = g_strndup(str+1,g_utf8_strlen(str,-1) - 2);
      g_value_init(&(self->priv->value),G_TYPE_STRING);
      g_value_take_string(&(self->priv->value),g_strcompress(new_str));
      g_free(new_str);
    }
  return GOLEM_EXPRESSION(self);
}
