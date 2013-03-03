
#pragma once

#include "../../CommonShared/RefCountHelper.h"
#include "../../CommonShared/_Trace.h"
#include "ILunerCalenderConverter.h"

class LunarCalenderConverterImpl : public ILunerCalendarConverter
{
public:
	LunarCalenderConverterImpl()
	{
		m_pRefCount = new RefCountHelper(this);
	}

	STDMETHOD_(ULONG, AddRef) ()
	{
		return m_pRefCount->AddRef();
	}

	STDMETHOD_(ULONG, Release) ()
	{
		return m_pRefCount->Release();
	}

	STDMETHOD(QueryInterface) (REFIID riid, void** ppv)
	{
		if (riid == IID_ILunerCalendarConverter)
		{
			*ppv = static_cast<ILunerCalendarConverter*>(this);
		}
		else
		{
			*ppv = NULL;
			return E_NOINTERFACE;
		}

		if (*ppv != NULL)
		{
			this->AddRef();
		}
		return S_OK;
	}

	STDMETHOD(ToPublicCalendar) (int year, int month, int date)
	{
		_Trace(_T("ToPublicCalendar"));
		return S_OK;
	}
private:
	RefCountHelper* m_pRefCount;
};

