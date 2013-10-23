
// oldboy.cpp : 메인함수가 포함 되어 있는 파일.


#include "stdafx.h"
#include "oldboy.h"



#define MAX_LOADSTRING 100


// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.


// -- Fmod 테스트용 함수
void InitSound();
void LoadSound();
void PLAYsound();
void DeleteSound();

//-- 버튼 관리용 핸들을 위한 전역 변수 및 초기화
HWND hWndButton = NULL;

//-- Fmod 사용을 위한 전역 변수 선언 및 초기화
FMOD::System *systemS = NULL;
FMOD::Sound *sound = NULL;
FMOD::Channel *channel = NULL;

//-- 윈도우 이동용 함수 선언
void SetMoveWindow(HWND hWnd, WPARAM wParam);


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	// 메모리 디버깅 옵션 부분
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


 	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	HACCEL hAccelTable;


	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_OLDBOY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OLDBOY));

	// 기본 메시지 루프입니다.
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
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OLDBOY));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_OLDBOY);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	//-- Fmod에서 볼륨 조절을 하기 위한 변수
	float	fVolume = 0;
	bool	isMute = false;
	bool	isPlaying = false;
	bool	isPaused = false;
	//-- 여기까지

	switch (message)
	{
	
		// 추가 구문

	case WM_KEYDOWN:
		SetMoveWindow(hWnd, wParam);
	break;

		//-- 추가 된 코드
	case WM_CREATE:
		{
			// 초기 생성 시에만 한 번 뿌려주는 버튼
			if(hWndButton == NULL)
			{
				hWndButton = CreateWindowA("button", "Play", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
					100,100, 80,40, hWnd, (HMENU)100, NULL, NULL );
			
				InitSound();
				LoadSound();
			}
			// 여기까지

			CreateWindowA("button", "Stop", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
				200,100, 80,40, hWnd, (HMENU)101, NULL, NULL );
			CreateWindowA("button", "Change", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
				300,100, 80,40, hWnd, (HMENU)102, NULL, NULL );
			CreateWindowA("button", "Vol +", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
				100,200, 80,40, hWnd, (HMENU)200, NULL, NULL );
			CreateWindowA("button", "Vol -", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
				200,200, 80,40, hWnd, (HMENU)201, NULL, NULL );
			CreateWindowA("button", "Mute", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
				300,200, 80,40, hWnd, (HMENU)202, NULL, NULL );

			// 버튼을 추가하고 이 구문 바로 밑의 WM_COMMAND에서 파싱 될 메뉴 인덱스를 매핑함.
		}
		break;
		//-- 여기까지

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{

			//-- 임시로 추가한 위의 버튼에 매핑 된 인덱스의 명령어들
		case 100:
			channel->isPlaying(&isPlaying);

			if(!isPlaying)
			{
				PLAYsound();
				// 재생 시작
				SetWindowTextA(hWndButton, "Pause");
			}
			else
			// 재생 중
			{
				isPaused = false;
				channel->getPaused(&isPaused);
				
				if(isPaused)
				{
					channel->setPaused(false);
					// 재생 중
					SetWindowTextA(hWndButton, "Pause");
				}
				else
				{
					channel->setPaused(true);
					// 일시 정지 상태
					SetWindowTextA(hWndButton, "Play Again");
				}
			}
			break;

		case 101:
			channel->stop();
			// 정지 상태
			SetWindowTextA(hWndButton, "Play");
			break;

		case 102:
			channel->stop();
			break;

		case 200:
			channel->getMute(&isMute);
			if(isMute)
			{
				channel->setVolume(0);
				channel->setMute(false);
			}

			channel->getVolume(&fVolume);
			
			if(fVolume < 1)
				channel->setVolume(fVolume + static_cast<float>(0.1));
			else
				channel->setVolume(1);
			break;

		case 201:
			channel->getVolume(&fVolume);
			if(fVolume > 0.1)
				channel->setVolume(fVolume - static_cast<float>(0.1));
			else
				channel->setVolume(0);
			break;
			
		case 202:
			channel->getMute(&isMute);
			if(isMute)
				channel->setMute(false);
			else
				channel->setMute(true);
			break;
			//-- 여기까지

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
		// TODO: 여기에 그리기 코드를 추가합니다.

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:

		//-- Fmod 생성한 객체 삭제
		DeleteSound();
		//-- 여기까지

		PostQuitMessage(0);
		/*	실제 프로세스를 종료하는 함수
		
			프로그램 종료를 시도하면(x 버튼 => 닫기를 누르면)
			창을 닫고 WM_DESTROY 메시지를 보냄.
		
			WM_DESTORY 메시지를 여기서 캐치해서 PostQuitMessage() api를 호출하여 실제 프로세스를 종료함.
		*/

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



//-- Fmod 사용을 위한 추가 코드

// 에러 체크
void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		char str[256] = {0,};
		sprintf_s(str, "FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		MessageBoxA(NULL, str, "TEST", MB_OK  );
	}
}

// 팩토리 생성
void InitSound()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&systemS);  // Create the main system object.
	ERRCHECK(result);
	
	result = systemS->init(2, FMOD_INIT_NORMAL, 0); // Initialize FMOD.
	ERRCHECK(result);
}

// 리소스 생성 - 재생하고자 하는 음원 로딩
void LoadSound()
{
	FMOD_RESULT result;


	// 사운드로딩
	result = systemS->createSound("./Resource/test.mp3", FMOD_LOOP_NORMAL, 0, &sound);  // FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
	ERRCHECK(result);
}

// 재생
void PLAYsound()
{
	FMOD_RESULT result;
	result = systemS->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	channel->setVolume(0.5);
	ERRCHECK(result);
}

// 해제 처리
void DeleteSound()
{
	if(sound)
	{
		sound->release();
		sound = NULL;
	}
	if(systemS)
	{
		systemS->release();
		systemS->close();
		systemS = NULL;
	}
}

// 창 이동 샘플
void SetMoveWindow( HWND hWnd, WPARAM wParam )
{
	// 윈도우의 위치와 크기(RECT)를 가져온다.
	RECT rt;
	GetWindowRect(hWnd, &rt);

	int moveOffset = 10;

	switch (wParam)
	{
	case 'W':
		rt.top -= moveOffset;
		rt.bottom -= moveOffset;
		break;
	case 'A':
		rt.left -= moveOffset;
		rt.right -= moveOffset;
		break;
	case 'S':
		rt.top += moveOffset;
		rt.bottom += moveOffset;
		break;
	case 'D':
		rt.left += moveOffset;
		rt.right += moveOffset;
		break;
	default:
		break;
	}

	MoveWindow(hWnd, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, TRUE);
}
