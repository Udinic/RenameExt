
RenameExtps.dll: dlldata.obj RenameExt_p.obj RenameExt_i.obj
	link /dll /out:RenameExtps.dll /def:RenameExtps.def /entry:DllMain dlldata.obj RenameExt_p.obj RenameExt_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del RenameExtps.dll
	@del RenameExtps.lib
	@del RenameExtps.exp
	@del dlldata.obj
	@del RenameExt_p.obj
	@del RenameExt_i.obj
