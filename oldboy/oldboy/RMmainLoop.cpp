#include "stdafx.h"
#include "RMmainLoop.h"

CRMmainLoop* CRMmainLoop::m_pInstance = nullptr;

CRMmainLoop::CRMmainLoop(void):
	m_NowTime(0),
	m_PrevTime(0),
	m_ElapsedTime(0),
	m_Fps(0)
{
	//1000ms를 60으로 나눠 60Fps를 유지할 수 있도록 함
	m_Fps = 1000/60;
}


CRMmainLoop::~CRMmainLoop(void)
{
}


void CRMmainLoop::RunMessageLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); //msg 초기화 함수

	while(true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // PeekMessage는 대기 없이 무한 루프 상태로 진행(non blocked function)
		{
			if ( msg.message == WM_QUIT )
			{
				return;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg); //Wndproc과 연결되어 있음
		}
		else
		{
			// 처리 해야 할 내부 로직들을 처리함(objectManager -> update)
			// CRMRender::GetInstance()->MovePosition();
			// 임시로 추가함

			m_NowTime = timeGetTime();

			if ( m_PrevTime == 0 )
			{
				m_PrevTime = m_NowTime;
			}

			m_ElapsedTime = m_NowTime - m_PrevTime;

			if(m_ElapsedTime % m_Fps == 0)
			{
				//화면에 대한 처리를 진행(objectManager -> render)
// 				CRMRender::GetInstance()->Render();
// 				ValidateRect(m_HWnd, NULL);

				m_PrevTime = m_NowTime;
			}

			if(m_ElapsedTime > m_Fps)
			{
				m_PrevTime = m_NowTime;
			}
		}
	}
}


HRESULT CRMmainLoop::Init()
{
	//HRESULT hr = S_FALSE;

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= HINST_THISCOMPONENT;
	wcex.hIcon			= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_OLDBOY));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_OLDBOY);
	wcex.lpszClassName	= L"RhythmMatch";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);


	m_Hwnd = CreateWindow(wcex.lpszClassName, 
						L"Rhythm Match v0.125", 
						WS_OVERLAPPEDWINDOW,
						50,  //하기 4줄이 화면 시작 좌표 의미 
						50, //
						1024, //
						668, //
						NULL, 
						NULL, 
						wcex.hInstance, 
						NULL);

	if (!m_Hwnd)
	{
		return S_FALSE;
	}

	ShowWindow(m_Hwnd, SW_SHOWNORMAL);
	UpdateWindow(m_Hwnd);

	return S_OK;
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
LRESULT CALLBACK CRMmainLoop::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	
	case WM_CREATE:
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

CRMmainLoop* CRMmainLoop::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new CRMmainLoop();
	}
	return m_pInstance;
}

void CRMmainLoop::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
