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

#ifndef GOLEM_METADATA_H_
#define GOLEM_METADATA_H_

#define GOLEM_TYPE_METADATA (golem_metadata_get_type())
G_DECLARE_DERIVABLE_TYPE (GolemMetadata,golem_metadata,GOLEM,METADATA,GObject)

struct _GolemMetadataClass
{
  GObjectClass parent_class;

  /* virtual */
  GolemMetadata * (*get_attribute)(GolemMetadata * metadata,
                                  const gchar * attr_name);

  glength8_t (*get_sizeof)(GolemMetadata * metadata);
};

GType             golem_metadata_get_type(void);

const gchar *     golem_metadata_get_name (GolemMetadata * metadata);

GolemMetadata *   golem_metadata_get_attribute (GolemMetadata * metadata,
                                                const gchar * attr_name);

glength8_t	  golem_metadata_get_sizeof (GolemMetadata * metadata);

#endif /* GOLEM_/METADATA_H_ */
