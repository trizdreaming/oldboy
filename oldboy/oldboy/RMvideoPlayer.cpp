#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMvideoPlayer.h"
#include "RMmainLoop.h"

CRMvideoPlayer::CRMvideoPlayer(void) :
	m_BandiVideoDevice(nullptr),
	m_BandiVideoTexture(nullptr),
	m_Hwnd(NULL),
	m_Count(0),
	m_Status(BVL_STATUS_CLOSED),
	m_Pitch(0),
	m_Buffer(nullptr)
{
}


CRMvideoPlayer::~CRMvideoPlayer(void)
{
}

HRESULT CRMvideoPlayer::CreateFactory()
{
	m_Hwnd = CRMmainLoop::GetInstance()->GetHwnd();

	if ( FAILED ( m_BandiVideoLibrary.Create( BANDIVIDEO_DLL_FILE_NAME, NULL, NULL ) ) )
	{
		MessageBox( NULL, L"Error creating BandiVideoLibrary.", L"ERROR!", MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}

	if ( FAILED ( m_BandiVideoLibrary.Open( "./Resource/sample.avi", FALSE ) ) )
	{
		MessageBox( NULL, L"Error opening file...", L"ERROR!", MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}

	if ( FAILED ( m_BandiVideoLibrary.GetVideoInfo( m_BandiVideoLibraryVideoInfo ) ) )
	{
		MessageBox( NULL, L"Error getting video info....", L"ERROR!", MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}

	m_BandiVideoDevice = new CBandiVideoDevice_DX9();

	if ( !m_BandiVideoDevice || FAILED ( m_BandiVideoDevice->Open( m_Hwnd ) ) )
	{
		MessageBox( NULL, L"Error opening device...",  L"ERROR!", MB_OK | MB_ICONSTOP );
		SafeDelete( m_BandiVideoDevice );

		return S_FALSE;
	}

	m_BandiVideoTexture = new CBandiVideoTexture_DX9( (CBandiVideoDevice_DX9* ) m_BandiVideoDevice );
	
	if ( !m_BandiVideoTexture || FAILED( m_BandiVideoTexture->Open( m_BandiVideoLibraryVideoInfo.width , m_BandiVideoLibraryVideoInfo.height ) ) )
	{
		MessageBox(NULL, L"Error opening texture...",  L"ERROR!", MB_OK | MB_ICONSTOP);
		DestroyWindow(m_Hwnd);
		
		SafeDelete( m_BandiVideoDevice );
		SafeDelete( m_BandiVideoTexture );

		return S_FALSE;
	}

	return S_OK;
}

void CRMvideoPlayer::DestoryFactory()
{
	m_BandiVideoLibrary.Destroy();
	
	if ( m_BandiVideoDevice ) 
	{
		m_BandiVideoDevice->Close();
		SafeDelete( m_BandiVideoDevice );
	}

	if ( m_BandiVideoTexture )
	{
		m_BandiVideoTexture->Close();
		SafeDelete( m_BandiVideoTexture );
	}
}

void CRMvideoPlayer::StartVideo()
{
	m_BandiVideoLibrary.GetStatus( m_Status );

	// 재생할 준비가 완료되었다면, 재생 시작
	if ( m_Status == BVL_STATUS_READY )
	{
		m_BandiVideoLibrary.GetVideoInfo( m_BandiVideoLibraryVideoInfo );
		m_BandiVideoLibrary.Play();
	}
}

void CRMvideoPlayer::RenderVideo()
{
	m_BandiVideoLibrary.GetStatus( m_Status );

	if ( m_BandiVideoLibrary.IsNextFrame() )
	{
		m_Buffer = m_BandiVideoTexture->Lock( m_Pitch );

		if ( m_Buffer )
		{
			// Get frame
			m_Frame.frame_buf = m_Buffer;
			m_Frame.frame_buf_size = m_BandiVideoLibraryVideoInfo.height * m_Pitch;
			m_Frame.pitch = m_Pitch;
			m_Frame.width = m_BandiVideoLibraryVideoInfo.width;
			m_Frame.height = m_BandiVideoLibraryVideoInfo.height;
			m_Frame.pixel_format = m_BandiVideoTexture->GetFormat();

			m_BandiVideoLibrary.GetFrame(m_Frame, TRUE);

			m_BandiVideoTexture->Unlock();

			// Show frame
			m_BandiVideoDevice->StartFrame();
			m_BandiVideoTexture->Draw( 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y );
			m_BandiVideoDevice->EndFrame();
			++m_Count;
		}
		else
		{
			m_BandiVideoTexture->Unlock();
		}		
	}
	else
	{
		Sleep(0);
	}

	printConsole( "frame: %d \n", m_Count );

	if ( m_Status == BVL_STATUS_PLAYEND )
	{
		printConsole("END! \n");
		
		DestoryFactory();
		CRMmainLoop::GetInstance()->GoNextScene();
	}

}