from building import *
import rtconfig

# get current directory
cwd     = GetCurrentDir()
# The set of source files associated with this SConscript file.
src     = Glob('src/*.c')

if GetDepend('VT100_USING_MONITOR'):
	src    += Glob('examples/vt_monitor.c')

path   =  [cwd + '/src']
path   += [cwd + '/examples']

LOCAL_CCFLAGS = ''

group = DefineGroup('vt100', src, depend = ['PKG_USING_VT100'], CPPPATH = path, LOCAL_CCFLAGS = LOCAL_CCFLAGS)

Return('group')
