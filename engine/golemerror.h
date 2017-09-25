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

#ifndef GOLEMERROR_H_
#define GOLEMERROR_H_

#define GOLEM_ERROR	(golem_error_quark())

typedef enum GolemError GolemError;

enum GolemError
{
  GOLEM_UNHANDLED_ERROR,
  GOLEM_NULL_POINTER_ERROR,
  GOLEM_NOT_IMPLEMENTED_ERROR,
  GOLEM_SYNTAXIS_ERROR,
  GOLEM_INVALID_CAST_ERROR,
  GOLEM_NOT_EXISTS_ERROR,
  GOLEM_ALREADY_EXISTS_ERROR,
  GOLEM_UNKNOWN_TYPE_ERROR,
  GOLEM_READ_ONLY_ERROR
};

GQuark	golem_error_quark(void);

void	golem_error_default_handle(GError * error);

void	golem_parser_error(GError ** error,GolemParser * parser,const gchar * format,...);

void	golem_runtime_error(GError ** error,enum GolemError code,const gchar * format,...);

void	golem_propage_error(GError ** error,GError * new_error);

#endif /* GOLEMERROR_H_ */
