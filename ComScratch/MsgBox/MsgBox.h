
#pragma once
#include "IMsgBox.h"

#include "../../CommonShared/_Trace.h"

class MsgBox : public IMsgBox
{
public:
	MsgBox() : m_nRefCount(0) {}
	
	ULONG __stdcall AddRef() { return ++m_nRefCount; }
	ULONG __stdcall Release() { if (--m_nRefCount == 0) delete this; return 0; }
	HRESULT __stdcall QueryInterface(REFIID riid, void **ppv)
	{
		_Trace(_T("MsgBox::QueryInterface"));
		_TraceGUID(riid, _T("MsgBox::QueryInterface: param riid "));
		if (riid == IID_IMsgBox)
		{
			*ppv = static_cast<IMsgBox*>(this);
		}
		else
		{
			return E_NOINTERFACE;
		}

		((IUnknown*)*ppv)->AddRef();

		return S_OK;
	}

	HRESULT DoSimpleMsgBox(HWND hwndParent, BSTR bsMessageText)
	{
		_Trace(_T("MsgBox::DoSimpleMsgBox"));
		_bstr_t bsMsg = bsMessageText;
		LPCTSTR szMsg = (TCHAR*)bsMsg;
		TCHAR szMessage[256];
		_stprintf(szMessage, _T("%s; thread id: %08x"), szMsg, GetCurrentThreadId());

		MessageBox(hwndParent, szMessage, _T("dflskdjf"), MB_OK);
		return S_OK;
	}
private:
	int m_nRefCount;
};