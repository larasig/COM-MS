#include "stdafx.h"

#include <tchar.h>
#include <string>
#include "RegistryHelper.h"
using namespace std;

void _CmbStr(LPTSTR str1, LPTSTR str2, TCHAR buf[], int len)
{
	wstring s1 = str1;
	s1 += str2;
	_tcscpy_s(buf, len, s1.c_str());
}

HRESULT ComRegistryHelper::DllRegisterServer(
	HINSTANCE hDll,
	LPTSTR szClassDesc,
	LPTSTR szCLSID
	)
{
	HKEY hCLSIDKey = NULL, hInProcSvrKey = NULL;

	LONG lRet;
	TCHAR szModulePath[MAX_PATH];
	//TCHAR szClassDesc[] = _T("MsgBox class");
	TCHAR szThreadingModel[] = _T("Apartment");
	TCHAR CLSIDKeyStr[256];

	_CmbStr(_T("CLSID\\"), szCLSID, CLSIDKeyStr, 256);
	__try
	{

		lRet = RegCreateKeyEx(
			HKEY_CLASSES_ROOT,
			CLSIDKeyStr,
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
			(const BYTE*)szClassDesc, _tcslen(szClassDesc)*sizeof(TCHAR)
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

		GetModuleFileName(hDll, szModulePath, MAX_PATH);
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

HRESULT ComRegistryHelper::DllUnregisterServer(LPTSTR szCLSID)
{
	TCHAR CLSIDKeyStr[256];
	TCHAR CLSIDKeyStrInProc[256];
	_CmbStr(_T("CLSID\\"), szCLSID, CLSIDKeyStr, 256);
	_CmbStr(CLSIDKeyStr, _T("\\InProcServer32"), CLSIDKeyStrInProc, 256);

	RegDeleteKey(HKEY_CLASSES_ROOT, CLSIDKeyStrInProc);
	RegDeleteKey(HKEY_CLASSES_ROOT, CLSIDKeyStr);
	return S_OK;
}