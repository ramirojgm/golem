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

#ifndef GOLEM_H_
#define GOLEM_H_

#include <glib.h>
#include <glib-object.h>
#include <glibconfig.h>

#include "golemdebugobject.h"
#include "golemparser.h"
#include "golemcontext.h"
#include "golemsentence.h"
#include "golemblock.h"
#include "golemfunc.h"
#include "golemclass.h"
#include "golembuilderclass.h"
#include "golembuilderextern.h"


gboolean	golem_compile_string(GolemContext * context,const gchar * script,gssize length,GError ** error);

#endif /* GOLEM_H_ */

