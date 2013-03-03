#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <Windows.h>

#define _TRACE_MAX 512
//void _Trace(BOOL endl, LPCTSTR lpszFormat, ...);
void _Trace(LPCTSTR lpszFormat, ...);
void _TraceGUID(GUID guid, LPCTSTR lpszFormat);