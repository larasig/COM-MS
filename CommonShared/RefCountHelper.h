
#pragma once

#include <ObjBase.h>

class RefCountHelper
{
public:
	RefCountHelper(void* owner) : m_ulCount(0)
	{
		m_ptrOwner = owner;
	}

	unsigned long AddRef()
	{
		m_ulCount++;
		return m_ulCount;
	}

	unsigned long Release()
	{
		m_ulCount--;
		if (0 == m_ulCount)
		{
			delete m_ptrOwner;
			return 0;
		}
		return m_ulCount;
	}

	BOOLEAN QueryInterface(REFIID riid, REFIID expRiid)
	{
		return riid == expRiid;
	}
private:
	void* m_ptrOwner;
	unsigned long m_ulCount;
};