
CLGridBookps.dll: dlldata.obj CLGridBook_p.obj CLGridBook_i.obj
	link /dll /out:CLGridBookps.dll /def:CLGridBookps.def /entry:DllMain dlldata.obj CLGridBook_p.obj CLGridBook_i.obj \
		mtxih.lib mtx.lib mtxguid.lib \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
		ole32.lib advapi32.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		/MD \
		$<

clean:
	@del CLGridBookps.dll
	@del CLGridBookps.lib
	@del CLGridBookps.exp
	@del dlldata.obj
	@del CLGridBook_p.obj
	@del CLGridBook_i.obj
