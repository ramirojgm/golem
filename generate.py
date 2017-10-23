#!/usr/bin/env python3

import os
import subprocess

sources = []
original_path = './'
programname = 'Debug/golem'
scriptname = ''

if os.name == 'nt':
    scriptname = 'make.bat'
else:
    scriptname = 'make.sh'

def load_sources(path):
    try:
        list_file = os.listdir(path)
        for file in list_file:
            if(os.path.isfile(os.path.join(path, file))):
                if(file.endswith('.c')):
                    new_path = os.path.join(path,file)
                    sources.append(new_path[len(original_path):])
            else:
                load_sources(os.path.join(path,file))
    except Exception:
        print(path)
        
load_sources(original_path)

compile_flags = subprocess.check_output(['pkg-config', '--cflags','glib-2.0', 'gmodule-2.0', 'gio-2.0']).decode('utf-8')
compile_flags = compile_flags.replace('\n','').replace('\r','')
compile_libs = subprocess.check_output(['pkg-config', '--libs', 'glib-2.0', 'gmodule-2.0', 'gio-2.0']).decode('utf-8')
compile_libs = compile_libs.replace('\n','').replace('\r','')

script = open(os.path.join(original_path,scriptname),'w')

if os.name == 'nt':
    script.write('@echo off\n')
else:
	script.write('#!/bin/bash\n')

objects = ''
for src in sources:
    objectname = src[0:len(src) - 2] + '.o'
    objects = objects + ' ' + objectname
    script.write('gcc -c %s -o %s %s -std=c99\n' % (src,objectname,compile_flags))
script.write('gcc %s -o %s %s\n' % (objects,programname,compile_libs))
if os.name == 'nt':
    script.write('del %s\n' % (objects,))
    script.write('pause\n')
else:
    script.write('rm %s\n' % (objects,))
script.close()
    
