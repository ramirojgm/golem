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


#include "../golem.h"

typedef struct _GolemMarshalType GolemMarshalType;

struct _GolemMarshalType
{
  GType type;
  GolemMarshalInfo info;
  GolemMarshalType * next;
};


static GolemMarshalType * _golem_declared_head_marshals = NULL;
static GolemMarshalType * _golem_declared_tail_marshals = NULL;

static GMutex 		_golem_declared_mutex_marshals = G_STATIC_MUTEX_INIT;

GType
golem_declare_marshal(gboolean 		return_const,
		     GType		return_type,
		     guint8		n_arguments,
		     const GType * 	argument_types)
{
  g_mutex_lock(&_golem_declared_mutex_marshals);
  for(GolemMarshalType * marshal = _golem_declared_head_marshals;
      marshal;
      marshal = marshal->next)
    {
      if((marshal->info.return_type == return_type) &&
	  (marshal->info.return_const == return_const) &&
	  (marshal->info.n_arguments == n_arguments))
	{
	  if(memcmp(marshal->info.argument_types,
		    argument_types,
		    sizeof(GType) * n_arguments) == 0)
	    {
	      g_mutex_unlock(&_golem_declared_mutex_marshals);
	      return marshal->type;
	    }
	}
    }

  GolemMarshalType * marshal = g_new0(GolemMarshalType,1);
  gchar marshal_type_name[256] = "Symbol";
  if(return_const)
    strcat(marshal_type_name,"Const");
  strcat(marshal_type_name,"_");
  strcat(marshal_type_name,g_type_name(return_type));
  for(guint8 n_arg = 0; n_arg < n_arguments; n_arg ++)
    {
      GType argument_type = argument_types[n_arg];
      strcat(marshal_type_name,"_");
      strcat(marshal_type_name,g_type_name(argument_type));
    }

  marshal->type = g_pointer_type_register_static(marshal_type_name);
  marshal->info.return_const = return_const;
  marshal->info.return_type = return_type;
  marshal->info.n_arguments = n_arguments;
  marshal->info.argument_types = g_memdup(argument_types, sizeof(GType) * n_arguments);

  if(_golem_declared_tail_marshals)
    {
      _golem_declared_tail_marshals->next = marshal;
      _golem_declared_tail_marshals = marshal;
    }
  else
    {
      _golem_declared_head_marshals = _golem_declared_tail_marshals = marshal;
    }

  g_mutex_unlock(&_golem_declared_mutex_marshals);
  return marshal->type;
}

GolemMarshalInfo *
g_type_get_marshal_info(GType type)
{
  GolemMarshalInfo * info = NULL;
  g_mutex_lock(&_golem_declared_mutex_marshals);
  for(GolemMarshalType * marshal = _golem_declared_head_marshals;
        marshal;
        marshal = marshal->next)
    {
      if(marshal->type == type)
      {
	  info = &(marshal->info);
	  break;
      }
    }
  g_mutex_unlock(&_golem_declared_mutex_marshals);
  return info;
}
