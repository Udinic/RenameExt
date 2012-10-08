/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Sep 13 13:57:29 2004
 */
/* Compiler settings for C:\My Projects\RenameExt\RenameExt.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __RenameExt_h__
#define __RenameExt_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IRenameExtImpl_FWD_DEFINED__
#define __IRenameExtImpl_FWD_DEFINED__
typedef interface IRenameExtImpl IRenameExtImpl;
#endif 	/* __IRenameExtImpl_FWD_DEFINED__ */


#ifndef __RenameExtImpl_FWD_DEFINED__
#define __RenameExtImpl_FWD_DEFINED__

#ifdef __cplusplus
typedef class RenameExtImpl RenameExtImpl;
#else
typedef struct RenameExtImpl RenameExtImpl;
#endif /* __cplusplus */

#endif 	/* __RenameExtImpl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IRenameExtImpl_INTERFACE_DEFINED__
#define __IRenameExtImpl_INTERFACE_DEFINED__

/* interface IRenameExtImpl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRenameExtImpl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A6CCD6F0-D247-4E22-AF37-245016EB0F3F")
    IRenameExtImpl : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IRenameExtImplVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRenameExtImpl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRenameExtImpl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRenameExtImpl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRenameExtImpl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRenameExtImpl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRenameExtImpl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRenameExtImpl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IRenameExtImplVtbl;

    interface IRenameExtImpl
    {
        CONST_VTBL struct IRenameExtImplVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRenameExtImpl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRenameExtImpl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRenameExtImpl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRenameExtImpl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRenameExtImpl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRenameExtImpl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRenameExtImpl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRenameExtImpl_INTERFACE_DEFINED__ */



#ifndef __RENAMEEXTLib_LIBRARY_DEFINED__
#define __RENAMEEXTLib_LIBRARY_DEFINED__

/* library RENAMEEXTLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_RENAMEEXTLib;

EXTERN_C const CLSID CLSID_RenameExtImpl;

#ifdef __cplusplus

class DECLSPEC_UUID("C24483D3-1FC8-4F3B-86CD-6C9133A0B165")
RenameExtImpl;
#endif
#endif /* __RENAMEEXTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
