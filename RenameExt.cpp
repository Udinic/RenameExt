// RenameExt.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f RenameExtps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "RenameExt.h"

#include "RenameExt_i.c"
#include "RenameExtImpl.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_RenameExtImpl, CRenameExtImpl)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_RENAMEEXTLib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	try
	{
		unsigned long length = 255;
		HKEY hKey = NULL;
		TCHAR ProgCLSID[] = _T("{C24483D3-1FC8-4F3B-86CD-6C9133A0B165}");
		
		if (RegCreateKeyEx(HKEY_CLASSES_ROOT, _T("*\\shellex\\ContextMenuHandlers\\ChangeExt"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS|KEY_READ, NULL, &hKey, &length) != ERROR_SUCCESS)
		{
			throw GetLastError();
		}
		
		if (RegSetValueEx(hKey, _T(""), 0, REG_SZ, (unsigned char *)ProgCLSID, sizeof(ProgCLSID)) != ERROR_SUCCESS)
		{
			throw GetLastError();
		}

		// registers object, typelib and all interfaces in typelib
		return _Module.RegisterServer(TRUE);
	}
	catch (LONG err)
	{
		TCHAR buff[255];
		LPVOID lpMsgBuf;
		FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			err,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,	0, NULL);

		_stprintf(buff, _T("Error Registering, %s"), lpMsgBuf);
	
		MessageBox(NULL, buff, _T("Error registring"), MB_OK);

		// Free the buffer.
		LocalFree( lpMsgBuf );
		return -1;
	}    
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	try
	{
		HKEY hKey = NULL;
	
		if (RegDeleteKey(HKEY_CLASSES_ROOT, _T("*\\shellex\\ContextMenuHandlers\\ChangeExt")) != ERROR_SUCCESS)
		{
			throw GetLastError();
		}

		return _Module.UnregisterServer(TRUE);				
	}
	catch (LONG err)
	{
		TCHAR buff[255];
		LPVOID lpMsgBuf;
		FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			err,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,	0, NULL);

		_stprintf(buff, _T("Error Registering, %s"), lpMsgBuf);
	
		MessageBox(NULL, buff, _T("Error registring"), MB_OK);

		// Free the buffer.
		LocalFree( lpMsgBuf );
		return -1;
	}
}


