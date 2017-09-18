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

typedef union _gresult gresult;

union _gresult
{
  gint8 int_8;
  guint8 uint_8;
  gint16 int_16;
  guint16 uint_16;
  gint32 int_32;
  guint32 uint_32;
  gint64 int_64;
  guint64 uint_64;
  gfloat float_32;
  gdouble double_64;
  gpointer pointer;
  gchar * string;
};

#include "golemmap.h"
#include "golemdebugobject.h"
#include "golemparser.h"
#include "golemcontext.h"
#include "golemmodule.h"
#include "golemtypeinfo.h"
#include "golemstructinfo.h"
#include "golemruntime.h"
#include "golemregister.h"
#include "golemstatement.h"
#include "golemsharedobject.h"
#include "golemreturn.h"
#include "golemexpression.h"
#include "golemconstant.h"
#include "golemnew.h"
#include "golemdeclaration.h"
#include "goleminvoke.h"
#include "golempointerof.h"
#include "golemmember.h"
#include "golemexpressioncomplex.h"
#include "golemidentificator.h"
#include "golemblock.h"
#include "golemif.h"
#include "golemwhile.h"
#include "golemclosure.h"
#include "golembuilderclass.h"
#include "golembuilderextern.h"
#include "golembuilderfunction.h"
#include "golembuilderclosure.h"
#include "golemextends.h"
#include "golemcinvoke.h"
#include "golemclassinfo.h"
#include "golemcompiled.h"
#include "golemerror.h"
#include "golemllm.h"
#include "golemutils.h"


#define GOLEM_TYPE_IMPORT

#endif /* GOLEM_H_ */

