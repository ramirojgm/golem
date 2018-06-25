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

#ifndef GOLEMSOURCE_H_
#define GOLEMSOURCE_H_

#define GOLEM_TYPE_SOURCE (golem_source_get_type())
G_DECLARE_INTERFACE (GolemSource, golem_source, GOLEM, SOURCE, GObject)

typedef enum _GolemMetadataType	GolemMetadataType;
typedef guint32 GolemMetadataId;


enum _GolemMetadataType
{
  GOLEM_METADATA_FUNDAMENTAL =	1<<0,
  GOLEM_METADATA_ENUM = 	1<<1,
  GOLEM_METADATA_OBJECT_CLASS =	1<<2,
  GOLEM_METADATA_INTERFACE = 	1<<3,
  GOLEM_METADATA_STRUCT = 	1<<4,
  GOLEM_METADATA_FUNCTION = 	1<<5,
  GOLEM_METADATA_PROPERTY = 	1<<6,
  GOLEM_METADATA_TYPE = 	GOLEM_METADATA_ENUM | GOLEM_METADATA_OBJECT_CLASS | GOLEM_METADATA_INTERFACE | GOLEM_METADATA_STRUCT
};

struct _GolemSourceInterface
{
  GTypeInterface parent_iface;

  GolemMetadata * (*query)(GolemSource * );

};


#endif /* GOLEMSOURCE_H_ */
