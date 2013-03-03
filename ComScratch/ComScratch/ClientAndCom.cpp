
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

interface IComponent: IUnknown
{
	virtual void __stdcall Print(const char* msg) = 0;
};

// {39E1C11A-4DEC-4B59-8E27-9B7014E59631}
static const IID IID_IComponent = 
{ 0x39e1c11a, 0x4dec, 0x4b59, { 0x8e, 0x27, 0x9b, 0x70, 0x14, 0xe5, 0x96, 0x31 } };

class CComponent : public IComponent
{
public:
	virtual HRESULT __stdcall QueryInterface(const IID& iid, void **ppv);
	virtual ULONG __stdcall AddRef() { Print("AddRef"); return InterlockedIncrement(&m_nRef); }
	virtual ULONG __stdcall Release()
	{
		Print("Release");
		if ( InterlockedDecrement(&m_nRef) == 0)
		{
			delete this;
		}
		return 0;
	}

	CComponent(): m_nRef(0) {}

	virtual void __stdcall Print(const char *msg);
private:
	long m_nRef;
};

HRESULT __stdcall CComponent::QueryInterface(const IID& iid, void **ppv)
{
	if (iid == IID_IUnknown)
	{
		*ppv = static_cast<IComponent*>(this);
	}
	else if (iid == IID_IComponent)
	{
		*ppv = static_cast<IComponent*>(this);
	}
	else
	{
		Print("Not supported");
		return E_NOINTERFACE;
	}

	AddRef();

	return S_OK;
}

void __stdcall CComponent::Print(const char* msg)
{
	cout << "------" << endl;
	cout << msg << endl;
	cout << "------" << endl;
}

IUnknown* CreateInstance()
{
	IUnknown *pUn = new CComponent;

	return pUn;
}

int _tmain(int argc, _TCHAR* argv[])
{
	IUnknown* pU = CreateInstance();
	IComponent *pI = NULL;
	pU->QueryInterface(IID_IComponent, (void**)&pI);
	pI->Print("testing");
	char c;
	cin >> c;
	pI->Release();
	cin >> c;
	return 0;
}

