// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include "ILunerCalenderConverter.h"
#include "LCCFactory.h"
#include "../../CommonShared/RegistryHelper.h"

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

HRESULT __stdcall DllGetClassObject(
  _In_   REFCLSID rclsid,
  _In_   REFIID riid,
  _Out_  LPVOID *ppv
)
{
	if (riid != IID_IClassFactory)
	{
		return E_NOINTERFACE;
	}

	LCCFactory* lccFactory = new LCCFactory();
	//lccFactory->CreateInstance(NULL, riid, ppv);
	lccFactory->AddRef();
	lccFactory->QueryInterface(riid, ppv);
	lccFactory->Release();

	return S_OK;
}

static long g_nDllCount = 0;

STDAPI DllCanUnloadNow()
{
	_Trace(_T("DllCanUnloadNow"));
	return g_nDllCount > 0 ? S_FALSE : S_OK;
}

STDAPI DllRegisterServer()
{
	return ComRegistryHelper::DllRegisterServer(
		g_hThisDll,
		_T("Lunar Calendar Converter"),
		_T("{955EC22C-3EB1-46CF-96E3-A77EEB6EE987}")
		);

}

STDAPI DllUnregisterServer()
{
	return ComRegistryHelper::DllUnregisterServer(_T("{955EC22C-3EB1-46CF-96E3-A77EEB6EE987}"));
}
