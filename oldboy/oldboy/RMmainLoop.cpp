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

CRMmainLoop::CRMmainLoop(void):
	m_NowTime(0),
	m_PrevTime(0),
	m_ElapsedTime(0),
	m_Fps(0),
	m_FpsCheckTime(0),
	m_SceneType(SCENE_TITLE)
{
	// 1000ms를 60으로 나눠 60Fps를 유지할 수 있도록 함
	m_Fps = 1000 / 60;
}

CRMmainLoop::~CRMmainLoop(void)
{
}

void CRMmainLoop::RunMessageLoop()
{
	MSG msg;
	UINT fps = 0;

	ZeroMemory(&msg, sizeof(msg)); //msg 초기화 함수

	CBandiVideoLibrary		bandiVideoLibrary;
	CBandiVideoDevice*		bandiVideoDevice = NULL;
	CBandiVideoTexture*		bandiVideoTexture = NULL;
	BVL_VIDEO_INFO			bandiVideoLibraryVideoInfo;

	
	if ( FAILED ( bandiVideoLibrary.Create( BANDIVIDEO_DLL_FILE_NAME, NULL, NULL ) ) )
	{
		MessageBox(NULL, L"Error creating BandiVideoLibrary.", L"ERROR!", MB_OK | MB_ICONSTOP);
		DestroyWindow(m_Hwnd);
	}

	if ( FAILED ( bandiVideoLibrary.Open( "./Resource/test.avi", FALSE ) ) )
	{
		MessageBox(NULL, L"Error opening file...", L"ERROR!", MB_OK | MB_ICONSTOP);
		DestroyWindow(m_Hwnd);
	}

	if ( FAILED ( bandiVideoLibrary.GetVideoInfo( bandiVideoLibraryVideoInfo ) ) )
	{
		MessageBox(NULL, L"Error getting video info....", L"ERROR!", MB_OK | MB_ICONSTOP);
		DestroyWindow(m_Hwnd);
	}


	bandiVideoDevice = new CBandiVideoDevice_DX9();

	if ( !bandiVideoDevice || FAILED ( bandiVideoDevice->Open( m_Hwnd ) ) )
	{
		MessageBox(NULL, L"Error opening device...",  L"ERROR!", MB_OK | MB_ICONSTOP);
		DestroyWindow(m_Hwnd);
		
		// if(m_bvd) delete m_bvd;

		SafeDelete( bandiVideoDevice );
	}

	int count=0;
	do
	{
	
		if ( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
		{
			if ( msg.message == WM_QUIT )
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			BVL_STATUS		status;
			bandiVideoLibrary.GetStatus(status);

			if ( status == BVL_STATUS_READY )
			{
				// 재생할 준비가 완료되었다면, 재생 시작
				bandiVideoLibrary.GetVideoInfo( bandiVideoLibraryVideoInfo );
				bandiVideoLibrary.Play();

				if ( bandiVideoTexture == NULL )
				{
					bandiVideoTexture = new CBandiVideoTexture_DX9((CBandiVideoDevice_DX9*)bandiVideoDevice);
					
					if ( !bandiVideoTexture || FAILED( bandiVideoTexture->Open( bandiVideoLibraryVideoInfo.width , bandiVideoLibraryVideoInfo.height ) ) )
					{
						MessageBox(NULL, L"Error opening texture...",  L"ERROR!", MB_OK | MB_ICONSTOP);
						DestroyWindow(m_Hwnd);
						/*
						if(m_bvd) delete m_bvd;
						if(m_bvt) delete m_bvt;
						m_bvd = nullptr;
						m_bvt = nullptr;
						*/

						SafeDelete( bandiVideoDevice );
						SafeDelete( bandiVideoTexture );
					}
				}
			}


			// 새 프레임을 출력할 시간인가?
			if ( bandiVideoLibrary.IsNextFrame() )
			{
				INT		pitch;
				BYTE*	buf = bandiVideoTexture->Lock( pitch );
				if ( buf )
				{
					// Get frame
					BVL_FRAME frame;
					frame.frame_buf = buf;
					frame.frame_buf_size = bandiVideoLibraryVideoInfo.height*pitch;
					frame.pitch = pitch;
					frame.width = bandiVideoLibraryVideoInfo.width;
					frame.height = bandiVideoLibraryVideoInfo.height;
					frame.pixel_format = bandiVideoTexture->GetFormat();

					bandiVideoLibrary.GetFrame(frame, TRUE);

					bandiVideoTexture->Unlock();

					// Show frame
					bandiVideoDevice->StartFrame();
					bandiVideoTexture->Draw( 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y );
					bandiVideoDevice->EndFrame();
					++count;
					
					
				}
			}
			else
			{
				Sleep(1);
			}

			if ( status == BVL_STATUS_PLAYEND )
			{
				printf_s("END! \n");
				break;
			}
			if ( GetAsyncKeyState( VK_A ) & 0x8000 )
			{
				break;
			}
			else
			{
				printf_s( "frame: %d \n", count );
			}
		}
	}
	while(true);	// do~while(true)

	bandiVideoLibrary.Destroy();

	if ( bandiVideoDevice ) 
	{
		bandiVideoDevice->Close();
		// delete m_bvd;
		// m_bvd = nullptr;

		SafeDelete( bandiVideoDevice );
	}

	if ( bandiVideoTexture )
	{
		bandiVideoTexture->Close();
		// delete m_bvt;
		// m_bvt = nullptr;

		SafeDelete( bandiVideoTexture );
	}
	//===================================================================
	

	// fmod 사용하기 fmodex.dll파일이 필요하다.
	CRMsound::GetInstance()->CreateSound();
	CRMsound::GetInstance()->LoadSound("bgm_title_00_01.mp3");
	CRMsound::GetInstance()->LoadSound("Dengue_Fever-Integration.mp3");
	CRMsound::GetInstance()->LoadSound("se1.wav");
	CRMsound::GetInstance()->LoadSound("se2.wav");
	CRMsound::GetInstance()->LoadSound("se3.wav");

	CreateObject();
	// 오브젝트 생성 부분을 리팩토링
	
	CRMsound::GetInstance()->PlaySound("bgm_title_00_01.mp3");

	while ( true )
	{
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) // PeekMessage는 대기 없이 무한 루프 상태로 진행(non blocked function)
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

			if( ( m_NowTime - m_FpsCheckTime ) > 1000 )
			{
				// printf_s("FPS : %d \n", fps);

				m_FpsCheckTime = m_NowTime;
				fps = 0;
			}

			m_ElapsedTime = m_NowTime - m_PrevTime;

			if( m_ElapsedTime == m_Fps )
			{
				// 테스트 
				CRMlabel* testLabel = new CRMlabel();
				testLabel->CreateLabel(L"테스트", L"테스트다옹", L"맑은 고딕", 35.0F );
				testLabel->SetRGBA( 0.8f, 0.5f, 0.3f, 1.f );
				testLabel->SetSceneType( SCENE_TITLE );
				testLabel->SetPosition( 50, 50 );
				
				// 처리 해야 할 내부 로직들을 처리함
				// Update
				CRMobjectManager::GetInstance()->Update();

				CRMinput::GetInstance()->UpdateKeyState();

				CRMrender::GetInstance()->RenderInit();

				// 화면에 대한 처리를 진행
				// Render
				CRMobjectManager::GetInstance()->Render();
				++fps;

				CRMrender::GetInstance()->RenderEnd();
				m_PrevTime = m_NowTime;

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

	testObject = new CRMchildEffectImage();
	testObject->SetObjectType(OBJECT_NOTE_HIT);
	testObject->SetPosition(DEFAULT_POSITION_X, DEFAULT_POSITION_Y);
	testObject->SetSceneType(SCENE_PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_NOTE_HIT);
	
	testObject = new CRMchildEffectImage();
	testObject->SetObjectType(OBJECT_NOTE_HIT);
	testObject->SetPosition(DEFAULT_POSITION_X, DEFAULT_POSITION_Y);
	testObject->SetSceneType(SCENE_PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_NOTE_HIT);
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
		CRMsound::GetInstance()->PlayEffect( "se2.wav" );
	}
	if ( CRMinput::GetInstance()->GetKeyStatusByKey( P1_TARGET2 ) == KEY_DOWN )
	{
		CRMsound::GetInstance()->PlayEffect( "se3.wav" );
	}
	if ( CRMinput::GetInstance()->GetKeyStatusByKey( P2_TARGET1 ) == KEY_DOWN )
	{
		CRMsound::GetInstance()->PlayEffect( "se2.wav" );
	}
	if ( CRMinput::GetInstance()->GetKeyStatusByKey( P2_TARGET2 ) == KEY_DOWN )
	{
		CRMsound::GetInstance()->PlayEffect( "se3.wav" );
	}
}

void CRMmainLoop::TestKeyboard()
{
	if ( ( CRMinput::GetInstance()->GetKeyStatusByKey( P1_TARGET1 ) == KEY_DOWN ) && m_SceneType == SCENE_TITLE )
	{
		GoNextScene();
	}
}

void CRMmainLoop::GoNextScene()
{
	if ( m_SceneType == SCENE_TITLE )
	{
		m_SceneType = SCENE_PLAY;

		CRMsound::GetInstance()->PlaySound("Dengue_Fever-Integration.mp3");
	}
}
