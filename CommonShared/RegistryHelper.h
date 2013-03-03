
#pragma once
#include <Windows.h>

class ComRegistryHelper
{
public:
	static HRESULT DllRegisterServer(HINSTANCE hDll,
		LPTSTR szClassDesc,
		LPTSTR szCLSID);

	static HRESULT DllUnregisterServer(LPTSTR szCLSID);

private:
	
};
