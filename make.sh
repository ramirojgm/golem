#!/bin/bash
gcc -c engine/golemclosure.c -o engine/golemclosure.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemcompiled.c -o engine/golemcompiled.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golembuilderclosure.c -o engine/golembuilderclosure.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemnew.c -o engine/golemnew.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemconstant.c -o engine/golemconstant.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemparser.c -o engine/golemparser.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/goleminvoke.c -o engine/goleminvoke.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemif.c -o engine/golemif.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/goleminit.c -o engine/goleminit.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golembuilderextern.c -o engine/golembuilderextern.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemdebugobject.c -o engine/golemdebugobject.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemwhile.c -o engine/golemwhile.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golembuilderfunction.c -o engine/golembuilderfunction.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golem.c -o engine/golem.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemexpressioncomplex.c -o engine/golemexpressioncomplex.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemcontext.c -o engine/golemcontext.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemblock.c -o engine/golemblock.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemllm.c -o engine/golemllm.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemextends.c -o engine/golemextends.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemexpression.c -o engine/golemexpression.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemstatement.c -o engine/golemstatement.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemerror.c -o engine/golemerror.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemmember.c -o engine/golemmember.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemdeclaration.c -o engine/golemdeclaration.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemidentificator.c -o engine/golemidentificator.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golembuilderclass.c -o engine/golembuilderclass.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemtypeinfo.c -o engine/golemtypeinfo.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemcinvoke.c -o engine/golemcinvoke.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c engine/golemsharedobject.c -o engine/golemsharedobject.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc -c main.c -o main.o -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
gcc  engine/golemclosure.o engine/golemcompiled.o engine/golembuilderclosure.o engine/golemnew.o engine/golemconstant.o engine/golemparser.o engine/goleminvoke.o engine/golemif.o engine/goleminit.o engine/golembuilderextern.o engine/golemdebugobject.o engine/golemwhile.o engine/golembuilderfunction.o engine/golem.o engine/golemexpressioncomplex.o engine/golemcontext.o engine/golemblock.o engine/golemllm.o engine/golemextends.o engine/golemexpression.o engine/golemstatement.o engine/golemerror.o engine/golemmember.o engine/golemdeclaration.o engine/golemidentificator.o engine/golembuilderclass.o engine/golemtypeinfo.o engine/golemcinvoke.o engine/golemsharedobject.o main.o -o Debug/golem -Wl,--export-dynamic -lgmodule-2.0 -pthread -lgio-2.0 -lgobject-2.0 -lglib-2.0
rm  engine/golemclosure.o engine/golemcompiled.o engine/golembuilderclosure.o engine/golemnew.o engine/golemconstant.o engine/golemparser.o engine/goleminvoke.o engine/golemif.o engine/goleminit.o engine/golembuilderextern.o engine/golemdebugobject.o engine/golemwhile.o engine/golembuilderfunction.o engine/golem.o engine/golemexpressioncomplex.o engine/golemcontext.o engine/golemblock.o engine/golemllm.o engine/golemextends.o engine/golemexpression.o engine/golemstatement.o engine/golemerror.o engine/golemmember.o engine/golemdeclaration.o engine/golemidentificator.o engine/golembuilderclass.o engine/golemtypeinfo.o engine/golemcinvoke.o engine/golemsharedobject.o main.o
