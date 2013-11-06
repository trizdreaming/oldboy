
// oldboy.cpp : 메인함수가 포함 되어 있는 파일.

#include "stdafx.h"
#include "oldboy.h"
#include "RMmainLoop.h"

#include "RMprintConsole.h"

#pragma comment(lib, "d2d1")
#pragma comment(lib, "winmm")
#pragma comment(lib, "dwrite")
#pragma comment(lib, "WindowsCodecs")

#pragma comment( lib, "LibraryFmod/fmodex_vc.lib" )

// bandi
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")


//메인함수 시작
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 메모리 디버깅 옵션 부분
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

// 	AllocConsole();
// 	FILE* pFile; 
// 	freopen_s(&pFile, "CONOUT$", "wb", stdout);

	//HACCEL hAccelTable;
	//hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OLDBOY));

	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if ( SUCCEEDED( CoInitialize( NULL ) ) )
	{
		if ( SUCCEEDED( CRMmainLoop::GetInstance()->CreateMainLoopWindow() ) )
		{
			CRMmainLoop::GetInstance()->RunMessageLoop();
		}

		CoUninitialize();
	}

	// FreeConsole();

	return 0;
}

