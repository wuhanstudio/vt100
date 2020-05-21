from building import *
import rtconfig

# get current directory
cwd     = GetCurrentDir()
# The set of source files associated with this SConscript file.
src     = Glob('src/*.c')

if GetDepend('VT100_USING_MONITOR'):
	src    += Glob('examples/vt_monitor.c')

if GetDepend('VT100_USING_COLOR'):
	src    += Glob('examples/vt_color.c')

if GetDepend('VT100_USING_SL'):
	src    += Glob('examples/vt_sl.c')

if GetDepend('VT100_USING_IMGBUF'):
	src    += Glob('examples/vt_imshow.c')

if GetDepend('VT100_USING_LSIMG'):
	src    += Glob('examples/vt_lsimg.c')

path   =  [cwd + '/src']
path   += [cwd + '/examples']

LOCAL_CCFLAGS = ''

group = DefineGroup('vt100', src, depend = ['PKG_USING_VT100'], CPPPATH = path, LOCAL_CCFLAGS = LOCAL_CCFLAGS)

Return('group')
