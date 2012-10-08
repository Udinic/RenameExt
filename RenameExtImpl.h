// RenameExtImpl.h : Declaration of the CRenameExtImpl

#ifndef __RENAMEEXTIMPL_H_
#define __RENAMEEXTIMPL_H_

#include "resource.h"       // main symbols
#include <shlobj.h>

/////////////////////////////////////////////////////////////////////////////
// CRenameExtImpl



class ATL_NO_VTABLE CRenameExtImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRenameExtImpl, &CLSID_RenameExtImpl>,
	public IShellExtInit,
	public IContextMenu 
{
public:
	CRenameExtImpl()
	{
		
	}

DECLARE_REGISTRY_RESOURCEID(IDR_RENAMEEXTIMPL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRenameExtImpl)
	COM_INTERFACE_ENTRY_IID(IID_IShellExtInit,IShellExtInit)
	COM_INTERFACE_ENTRY_IID(IID_IContextMenu, IContextMenu)
END_COM_MAP()

#define IDM_DISPLAY 0

public:

LPCITEMIDLIST m_pIDFolder; //The folder's PIDL.

HKEY m_hRegKey; //The file or folder's registry key.

STDMETHODIMP Initialize(LPCITEMIDLIST pIDFolder, 
                                      IDataObject *pDataObj, 
                                      HKEY hRegKey);

STDMETHOD (GetCommandString)(UINT idCmd, UINT uFlags, UINT *pwReserved, LPSTR pszName, UINT cchMax);
STDMETHOD (InvokeCommand)(LPCMINVOKECOMMANDINFO lpcmi);
STDMETHOD (QueryContextMenu)(HMENU hMenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);

static BOOL CALLBACK DeleteItemProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) ;

private:
	static IDataObject *m_pDataObj;
	static BOOL m_singleExt;
	static TCHAR m_ext[MAX_PATH];
	
};



#endif //__RENAMEEXTIMPL_H_
