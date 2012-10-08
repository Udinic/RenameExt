// RenameExtImpl.cpp : Implementation of CRenameExtImpl
#include "stdafx.h"
#include "RenameExt.h"
#include "RenameExtImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CRenameExtImpl

IDataObject* CRenameExtImpl::m_pDataObj = NULL;
BOOL CRenameExtImpl::m_singleExt;
TCHAR CRenameExtImpl::m_ext[MAX_PATH];

STDMETHODIMP CRenameExtImpl::Initialize(LPCITEMIDLIST pIDFolder, IDataObject *pDataObj, HKEY hRegKey) 
{ 
    // If Initialize has already been called, release the old
    // IDataObject pointer.
    if (m_pDataObj)
	{ 
        m_pDataObj->Release(); 
    }
	 
    // If a data object pointer was passed in, save it and
    // extract the file name. 
    if (pDataObj) 
    { 
        m_pDataObj = pDataObj;

		m_pDataObj->AddRef();
      
		STGMEDIUM   medium;
	
		UINT        uCount;
		FORMATETC   fe = {CF_HDROP, NULL, DVASPECT_CONTENT, -1, 
						  TYMED_HGLOBAL};

		TCHAR szFile[MAX_PATH];

		if(SUCCEEDED(m_pDataObj->GetData(&fe, &medium)))
		{
		// Get the file name from the CF_HDROP.
			unsigned int i;
			uCount = DragQueryFile((HDROP)medium.hGlobal, (UINT)-1, 
									NULL, 0);

			m_singleExt = TRUE;
			lstrcpy(m_ext, _T(""));

			for (i = 0; i < uCount; i++)
			{
				DragQueryFile((HDROP)medium.hGlobal, i, szFile, 
							  sizeof(szFile));
				
				TCHAR* tempExt = _tcsrchr(szFile, '.');
			//	if (tempExt != NULL)
				{
					if (lstrcmp(m_ext, _T("")) == 0)
					{
						lstrcpy(m_ext, tempExt);
					}
					else
					{
						if (lstrcmp(m_ext, tempExt) != 0)
						{
							m_singleExt = FALSE;
							break;
						}
					}
				
				}
			}

			ReleaseStgMedium(&medium);
		}

    }

    // Duplicate the registry handle. 
    if (hRegKey) 
        RegOpenKeyEx(   hRegKey, 
                        NULL, 
                        0L, 
                        MAXIMUM_ALLOWED, 
                        &m_hRegKey); 
    return S_OK; 
}


HRESULT STDMETHODCALLTYPE 
CRenameExtImpl::QueryContextMenu(HMENU hMenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
	if((CMF_CANRENAME & uFlags))
    {
        InsertMenu(hMenu, 
                    indexMenu, 
                    MF_STRING | MF_BYPOSITION, 
                    idCmdFirst + IDM_DISPLAY, 
                    _T("&Change File Extention"));

        return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(IDM_DISPLAY + 1));
    }

    return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(0));
}

HRESULT STDMETHODCALLTYPE 
CRenameExtImpl::GetCommandString(UINT idCmd, UINT uFlags, UINT *pwReserved, LPSTR pszName, UINT cchMax)
{
	HRESULT  hr = E_INVALIDARG;
	int uMaxNameLen = 100;
    if(idCmd != IDM_DISPLAY)
    {
        return hr;
    }

    switch(uFlags)
    {
       	case GCS_HELPTEXTA:        
		case GCS_VERBA:
            lstrcpynA(pszName, "Change File Extention", uMaxNameLen);
            hr = S_OK;
            break; 

		case GCS_HELPTEXTW: 
        case GCS_VERBW: 
            lstrcpynW((LPWSTR)pszName, L"Change File Extention", uMaxNameLen); 
            hr = S_OK;
            break; 
   
        default:
            hr = S_OK;
            break; 
    }
    return hr;
}

HRESULT STDMETHODCALLTYPE CRenameExtImpl::InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi)
{
	BOOL fEx = FALSE;
    BOOL fUnicode = FALSE;

    if(lpcmi->cbSize = sizeof(CMINVOKECOMMANDINFOEX))
    {
        fEx = TRUE;
        if((lpcmi->fMask & CMIC_MASK_UNICODE))
        {
            fUnicode = TRUE;
        }
    }

    DialogBox( _Module.GetModuleInstance(), MAKEINTRESOURCE(IDD_RENAME), lpcmi->hwnd, (DLGPROC)DeleteItemProc );
	
    return S_OK;
}

BOOL CALLBACK CRenameExtImpl::DeleteItemProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{
	FORMATETC   fe = {CF_HDROP, NULL, DVASPECT_CONTENT, -1, 
					  TYMED_HGLOBAL};
	switch (message) 
    { 
	   case WM_INITDIALOG:
		
			RECT rc;
			POINT mp;
			int width, height;

			GetWindowRect(hwndDlg, &rc);
			GetCursorPos(&mp);
			width = rc.right - rc.left;
			height = rc.bottom - rc.top;

			MoveWindow(hwndDlg, mp.x - width/2, mp.y - height/3, width, height,TRUE);
			
			HWND hEdit;
			hEdit = GetDlgItem(hwndDlg, IDC_EXT );    // Get handle to control.

			TCHAR Message[200];
			DWORD CURR_IDS;
			CURR_IDS = IDS_MULTIEXT;

			if (m_singleExt)
			{
				CURR_IDS = IDS_ONEEXT;
				SetWindowText(hEdit, (m_ext[0] == NULL) ? _T("") : m_ext+1);
			}
						
			LoadString(_Module.GetModuleInstance(), CURR_IDS, Message, sizeof(Message));
			SetWindowText(GetDlgItem(hwndDlg, IDC_STATICEXT), Message);
			
		    SetFocus( hEdit );			
		    SendMessage( hEdit, EM_SETSEL, 0, MAKELONG(0xffff,0xffff) ); 

			return TRUE;
					   		   
        case WM_COMMAND: 
            switch (LOWORD(wParam)) 
            { 
                case IDOK: 
					m_pDataObj->AddRef();
      
					STGMEDIUM medium;
				
					UINT      uCount;
					TCHAR	  szFile[MAX_PATH];

					if(SUCCEEDED(m_pDataObj->GetData(&fe, &medium)))
					{
						// Get the file name from the CF_HDROP.
						unsigned int i;
						uCount = DragQueryFile((HDROP)medium.hGlobal, (UINT)-1, NULL, 0);

						for (i = 0; i < uCount; i++)
						{
							DragQueryFile((HDROP)medium.hGlobal, i, szFile, sizeof(szFile));

							TCHAR  szExt[MAX_PATH];
							TCHAR  szOldFile[MAX_PATH];
							TCHAR* szTempExt;
							int Offset;
							Offset = 0;
														
							lstrcpy(szOldFile, szFile);	
							
							GetDlgItemText(hwndDlg, IDC_EXT, szExt, MAX_PATH);
							if (szExt[0] != '.')
							{
								szExt[0] = '.';
								GetDlgItemText(hwndDlg, IDC_EXT, szExt+1, MAX_PATH);
							}

							szTempExt = _tcsrchr(szFile, '.');
							
							if (szTempExt != NULL)
							{
								lstrcpy(szTempExt, szExt);
							}
							else
							{
								_tcscat(szFile, szExt);
							}							


							if (MoveFileEx(szOldFile, szFile, NULL) == 0)
							{
								LPVOID lpMsgBuf;
								FormatMessage( 
									FORMAT_MESSAGE_ALLOCATE_BUFFER | 
									FORMAT_MESSAGE_FROM_SYSTEM | 
									FORMAT_MESSAGE_IGNORE_INSERTS,
									NULL,
									GetLastError(),
									0, // Default language
									(LPTSTR) &lpMsgBuf,
									0,
									NULL 
								);
								// Process any inserts in lpMsgBuf.
								// ...
								// Display the string.
								MessageBox( NULL, (LPCTSTR)lpMsgBuf, _T("Error"), MB_OK | MB_ICONINFORMATION );
								// Free the buffer.
								LocalFree( lpMsgBuf );
							}
						}

						ReleaseStgMedium(&medium);
					}
  
                case IDCANCEL: 
                    EndDialog(hwndDlg, wParam); 
                    return TRUE; 
            } 
    } 
    return FALSE; 

}
