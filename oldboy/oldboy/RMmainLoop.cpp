#include "stdafx.h"
#include "RMmainLoop.h"
#include "RMObjectManager.h"
#include "RMresourceManager.h"
#include "RMrender.h"

#include "RMchildNote.h"
#include "RMchildBGImage.h"

CRMmainLoop* CRMmainLoop::m_pInstance = nullptr;

CRMmainLoop::CRMmainLoop(void):
	m_NowTime(0),
	m_PrevTime(0),
	m_ElapsedTime(0),
	m_Fps(0)
{
	// 1000ms를 60으로 나눠 60Fps를 유지할 수 있도록 함
	m_Fps = 1000/60;

	// fmod 사용하기 fmodex.dll파일이 필요하다.
	CRMsound::GetInstance()->InitSound();
	CRMsound::GetInstance()->LoadSound();
}


CRMmainLoop::~CRMmainLoop(void)
{
	CRMsound::ReleaseInstance();
	CRMobjectManager::ReleaseInstance();
	CRMresourceManager::ReleaseInstance();
	CRMrender::ReleaseInstance();
}


void CRMmainLoop::RunMessageLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); //msg 초기화 함수

	CreateObject();
	// 오브젝트 생성 부분을 리팩토링
	
	CRMsound::GetInstance()->PLAYsound();

	while(true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // PeekMessage는 대기 없이 무한 루프 상태로 진행(non blocked function)
		{
			if ( msg.message == WM_QUIT )
			{
				return;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);	// Wndproc과 연결되어 있음
		}
		else
		{
			m_NowTime = timeGetTime();

			if ( m_PrevTime == 0 )
			{
				m_PrevTime = m_NowTime;
			}

			m_ElapsedTime = m_NowTime - m_PrevTime;

			if(m_ElapsedTime % m_Fps == 0)
			{
				// 처리 해야 할 내부 로직들을 처리함
				// Update
				CRMobjectManager::GetInstance()->Update();
				// 업데이트 주기를 화면 뿌려주는 주기와 동기화 시키기 위해서 이쪽으로 이동시킴
				// 그렇지 않을 경우 오브젝트들 내부에서 스스로 시간 경과를 체크해서
				// 자신이 update 되어야 할 타이밍을 계산하거나 해야 됨

				CRMrender::GetInstance()->RenderInit();

				// 화면에 대한 처리를 진행
				// Render
				CRMobjectManager::GetInstance()->Render();

				CRMrender::GetInstance()->RenderEnd();
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
	// HRESULT hr = S_FALSE;

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= CRMmainLoop::WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= HINST_THISCOMPONENT;
	wcex.hIcon			= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_OLDBOY));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL; // 배경 색상 부분 NULL로 설정
	wcex.lpszMenuName	= NULL;	// 메뉴 생성 부분 NULL로 설정
	wcex.lpszClassName	= L"RhythmMatch";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);


	m_Hwnd = CreateWindow(wcex.lpszClassName, 
						L"Rhythm Match v0.125", 
						WS_OVERLAPPEDWINDOW,
						50,		// 하기 4줄이 화면 시작 좌표 의미 
						50,		//
						1024,	//
						668,	//
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

void CRMmainLoop::CreateObject()
{
	// 이미지 리소스를 불러오려면 렌더가 필요함
	CRMrender::GetInstance()->CreateFactory();
	CRMrender::GetInstance()->CreateRenderTarget();
	// 	// 렌더를 메인루프의 생성자에 못 넣는 이유는?
	// 렌더 쪽에서 메인루프 싱글톤을 호출하므로 메모리 접근 오류 발생!

	// 이미지 리소스 파일 불러오기
	CRMresourceManager::GetInstance()->InitTexture();

	/**********************************************************************************/
	// 화면 출력을 시험 하기 위해 임시로 추가 해 둠
	/**********************************************************************************/
	CRMobject*	testObject = new CRMchildBGImage();
	testObject->SetKey(BG_IMAGE);
	testObject->SetPosition(0, 0);
	CRMobjectManager::GetInstance()->AddObject(testObject);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(400, 0);
	CRMobjectManager::GetInstance()->AddObject(testObject);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(800, 0);
	CRMobjectManager::GetInstance()->AddObject(testObject);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(400, -150);
	CRMobjectManager::GetInstance()->AddObject(testObject);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(800, -150);
	CRMobjectManager::GetInstance()->AddObject(testObject);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(400, -300);
	CRMobjectManager::GetInstance()->AddObject(testObject);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(800, -300);
	CRMobjectManager::GetInstance()->AddObject(testObject);

}
