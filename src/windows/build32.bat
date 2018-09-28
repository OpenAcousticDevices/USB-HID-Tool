cl /I .. ../main.c hid.c /link /out:usbhidtool.exe SetupAPI.lib

del *.obj
del *.exp
del *.lib

move usbhidtool.exe ../../bin/windows32/usbhidtool.exe


