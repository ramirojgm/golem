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

/* VM */
#include "vm/golemvm.h"

/* Error */
#include "golemerror.h"

/* Compile */
#include "compile/golemparser.h"
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

/* Metadata */
#include "runtime/golemsource.h"
#include "runtime/golemmetadata.h"
#include "runtime/golemtype.h"
#include "runtime/golemfunctiontype.h"
#include "runtime/golemfunction.h"
#include "runtime/golemfunctionwrap.h"

#endif /* GOLEM_H_ */
