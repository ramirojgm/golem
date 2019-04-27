project('golem','c')

glib_deps = dependency('glib-2.0')
gobject_deps = dependency('gobject-2.0')
gio_deps = dependency('gio-2.0')


golem_exec = executable ('golem',[
              'golemenums.h',
              'golemenums.c',
              
              'vm/golemvm.h',
              'vm/golemvm.c',
              
              'metadata/golemmetadata.h',
              'metadata/golemmetadata.c',
              'metadata/golemprimitive.h',
              'metadata/golemprimitive.c',
              'metadata/golemattribute.h',
              'metadata/golemattribute.c',
              'metadata/golemtype.h',
              'metadata/golemtype.c',
              
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
              'golem.h',
              'golem.c'
            ],
            dependencies: [
            	glib_deps,
            	gobject_deps,
            	gio_deps
	       ],
	       link_args: '-lm',
            install: true)

test('golem',golem_exec)