// DirectNoise.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DirectNoise.h"
#define INITGUID
#include <dmusici.h>
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DrumDialog( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL done = FALSE;

IDirectMusicLoader8*		g_pLoader = NULL;
IDirectMusicPerformance8*	g_pPerformance = NULL;
IDirectMusicSegment8*		g_pSegment2 = NULL;
IDirectMusicSegment8*		g_pSegment3 = NULL;
IDirectMusicSegment8*		g_pSegment4 = NULL;
IDirectMusicSegment8*		g_pSegment5 = NULL;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Dmusic and COM setup
	CoInitialize( NULL );

	CoCreateInstance( CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC,
						IID_IDirectMusicLoader8, (void **)&g_pLoader );
	CoCreateInstance( CLSID_DirectMusicPerformance, NULL, CLSCTX_INPROC,
						IID_IDirectMusicPerformance8, (void **)&g_pPerformance );
	// End Dmusic and COM setup

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DIRECTNOISE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	//if (!InitInstance (hInstance, nCmdShow)) 
	//{
	//	return FALSE;
	//}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_DIRECTNOISE);

	// init audio
	g_pPerformance->InitAudio( 
	NULL,                  // IDirectMusic interface not needed.
	NULL,                  // IDirectSound interface not needed.
	NULL,                  // Window handle.
	DMUS_APATH_SHARED_STEREOPLUSREVERB,  // Default audiopath type.
	64,                    // Number of performance channels.
	DMUS_AUDIOF_ALL,       // Features on synthesizer.
	NULL                   // Audio parameters; use defaults.
	);
	// end init audio

	// Set the search directory.
	g_pLoader->SetSearchDirectory( 
		GUID_DirectMusicAllTypes,   // Types of files sought.
		L".\\Debug", // Where to look. Null for default
		FALSE                       // Don't clear object data.
	); // This function has a lot of stuff I did to it, explained below

	WCHAR wstrFileName2[MAX_PATH] = L"kick.wav";
	WCHAR wstrFileName3[MAX_PATH] = L"snare.wav";
	WCHAR wstrFileName4[MAX_PATH] = L"c_hihat.wav";
	WCHAR wstrFileName5[MAX_PATH] = L"hihat.wav";

	//make this message box say whatever you want to indicate the file
	//couldn't be found

	if (FAILED(g_pLoader->LoadObjectFromFile(
		CLSID_DirectMusicSegment,   // Class identifier.
		IID_IDirectMusicSegment8,   // ID of desired interface.
		wstrFileName2,               // Filename.
		(LPVOID*) &g_pSegment2)))    // Pointer that receives interface.
	{		
		MessageBox( NULL, "Media WAV not found, sample will now quit.", 
					"DMusic Tutorial", MB_OK );
		return 0;
	} 

	if (FAILED(g_pLoader->LoadObjectFromFile(
		CLSID_DirectMusicSegment,   // Class identifier.
		IID_IDirectMusicSegment8,   // ID of desired interface.
		wstrFileName3,               // Filename.
		(LPVOID*) &g_pSegment3)))    // Pointer that receives interface.
	{		
		MessageBox( NULL, "Media WAV2 not found, sample will now quit.", 
					"DMusic Tutorial", MB_OK );
		return 0;
	} 

	if (FAILED(g_pLoader->LoadObjectFromFile(
		CLSID_DirectMusicSegment,   // Class identifier.
		IID_IDirectMusicSegment8,   // ID of desired interface.
		wstrFileName4,               // Filename.
		(LPVOID*) &g_pSegment4)))    // Pointer that receives interface.
	{		
		MessageBox( NULL, "Media WAV3 not found, sample will now quit.", 
					"DMusic Tutorial", MB_OK );
		return 0;
	} 

	if (FAILED(g_pLoader->LoadObjectFromFile(
		CLSID_DirectMusicSegment,   // Class identifier.
		IID_IDirectMusicSegment8,   // ID of desired interface.
		wstrFileName5,               // Filename.
		(LPVOID*) &g_pSegment5)))    // Pointer that receives interface.
	{		
		MessageBox( NULL, "Media WAV4 not found, sample will now quit.", 
					"DMusic Tutorial", MB_OK );
		return 0;
	} 

	HWND hWnd = CreateDialog(hInst, (LPCTSTR)IDD_DRUMMACHINE, NULL, (DLGPROC)DrumDialog);
	ShowWindow( hWnd, nCmdShow );

	// Main message loop:
	while (!done && GetMessage(&msg, NULL, 0, 0)) 
	{
		if( msg.message == WM_KEYDOWN )
		{
			switch( msg.wParam )
			{
				case 'W':
					g_pSegment2->Download( g_pPerformance );

					g_pPerformance->PlaySegmentEx(
						g_pSegment2,  // Segment to play.
						NULL,        // Used for songs; not implemented.
						NULL,        // For transitions. 
						0,           // Flags.
						0,           // Start time; 0 is immediate.
						NULL,        // Pointer that receives segment state.
						NULL,        // Object to stop.
						NULL         // Audiopath, if not default.
					);
					break;
				case 'S':
					g_pSegment3->Download( g_pPerformance );

					g_pPerformance->PlaySegmentEx(
						g_pSegment3,  // Segment to play.
						NULL,        // Used for songs; not implemented.
						NULL,        // For transitions. 
						0,           // Flags.
						0,           // Start time; 0 is immediate.
						NULL,        // Pointer that receives segment state.
						NULL,        // Object to stop.
						NULL         // Audiopath, if not default.
					);
					break;
				case 'A':
					g_pSegment4->Download( g_pPerformance );

					g_pPerformance->PlaySegmentEx(
						g_pSegment4,  // Segment to play.
						NULL,        // Used for songs; not implemented.
						NULL,        // For transitions. 
						0,           // Flags.
						0,           // Start time; 0 is immediate.
						NULL,        // Pointer that receives segment state.
						NULL,        // Object to stop.
						NULL         // Audiopath, if not default.
					);
					break;
				case 'D':
					g_pSegment5->Download( g_pPerformance );

					g_pPerformance->PlaySegmentEx(
						g_pSegment5,  // Segment to play.
						NULL,        // Used for songs; not implemented.
						NULL,        // For transitions. 
						0,           // Flags.
						0,           // Start time; 0 is immediate.
						NULL,        // Pointer that receives segment state.
						NULL,        // Object to stop.
						NULL         // Audiopath, if not default.
					);
					break;
				case VK_ESCAPE:
					done = TRUE;
					break;
				default:
					break;
				}
		}
		else if ( hWnd == 0 || !IsDialogMessage( hWnd, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	g_pPerformance->Stop(
	NULL,   // Stop all segments.
	NULL,   // Stop all segment states.
	0,      // Do it immediately.
	0       // Flags.
	);

	g_pPerformance->CloseDown();

	if( g_pLoader) g_pLoader->Release();
	if( g_pPerformance ) g_pPerformance->Release();
	if( g_pSegment2) g_pSegment2->Release();
	if( g_pSegment3) g_pSegment3->Release();
	if( g_pSegment4) g_pSegment4->Release();
	if( g_pSegment5) g_pSegment5->Release();

	CoUninitialize();


	return 0;
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
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_SMALL);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_DIRECTNOISE;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
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

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
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
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
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
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK DrumDialog( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if( LOWORD(wParam) == IDEXIT )
		{
			DestroyWindow( hDlg );
			done = true;
			return TRUE;
		}
		else if(LOWORD( wParam) == IDC_KICK )
		{
			g_pSegment2->Download( g_pPerformance );

			g_pPerformance->PlaySegmentEx(
				g_pSegment2,  // Segment to play.
				NULL,        // Used for songs; not implemented.
				NULL,        // For transitions. 
				0,           // Flags.
				0,           // Start time; 0 is immediate.
				NULL,        // Pointer that receives segment state.
				NULL,        // Object to stop.
				NULL         // Audiopath, if not default.
			);
		}
		else if(LOWORD( wParam) == IDC_Snare )
		{
			g_pSegment3->Download( g_pPerformance );

			g_pPerformance->PlaySegmentEx(
				g_pSegment3,  // Segment to play.
				NULL,        // Used for songs; not implemented.
				NULL,        // For transitions. 
				0,           // Flags.
				0,           // Start time; 0 is immediate.
				NULL,        // Pointer that receives segment state.
				NULL,        // Object to stop.
				NULL         // Audiopath, if not default.
			);

		}
		else if(LOWORD( wParam) == IDC_C_HIHAT )
		{
			g_pSegment4->Download( g_pPerformance );

			g_pPerformance->PlaySegmentEx(
				g_pSegment4,  // Segment to play.
				NULL,        // Used for songs; not implemented.
				NULL,        // For transitions. 
				0,           // Flags.
				0,           // Start time; 0 is immediate.
				NULL,        // Pointer that receives segment state.
				NULL,        // Object to stop.
				NULL         // Audiopath, if not default.
			);

		}
		else if(LOWORD( wParam) == IDC_HIHAT )
		{
			g_pSegment5->Download( g_pPerformance );

			g_pPerformance->PlaySegmentEx(
				g_pSegment5,  // Segment to play.
				NULL,        // Used for songs; not implemented.
				NULL,        // For transitions. 
				0,           // Flags.
				0,           // Start time; 0 is immediate.
				NULL,        // Pointer that receives segment state.
				NULL,        // Object to stop.
				NULL         // Audiopath, if not default.
			);

		}
		return TRUE;
		break;
	}

	return FALSE;
}
