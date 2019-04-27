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

#include "golemenums.h"
#include "vm/golemvm.h"

/* Metadata */
#include "metadata/golemmetadata.h"
#include "metadata/golemattribute.h"
#include "metadata/golemtype.h"
#include "metadata/golemprimitive.h"
/*#include "metadata/golemmodulemanager.h"
#include "metadata/golemtype.h"
#include "metadata/golemmodule.h"
#include "metadata/golemmember.h"
#include "metadata/golemfield.h"
#include "metadata/golemstruct.h"
#include "metadata/golemproperty.h"
#include "metadata/golemfunction.h"
//#include "metadata/golemclass.h"
#include "metadata/goleminterface.h"
*/
/* Runtime */
//#include "runtime/golemcallable.h"


/* Compile */

#include "compile/golemparser.h"
#include "compile/golemscopebuilder.h"
#include "compile/golemstatement.h"
#include "compile/golemexpression.h"
#include "compile/golemblock.h"
#include "compile/golemreturn.h"
#include "compile/expr/golemconst.h"
#include "compile/expr/golemneg.h"

/*#include "compile/golemcall.h"
#include "compile/golemnot.h"

#include "compile/golemgsvar.h"



#include "compile/golemvar.h"
#include "compile/golemconditional.h"
#include "runtime/golemboundfunc.h"
#include "runtime/golemlambdafunc.h"
*/


#endif /* GOLEM_H_ */
