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
#ifndef ENGINE_GOLEMDECLARATION_H_
#define ENGINE_GOLEMDECLARATION_H_

typedef struct _GolemDeclarationPrivate GolemDeclarationPrivate;

#define GOLEM_TYPE_DECLARATION (golem_declaration_get_type())
G_DECLARE_FINAL_TYPE(GolemDeclaration,golem_declaration,GOLEM,DECLARATION,GolemStatement)

struct _GolemDeclarationClass
{
  GolemStatementClass parent_class;
};

struct _GolemDeclaration
{
  GolemStatement 		parent_instance;
  GolemDeclarationPrivate * 	priv;
};

GType			golem_declaration_get_type(void);

gboolean		golem_declaration_check(GolemParser * parser);

GolemStatement *	golem_declaration_parse(GolemParser * parser,GError ** error);

#endif /* ENGINE_GOLEMDECLARATION_H_ */
