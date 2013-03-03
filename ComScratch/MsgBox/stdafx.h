// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <ObjBase.h>
#include <Ole2.h>
#include <comutil.h>
#include <tchar.h>

extern ULONG g_uDllLockCount;
extern const CLSID CLSID_MsgBox;
extern const IID IID_IMsgBox;

// TODO: reference additional headers your program requires here
