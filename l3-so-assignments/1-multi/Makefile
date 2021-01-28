CFLAGS = /nologo /W3 /EHsc /Za /MD /D_CRT_SECURE_NO_DEPRECATE

build: so-cpp.exe

so-cpp.exe: so-cpp.obj
	cl /Feso-cpp.exe so-cpp.obj

so-cpp.obj:
	cl /c so-cpp.c /Foso-cpp.obj $(CFLAGS)

clean:
	del *.obj *.exe