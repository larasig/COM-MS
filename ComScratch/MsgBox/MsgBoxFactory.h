
#pragma once

#include "MsgBox.h"

class MsgBoxFactory : public IClassFactory
{
public:
	MsgBoxFactory() : m_uRefCount(0) {}

	HRESULT __stdcall QueryInterface(REFIID riid, void **ppv)
	{
		_Trace(_T("MsgBoxFactory::QueryInterface"));

		if (riid == IID_IClassFactory)
		{
			*ppv = static_cast<IClassFactory*>(this);
		}
		else
		{
			return E_NOINTERFACE;
		}

		((IUnknown*)*ppv)->AddRef();

		return S_OK;
	}

	ULONG __stdcall AddRef() { return ++m_uRefCount; }
	ULONG __stdcall Release() { if (--m_uRefCount == 0) delete this; return 0; }

	HRESULT __stdcall CreateInstance(IUnknown *pOuter, REFIID riid, void **ppv)
	{
		_Trace(_T("MsgBoxFactory::CreateInstance"));
		if (pOuter != NULL)
		{
			return CLASS_E_NOAGGREGATION;
		}

		*ppv = NULL;
		MsgBox *pm = new MsgBox;
		if (NULL == pm)
		{
			return E_OUTOFMEMORY;
		}

		HRESULT hr = pm->QueryInterface(riid, ppv);
		if (FAILED(hr))
		{
			delete pm;
		}

		return hr;

		return ((IUnknown*)*ppv)->AddRef();
	}

	HRESULT __stdcall LockServer(BOOL fLock)
	{
		_Trace(_T("MsgBoxFactory::LockServer"));
		fLock ? g_uDllLockCount ++ : g_uDllLockCount --;
		return S_OK;
	}

private:
	ULONG m_uRefCount;
};