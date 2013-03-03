#include "stdafx.h"

#include "_Trace.h"

void GUID2String(GUID const& guid, TCHAR output[])
{
	_sntprintf(output, 40, _T("{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}"),
		guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1],
		guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]
	);
}

void _Trace(BOOL endl, LPCTSTR lpszFormat, va_list args)
{
	//va_list args;
	int nBuf;
	TCHAR szBuffer[_TRACE_MAX];

	//va_start(args, lpszFormat);

	if (args != NULL)
	{
		nBuf = _vsntprintf(szBuffer, 512, lpszFormat, args);
	}

	OutputDebugString(szBuffer);
	if (endl)
	{
		OutputDebugString(_T("\n"));
	}

	//va_end(args);
}

void _Trace(BOOL endl, LPCTSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	_Trace(endl, lpszFormat, args);

	va_end(args);
}

void _Trace(LPCTSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	_Trace(TRUE, lpszFormat, args);

	va_end(args);
}

void _TraceGUID(GUID guid, LPCTSTR msg)
{
	TCHAR buf[40];

	GUID2String(guid, buf);

	_Trace(FALSE, msg);
	_Trace(buf);
}