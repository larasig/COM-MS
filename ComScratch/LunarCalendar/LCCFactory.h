
#pragma once
#include "../../CommonShared/RefCountHelper.h"
#include "LunarCalendarImpl.h"

class LCCFactory : public IClassFactory
{
public:
	LCCFactory()
	{
		m_refCount = new RefCountHelper(this);
	}

	STDMETHOD_(ULONG, AddRef) ()
	{
		return m_refCount->AddRef();
	}

	STDMETHOD_(ULONG, Release) ()
	{
		return m_refCount->Release();
	}

	//STDMETHOD(CreateInstance) (IUnknown *pOuter,
	//	REFIID riid,
	//	void **ppv)
	HRESULT __stdcall CreateInstance(IUnknown *pOuter, REFIID riid, void **ppv)
	{
		if (riid != IID_ILunerCalendarConverter)
		{
			return E_NOINTERFACE;
		}

		LunarCalenderConverterImpl* lcci = new LunarCalenderConverterImpl();
		return lcci->QueryInterface(riid, ppv);
	}

	//STDMETHOD(LockServer) (bool fLock)
	HRESULT __stdcall LockServer(BOOL fLock)
	{
		fLock ? InterlockedIncrement(&g_nDllCount) : InterlockedDecrement(&g_nDllCount);
		return S_OK;
	}

	STDMETHOD(QueryInterface) (REFIID riid, LPVOID* ppv)
	{
		if (m_refCount->QueryInterface(riid, __uuidof(IClassFactory)))
		{
			*ppv = static_cast<IClassFactory*>(this);
		}
		else
		{
			*ppv = NULL;
		}

		if (*ppv != NULL)
		{
			this->AddRef();
			return S_OK;
		}
		
		return E_NOINTERFACE;
	}
private:
	RefCountHelper* m_refCount;
};