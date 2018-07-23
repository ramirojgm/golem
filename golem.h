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

#ifndef GOLEM_H_
#define GOLEM_H_

#include <glib.h>
#include <gio/gio.h>
#include <glib-object.h>

/* Metadata */
#include "metadata/golemmodulemanager.h"
#include "metadata/golemtype.h"
#include "metadata/golemmodule.h"
#include "metadata/golemmember.h"
#include "metadata/golemfield.h"
#include "metadata/golemstruct.h"
#include "metadata/golemproperty.h"
#include "metadata/golemfunction.h"
#include "metadata/golemclass.h"

/* VM */
#include "vm/golemvm.h"

/* Error */
#include "golemerror.h"

/* Compile */
#include "compile/golemparser.h"
#include "compile/golemmodulebuilder.h"
#include "compile/golemtypebuilder.h"
#include "compile/golemscopebuilder.h"
#include "compile/golemstatement.h"
#include "compile/golemexpression.h"
#include "compile/golemcall.h"
#include "compile/golemnot.h"
#include "compile/golemnegative.h"
#include "compile/golemgsvar.h"
#include "compile/golemblock.h"
#include "compile/golemreturn.h"
#include "compile/golemconst.h"
#include "compile/golemvar.h"
#include "compile/golemconditional.h"
#include "compile/golemsymbolentry.h"
#include "compile/golemsymbolentry.h"



#endif /* GOLEM_H_ */
