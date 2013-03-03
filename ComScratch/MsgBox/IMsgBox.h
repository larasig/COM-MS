
#pragma once

interface IMsgBox : IUnknown
{
	virtual HRESULT DoSimpleMsgBox(HWND hwndParent, BSTR bsMessageText) = 0;
};

// {AFF0F91C-B476-4F4F-AED2-02F761EC07E8}
static const IID IID_IMsgBox = 
{ 0xaff0f91c, 0xb476, 0x4f4f, { 0xae, 0xd2, 0x2, 0xf7, 0x61, 0xec, 0x7, 0xe8 } };

// {CDC91971-F903-4AED-9D47-4D9B8698B710}
static const CLSID CLSID_MsgBox = 
{ 0xcdc91971, 0xf903, 0x4aed, { 0x9d, 0x47, 0x4d, 0x9b, 0x86, 0x98, 0xb7, 0x10 } };
