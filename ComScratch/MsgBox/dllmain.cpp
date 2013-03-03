// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include "MsgBoxFactory.h"
#include "../../CommonShared/_Trace.h"

#if 1

HINSTANCE g_hThisDll = NULL;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_hThisDll = hModule;
		DisableThreadLibraryCalls(hModule);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#endif

HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	_Trace(_T("DllGetClassObject"));
	_TraceGUID(riid, _T("DllGetClassObject: param riid "));
	_TraceGUID(rclsid, _T("DllGetClassObject: param rclsid "));
	_TraceGUID(IID_IClassFactory, _T("DllGetClassObject: IID_IClassFactory "));
	if (rclsid != CLSID_MsgBox)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}

	*ppv = NULL;

	MsgBoxFactory *pfactory = new MsgBoxFactory;
	if (NULL == pfactory)
		return E_OUTOFMEMORY;

	pfactory->AddRef();
	pfactory->QueryInterface(riid, ppv);
	pfactory->Release();

	return S_OK;
}

STDAPI DllCanUnloadNow()
{
	_Trace(_T("DllCanUnloadNow"));
	return g_uDllLockCount > 0 ? S_FALSE : S_OK;
}

STDAPI DllRegisterServer()
{
	HKEY hCLSIDKey = NULL, hInProcSvrKey = NULL;

	LONG lRet;
	TCHAR szModulePath[MAX_PATH];
	TCHAR szClassDesc[] = _T("MsgBox class");
	TCHAR szThreadingModel[] = _T("Apartment");

	__try
	{
		lRet = RegCreateKeyEx(
			HKEY_CLASSES_ROOT,
			_T("CLSID\\{CDC91971-F903-4AED-9D47-4D9B8698B710}"),
			0,
			NULL,
			REG_OPTION_NON_VOLATILE,
			KEY_SET_VALUE,
			NULL,
			&hCLSIDKey,
			NULL
			);

		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);

		lRet = RegSetValueEx(hCLSIDKey, NULL, 0, REG_SZ,
			(const BYTE*)szClassDesc, sizeof(szClassDesc)
			);

		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);

		lRet = RegCreateKeyEx(hCLSIDKey, _T("InProcServer32"),
			0, NULL,
			REG_OPTION_NON_VOLATILE,
			KEY_SET_VALUE,
			NULL,
			&hInProcSvrKey,
			NULL
			);

		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);

		GetModuleFileName(g_hThisDll, szModulePath, MAX_PATH);
		lRet = RegSetValueEx(hInProcSvrKey, NULL, 0, REG_SZ, (const BYTE*)szModulePath,
			sizeof(TCHAR)*(lstrlen(szModulePath)+1)
			);

		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);

		lRet = RegSetValueEx(hInProcSvrKey,
			_T("ThreadingModel"),
			0,
			REG_SZ,
			(const BYTE*)szThreadingModel,
			sizeof(szThreadingModel)
			);

		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);
	}
	__finally
	{
		if (NULL == hCLSIDKey)
			RegCloseKey(hCLSIDKey);

		if (NULL == hInProcSvrKey)
		{
			RegCloseKey(hInProcSvrKey);
		}

	}
		return S_OK;
}

STDAPI DllUnregisterServer()
{
	RegDeleteKey(HKEY_CLASSES_ROOT, _T("CLSID\\{CDC91971-F903-4AED-9D47-4D9B8698B710}\\InProcServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, _T("CLSID\\{CDC91971-F903-4AED-9D47-4D9B8698B710}"));
	return S_OK;
}