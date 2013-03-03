// TestClient.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TestClient.h"

#include <comdef.h>
#include "../MsgBox/IMsgBox.h"
#include "../../CommonShared/_Trace.h"
#include "../LunarCalendar/ILunerCalenderConverter.h"

void TestMsgBox(HWND hMainWnd);

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TESTCLIENT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTCLIENT));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTCLIENT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TESTCLIENT);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


void TestLCC()
{
	ILunerCalendarConverter* pi = NULL;

	HRESULT hr;

	_TraceGUID(CLSID_LunerCalendarConverter, _T("TestLCC Calling CoCreateInstance, CLSID_LunerCalendarConverter "));
	_TraceGUID(IID_ILunerCalendarConverter, _T("Calling CoCreateInstance, IID_ILunerCalendarConverter "));
	hr = CoCreateInstance(
		CLSID_LunerCalendarConverter,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_ILunerCalendarConverter,
		(void **)&pi
		);
	if (FAILED(hr))
	{
		DWORD ec = GetLastError();
		_Trace(_T("HRESULT: %08x; Last error: %08x"), hr, ec);
		return;
	}

	pi->ToPublicCalendar(2000, 1, 1);
	pi->Release();

}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_FILE_TESTMSGBOXCOMSERVER:
			TestMsgBox(hWnd);
			break;
		case ID_FILE_TESTLCC:
			TestLCC();
			break;
		case ID_FILE_CALLCOFREEUNUSEDLIBRARIES:
			CoFreeUnusedLibraries();
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
		TCHAR szMessage[256];
		_stprintf(szMessage, _T("thread id: %08x"), GetCurrentThreadId());

		MessageBox(hDlg, szMessage, _T("dflskdjf"), MB_OK);

			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void TestMsgBox(HWND hMainWnd)
{
	IMsgBox* pIMsgBox = NULL;

	HRESULT hr;

	_TraceGUID(CLSID_MsgBox, _T("Calling CoCreateInstance, CLSID_MsgBox "));
	_TraceGUID(IID_IMsgBox, _T("Calling CoCreateInstance, IID_IMsgBox "));
	hr = CoCreateInstance(
		CLSID_MsgBox,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IMsgBox,
		(void **)&pIMsgBox
		);
	if (FAILED(hr))
	{
		DWORD ec = GetLastError();
		_Trace(_T("HRESULT: %08x; Last error: %08x"), hr, ec);
		return;
	}

	pIMsgBox->DoSimpleMsgBox(
		hMainWnd, _bstr_t("H com!")
		);
	pIMsgBox->Release();

}