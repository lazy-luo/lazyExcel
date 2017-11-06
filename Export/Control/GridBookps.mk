
GridBookps.dll: dlldata.obj GridBook_p.obj GridBook_i.obj
	link /dll /out:GridBookps.dll /def:GridBookps.def /entry:DllMain dlldata.obj GridBook_p.obj GridBook_i.obj \
		mtxih.lib mtx.lib mtxguid.lib \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
		ole32.lib advapi32.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		/MD \
		$<

clean:
	@del GridBookps.dll
	@del GridBookps.lib
	@del GridBookps.exp
	@del dlldata.obj
	@del GridBook_p.obj
	@del GridBook_i.obj
