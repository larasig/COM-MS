
#pragma once

interface ILunerCalendarConverter : IUnknown
{
public:
	STDMETHOD(ToPublicCalendar) (int year, int month, int date) PURE;
};

// {F285EC8E-0287-4E78-8B1E-A4AA34984FA3}
static const IID IID_ILunerCalendarConverter = 
{ 0xf285ec8e, 0x287, 0x4e78, { 0x8b, 0x1e, 0xa4, 0xaa, 0x34, 0x98, 0x4f, 0xa3 } };

// {955EC22C-3EB1-46CF-96E3-A77EEB6EE987} 
static const GUID CLSID_LunerCalendarConverter = 
{ 0x955ec22c, 0x3eb1, 0x46cf, { 0x96, 0xe3, 0xa7, 0x7e, 0xeb, 0x6e, 0xe9, 0x87 } };

