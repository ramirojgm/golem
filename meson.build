project('golem','c')

glib_deps = dependency('glib-2.0')
gobject_deps = dependency('gobject-2.0')
gio_deps = dependency('gio-2.0')
gmodule_deps = dependency('gmodule-2.0')
libffi_deps = dependency('libffi')


golem_exec = executable ('golem',[
              'golemenums.h',
              'golemenums.c',
              'golemerror.h',
              'golemerror.c',
              
              'vm/golemvm.h',
              'vm/golemvm.c',
              
              'metadata/golemmetadata.h',
              'metadata/golemmetadata.c',
              'metadata/golemprimitive.h',
              'metadata/golemprimitive.c',
              'metadata/golemattribute.h',
              'metadata/golemattribute.c',
              'metadata/golemfunction.h',
              'metadata/golemfunction.c',
              'metadata/golemtype.h',
              'metadata/golemtype.c',

              'metadata/function/golemsymbol.h',
              'metadata/function/golemsymbol.c',              
              'metadata/function/golemfunctionwrap.h',
              'metadata/function/golemfunctionwrap.c',
              
              'compile/golemparser.h',
              'compile/golemparser.c',
              'compile/golemscopebuilder.h',
              'compile/golemscopebuilder.c',
              'compile/golemstatement.h',
              'compile/golemstatement.c',
              'compile/golemblock.h',
              'compile/golemblock.c',
              'compile/golemreturn.h',
              'compile/golemreturn.c',
              'compile/golemexpression.h',
              'compile/golemexpression.c',
              
              'compile/expr/golemconst.h',
              'compile/expr/golemconst.c',
              'compile/expr/golemneg.h',
              'compile/expr/golemneg.c',
              'compile/expr/golemcontext.h',
              'compile/expr/golemcontext.c',
              'compile/expr/golemnot.h',
              'compile/expr/golemnot.c',
              'compile/expr/golemaccessor.h',
              'compile/expr/golemaccessor.c',
              'compile/expr/golemcall.h',
              'compile/expr/golemcall.c',
              
              'golem.h',
              'golem.c'
            ],
            dependencies: [
            	glib_deps,
            	gobject_deps,
            	gio_deps,
            	gmodule_deps,
            	libffi_deps
	       ],
	       link_args: '-lm',
            install: true)

test('golem',golem_exec)