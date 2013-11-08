#include "stdafx.h"
#include "oldboy.h"

#include "RMmainLoop.h"
#include "RMObjectManager.h"
#include "RMresourceManager.h"
#include "RMrender.h"

#include "RMchildNote.h"
#include "RMchildBGImage.h"
#include "RMchildShutter.h"
#include "RMsound.h"
#include "RMJudgeManager.h"
#include "RMchildEffectImage.h"
#include "RMlabel.h"
#include "RMvideoPlayer.h"
#include "RMxmlLoader.h"

CRMmainLoop::CRMmainLoop(void):
	m_NowTime(0),
	m_PrevTime(0),
	m_ElapsedTime(0),
	m_Fps(0),
	m_FpsCheckTime(0),
	m_SceneType(SCENE_OPENING),
	m_Hwnd(NULL)
{
	// 1000ms를 60으로 나눠 60Fps를 유지할 수 있도록 함
	m_Fps = ( 1000 / 60 ) + 1;
}

CRMmainLoop::~CRMmainLoop(void)
{
}

void CRMmainLoop::RunMessageLoop()
{
	MSG msg;
	UINT fps = 0;
	HRESULT hr = S_FALSE;

	ZeroMemory( &msg, sizeof(msg) ); //msg 초기화 함수

	//===================================================================
	// fmod 사용하기 fmodex.dll파일이 필요하다.
	CRMsound::GetInstance()->CreateSound();
	CRMsound::GetInstance()->LoadSound("bgm_title_00_01.mp3");
	CRMsound::GetInstance()->LoadSound("SingleBell.mp3");
	CRMsound::GetInstance()->LoadSound("sound_effect_01_01.wav");
	CRMsound::GetInstance()->LoadSound("sound_effect_02_01.wav");

	//===================================================================
	// 동영상 출력 부분
	hr = CRMvideoPlayer::GetInstance()->CreateFactory();
	
	if ( hr == S_OK )
	{
		CRMvideoPlayer::GetInstance()->StartVideo();
	}
	else
	{
		GoNextScene();
		// 동영상 재생을 위한 초기화에 실패 했을 경우 동영상 재생 패스
	}

	CreateObject();
	// 오브젝트 생성 부분을 리팩토링
	
	while ( true )
	{
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) // PeekMessage는 대기 없이 무한 루프 상태로 진행(non blocked function)
		{
			if ( msg.message == WM_QUIT )
			{
				CRMvideoPlayer::GetInstance()->DestoryFactory();
				return;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);	// Wndproc과 연결되어 있음
		}
		else
		{
			if ( m_SceneType == SCENE_OPENING )
			{
				CRMvideoPlayer::GetInstance()->RenderVideo();

				CRMinput::GetInstance()->UpdateKeyState();
				if ( CRMinput::GetInstance()->GetKeyStatusByKey( P1_TARGET1 ) == KEY_UP )
				{
					CRMvideoPlayer::GetInstance()->DestoryFactory();
					GoNextScene();
				}
				continue;
			}

			m_NowTime = timeGetTime();

			if ( m_PrevTime == 0 )
			{
				m_PrevTime = m_NowTime;
			}

			/*

			// FPS 출력용 계산

			if( ( m_NowTime - m_FpsCheckTime ) > 1000 )
			{
				printConsole("FPS : %d \n", fps);
				m_FpsCheckTime = m_NowTime;
				fps = 0;
			}
			*/

			m_ElapsedTime = m_NowTime - m_PrevTime;

			if( m_ElapsedTime == m_Fps )
			{
				// 테스트 
				/*
				CRMlabel* testLabel = new CRMlabel();
				testLabel->CreateLabel(L"테스트", L"테스트 라벨입니다.", L"맑은 고딕", 35.0F );
				testLabel->SetRGBA( 0.8f, 0.5f, 0.3f, 1.f );
				testLabel->SetSceneType( SCENE_TITLE );
				testLabel->SetPosition( 50, 50 );
				*/

				// 처리 해야 할 내부 로직들을 처리함
				// Update
				CRMobjectManager::GetInstance()->Update();

				CRMrender::GetInstance()->RenderInit();

				// 화면에 대한 처리를 진행
				// Render
				CRMobjectManager::GetInstance()->Render();
				++fps;

				CRMrender::GetInstance()->RenderEnd();
				m_PrevTime = m_NowTime;


				// 소리 밀림을 방지하기 위해 UpdateKeyState와 TestSound를 묶어 둠
				CRMinput::GetInstance()->UpdateKeyState();

				// test sound
				TestSound();

				// test Key
				TestKeyboard();
				CRMjudgeManager::GetInstance()->JudgeNote();
			}

			if ( m_ElapsedTime > m_Fps )
			{
				m_PrevTime = m_NowTime;
			}
		}
	}
}

HRESULT CRMmainLoop::CreateMainLoopWindow()
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
						SCREEN_SIZE_X,	// 1024 + 16
						SCREEN_SIZE_Y,	// 668 + 32
						NULL, 
						NULL, 
						wcex.hInstance, 
						NULL);

	if ( !m_Hwnd )
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
	switch ( message )
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

void CRMmainLoop::CreateObject()
{
	// 이미지 리소스를 불러오려면 렌더가 필요함
	CRMrender::GetInstance()->CreateFactory();
	CRMrender::GetInstance()->CreateRenderTarget();
	// 렌더를 메인루프의 생성자에 못 넣는 이유는?
	// 렌더 쪽에서 메인루프 싱글톤을 호출하므로 메모리 접근 오류 발생!

	// 이미지 리소스 파일 불러오기
	CRMresourceManager::GetInstance()->CreateFactory();
	CRMresourceManager::GetInstance()->CreateTexture();

	/**********************************************************************************/
	// 화면 출력을 시험 하기 위해 임시로 추가 해 둠
	/**********************************************************************************/
	CRMobject*	testObject = new CRMchildBGImage();
	testObject->SetObjectType(OBJECT_BG_IMAGE_TITLE);
	testObject->SetPosition(0, 0);
	testObject->SetSceneType(SCENE_TITLE);
	CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_BACKGROUND);

	testObject = new CRMchildBGImage();
	testObject->SetObjectType(OBJECT_BG_IMAGE_PLAY);
	testObject->SetPosition(0, 0);
	testObject->SetSceneType(SCENE_PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_BACKGROUND);
	
	for ( int i = 0 ; i < 100 ; ++i )
	{
		testObject = new CRMchildNote();
		testObject->SetObjectType(OBJECT_NOTE_NORMAL_1);
		testObject->SetPosition( DEFAULT_POSITION_X, DEFAULT_POSITION_Y );
		testObject->SetSceneType(SCENE_PLAY);
		CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_MEMORY_POOL);
	}

	testObject = new CRMchildShutter();
	testObject->SetObjectType(OBJECT_SHUTTER);
	testObject->SetPosition(0, -670);
	testObject->SetSceneType(SCENE_PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_SHUTTER);

	testObject = new CRMchildShutter();
	testObject->SetObjectType(OBJECT_SHUTTER);
	testObject->SetPosition(515, -890);
	testObject->SetSceneType(SCENE_PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_SHUTTER);

	for ( int i = 0 ; i < 20 ; ++ i )
	{
		testObject = new CRMchildEffectImage();
		testObject->SetObjectType(OBJECT_NOTE_HIT);
		testObject->SetPosition(DEFAULT_POSITION_X, DEFAULT_POSITION_Y);
		testObject->SetSceneType(SCENE_PLAY);
		CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_NOTE_HIT);
	}
}

// ================================================================

void CRMmainLoop::TestSound()
{
	
	if ( m_SceneType != SCENE_PLAY )
	{
		return;
	}

	if ( CRMinput::GetInstance()->GetKeyStatusByKey( P1_ATTACK ) == KEY_DOWN )
	{
		int testRand1 = rand();
		if( testRand1%2 == 0 )
		{
			CRMjudgeManager::GetInstance()->StartNote( PLAYER_ONE , OBJECT_NOTE_NORMAL_1 );
		}
		else
		{
			CRMjudgeManager::GetInstance()->StartNote( PLAYER_ONE , OBJECT_NOTE_NORMAL_2 );
		}
	}
	if ( CRMinput::GetInstance()->GetKeyStatusByKey( P2_ATTACK ) == KEY_DOWN )
	{
		int testRand2 = rand();
		if( testRand2%2 == 0 )
		{
			CRMjudgeManager::GetInstance()->StartNote( PLAYER_TWO , OBJECT_NOTE_NORMAL_1 );
		}
		else
		{
			CRMjudgeManager::GetInstance()->StartNote( PLAYER_TWO , OBJECT_NOTE_NORMAL_2 );
		}
	}
	if ( CRMinput::GetInstance()->GetKeyStatusByKey( P1_TARGET1 ) == KEY_DOWN )
	{
		CRMsound::GetInstance()->PlayEffect( "sound_effect_01_01.wav" );
	}
	if ( CRMinput::GetInstance()->GetKeyStatusByKey( P1_TARGET2 ) == KEY_DOWN )
	{
		CRMsound::GetInstance()->PlayEffect( "sound_effect_02_01.wav" );
	}
	if ( CRMinput::GetInstance()->GetKeyStatusByKey( P2_TARGET1 ) == KEY_DOWN )
	{
		CRMsound::GetInstance()->PlayEffect( "sound_effect_01_01.wav" );
	}
	if ( CRMinput::GetInstance()->GetKeyStatusByKey( P2_TARGET2 ) == KEY_DOWN )
	{
		CRMsound::GetInstance()->PlayEffect( "sound_effect_02_01.wav" );
	}
}

void CRMmainLoop::TestKeyboard()
{
	if ( ( CRMinput::GetInstance()->GetKeyStatusByKey( P1_TARGET1 ) == KEY_DOWN ) && m_SceneType == SCENE_TITLE )
	{
		GoNextScene();
		CRMxmlLoader::GetInstance()->TestXML();
	}
}

void CRMmainLoop::GoNextScene()
{
	if ( m_SceneType == SCENE_OPENING )
	{
		m_SceneType = SCENE_TITLE;

		CRMsound::GetInstance()->PlaySound("bgm_title_00_01.mp3");
		return;
	}

	if ( m_SceneType == SCENE_TITLE )
	{
		m_SceneType = SCENE_PLAY;

		CRMsound::GetInstance()->PlaySound("SingleBell.mp3");
		return;
	}
}
