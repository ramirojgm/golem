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

#ifndef GOLEMERROR_H_
#define GOLEMERROR_H_

#define GOLEM_ERROR	(golem_error_get_quark())

enum {
  GOLEM_ERROR_UNKNOW,
  GOLEM_ERROR_NOT_IMPLEMENTED,
  GOLEM_ERROR_NULL_POINTER
};

const GQuark	golem_error_get_quark(void);

#endif /* GOLEMERROR_H_ */
