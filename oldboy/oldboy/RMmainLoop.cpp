#include "stdafx.h"
#include "RMmainLoop.h"
#include "RMObjectManager.h"
#include "RMresourceManager.h"
#include "RMrender.h"

#include "RMchildNote.h"
#include "RMchildBGImage.h"
#include "RMchildShutter.h"

CRMmainLoop* CRMmainLoop::m_pInstance = nullptr;

CRMmainLoop::CRMmainLoop(void):
	m_NowTime(0),
	m_PrevTime(0),
	m_ElapsedTime(0),
	m_Fps(0),
	m_SceneType(TITLE)
{
	// 1000ms를 60으로 나눠 60Fps를 유지할 수 있도록 함
	m_Fps = 1000/60;

	// fmod 사용하기 fmodex.dll파일이 필요하다.
	CRMsound::GetInstance()->InitSound();
	CRMsound::GetInstance()->LoadSound("test.mp3");
	CRMsound::GetInstance()->LoadSound("Dengue_Fever-Integration.mp3");
	CRMsound::GetInstance()->LoadSound("se1.wav");
	CRMsound::GetInstance()->LoadSound("se2.wav");
	CRMsound::GetInstance()->LoadSound("se3.wav");
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
	
	CRMsound::GetInstance()->PLAYsound("test.mp3");

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

			if(m_ElapsedTime % m_Fps == 0) //SM9: 이게 0으로 딱 안떨어지면 어떻할려고??
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

				// test sound
				testSound();

				// test Key
				testKey();

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
						1040,	// 1024 + 16
						700,	// 668 + 32
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
	testObject->SetKey(BG_IMAGE_TITLE);
	testObject->SetPosition(0, 0);
	testObject->SetScene(TITLE);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_1);

	testObject = new CRMchildBGImage();
	testObject->SetKey(BG_IMAGE_PLAY);
	testObject->SetPosition(0, 0);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_1);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(395, 0);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_2);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(910, 0);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_2);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(395, -150);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_2);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(910, -150);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_2);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(395, -300);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_2);
	
	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(910, -300);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_2);

	testObject = new CRMchildShutter();
	testObject->SetKey(SHUTTER_IMAGE);
	testObject->SetPosition(0, -660);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_3);

	testObject = new CRMchildShutter();
	testObject->SetKey(SHUTTER_IMAGE);
	testObject->SetPosition(515, -880);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_3);
}

// ================================================================

int testSoundCount = 0;
void CRMmainLoop::testSound()
{
	
	if(m_SceneType == PLAY)
	{
		++testSoundCount;
	}

	if(testSoundCount==300)
	{
		CRMsound::GetInstance()->PLAYSEsound("se1.wav");
	}
	if(testSoundCount==450)
	{
		CRMsound::GetInstance()->PLAYSEsound("se2.wav");
	}
	if(testSoundCount==540)
	{
		CRMsound::GetInstance()->PLAYSEsound("se3.wav");
	}
	if(testSoundCount==663)
	{
		CRMsound::GetInstance()->PLAYSEsound("se3.wav");
		testSoundCount = 200;
	}

	
}

void CRMmainLoop::testKey()
{

	if(CRMinput::GetInstance()->InputKeyboard() == P1TARGET1)
	{
		// 'A'키 입력을 받은 후 씬이 넘어가고 음악 재생에 문제가 있었던 이유 
		// RMinput.cpp 확인 해 보면 현재 Key Status를 초기화 하지 않았음

		// 그 결과 키가 한 번 눌린 상태면 계속 눌려 있다 라고 인식이 되어서
		// 이 if 구문의 결과가 참으로 인식 되어 계속 내부로 들어옴
		
		// 그래서 하단의 GoNextScene() 메소드를 계속 반복 호출(1/60초에 1회씩 미친듯이...)
		// 그 결과 음악이 1/60초에 한 번씩 계속 반복 시작 되느라 멈춘 것처럼 느껴진 것이고

		// 마우스를 드래그 할 때에는 메인루프 로직이 멈춰 있으니
		// (우리 게임에서는 WM_MOVE나 기타 메시지 처리를 안 하므로 이동처리시 흐름 진행이 안 됨)
		// 하단의 GoNextScene() 메소드 호출이 멈추게 되어서
		// 마치 마우스를 드래그 할 때에만 정상적으로 노래가 나오는 것처럼 느껴진 것임
		
		GoNextScene();
	}
}

void CRMmainLoop::GoNextScene()
{
	if(m_SceneType == TITLE)
	{
		m_SceneType = PLAY;

		CRMsound::GetInstance()->PLAYsound("Dengue_Fever-Integration.mp3");
		// 문맥 의미상 배경 음악 재생을 변경 시작하는 것은 이곳에 배치 되는 것이 맞음
	}
}
