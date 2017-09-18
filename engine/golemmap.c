/*
	Copyright (C) 2017 Ramiro Jose Garcia Moraga

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


#include "golem.h"

G_DEFINE_BOXED_TYPE(GolemMap,golem_map,golem_map_ref,golem_map_unref)

typedef struct
{
  gchar * name;
  GValue  value;
}GolemMapMember;

struct _GolemMap
{
  GMutex mutex;
  gint ref_count;
  GList * members;
};

static GList *
golem_map_get_member(GolemMap * map,const gchar * name,gboolean alloc)
{
  GList * member_node = NULL;
  for(GList * iter = g_list_first(map->members);iter;iter = g_list_next(iter))
    {
      if(g_strcmp0(((GolemMapMember*)iter->data)->name,name) == 0)
	{
	  member_node = iter;
	  break;
	}
    }

  if((member_node == NULL) && (alloc))
    {
      GolemMapMember * member = g_new0(GolemMapMember,1);
      member->name = g_strdup(name);
      map->members = g_list_append(map->members,member);
      member_node = g_list_last(map->members);
    }
  return member_node;
}

static void
golem_map_free_member(GolemMapMember * member)
{
  g_free(member->name);
  g_value_unset(&member->value);
  g_free(member);
}


GolemMap *
golem_map_new()
{
  GolemMap * map = g_new0(GolemMap,1);
  g_mutex_init(&map->mutex);
  map->ref_count = 1;
  map->members = NULL;
  return map;
}

gboolean
golem_map_get(GolemMap * map,const gchar * name,GValue * dest)
{
  g_mutex_lock(&map->mutex);
  GList * member_node = golem_map_get_member(map,name,FALSE);
  if(member_node)
    {
      GValue * src = &((GolemMapMember*)member_node->data)->value;
      g_value_init(dest,G_VALUE_TYPE(src));
      g_value_copy(src,dest);
    }
  g_mutex_unlock(&map->mutex);
  return member_node != NULL;
}

void
golem_map_set(GolemMap * map,const gchar * name,const GValue * src)
{
  g_mutex_lock(&map->mutex);
  GList * member_node = golem_map_get_member(map,name,TRUE);
  GValue * dest = &((GolemMapMember*)member_node->data)->value;
  g_value_unset(dest);
  g_value_init(dest,G_VALUE_TYPE(src));
  g_value_copy(src,dest);
  g_mutex_unlock(&map->mutex);
}

void
golem_map_unset(GolemMap * map,const gchar * name)
{
  g_mutex_lock(&map->mutex);
  GList * member_node = golem_map_get_member(map,name,TRUE);
  if(member_node)
    {
      golem_map_free_member((GolemMapMember*)member_node->data);
      map->members = g_list_remove_link(map->members,member_node);
    }
  g_mutex_unlock(&map->mutex);
}

void
golem_map_reset(GolemMap * map)
{
  g_mutex_lock(&map->mutex);
  g_list_free_full(map->members,(GDestroyNotify)golem_map_free_member);
  map->members = NULL;
  g_mutex_unlock(&map->mutex);
}

GolemMap *
golem_map_ref(GolemMap * map)
{
  g_mutex_lock(&map->mutex);
  map->ref_count = map->ref_count + 1;
  g_mutex_unlock(&map->mutex);
  return map;
}

void
golem_map_unref(GolemMap * map)
{
  gboolean destroy;
  g_mutex_lock(&map->mutex);
  map->ref_count = map->ref_count - 1;
  destroy = map->ref_count <= 0;
  g_mutex_unlock(&map->mutex);
  if(destroy)
    {
      g_mutex_clear(&map->mutex);
      g_list_free_full(map->members,(GDestroyNotify)golem_map_free_member);
      g_free(map);
    }
}
