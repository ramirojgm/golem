/*
	Copyright (C) 2019 Ramiro Jose Garcia Moraga

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

#define GOLEM_TYPE_ATTRIBUTE (golem_attribute_get_type())
G_DECLARE_FINAL_TYPE(GolemAttribute,golem_attribute,GOLEM,ATTRIBUTE,GolemMetadata)

typedef struct _GolemAttributePrivate GolemAttributePrivate;

struct _GolemAttribute
{
  GolemMetadata parent;

  GolemAttributePrivate * priv;
};

struct _GolemAttributeClass
{
  GolemMetadataClass parent_class;
};

GType           golem_attribute_get_type(void);

GolemMetadata * golem_attribute_get_defined_type (GolemAttribute * attr);

glength16_t     golem_attribute_get_offset(GolemAttribute * attr);

glength8_t      golem_attribute_get_length(GolemAttribute * attr);

void            golem_attribute_get (GolemAttribute * attr,
                                     gpointer instance,
                                     GolemValue * dest);

void            golem_attribute_set (GolemAttribute * attr,
                                     gpointer instance,
                                     GolemValue * src);
