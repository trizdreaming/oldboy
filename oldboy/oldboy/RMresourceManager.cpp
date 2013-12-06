#include "stdafx.h"
#include "RMdefine.h"
#include "RMconst.h"
#include "RMmacro.h"
#include "RMresourceManager.h"
#include "RMimage.h"
#include "RMxmlLoader.h"
#include "RMmusicData.h"

CRMresourceManager::CRMresourceManager(void):
	m_pWICFactory(nullptr)
{
}


CRMresourceManager::~CRMresourceManager(void)
{
	SafeRelease(m_pWICFactory);

	InitializeArray();
}


void CRMresourceManager::InitializeArray()
{
	for ( auto& toBeDelete : m_TextureArray )
	{
		SafeDelete( toBeDelete );
	}
}

void CRMresourceManager::InitializeAlbum()
{
	if ( m_TextureArray[OBJECT_ALBUM_IMAGE] != nullptr )
	{
		SafeDelete( m_TextureArray[OBJECT_ALBUM_IMAGE] );
	}
}

//////////////////////////////////////////////////////////////////////////
//CLSID_WICImagingFactory는 1, 2가 나뉘어져 있음
//각 PC에 따라서 구동되는 것이 다르기 때문에 해당 내용에 대해서 확인하는 방어 코드 작성
//////////////////////////////////////////////////////////////////////////

HRESULT CRMresourceManager::CreateFactory()
{
	HRESULT hr = S_FALSE;

	if ( m_pWICFactory == nullptr )
	{
		hr = CoCreateInstance( CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory) );

		if ( hr == REGDB_E_CLASSNOTREG )
		{
			hr = CoCreateInstance( CLSID_WICImagingFactory1, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory) );

			if ( hr == REGDB_E_CLASSNOTREG )
			{
				hr = CoCreateInstance( CLSID_WICImagingFactory2, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory) );
			}
		}

	}

	return hr;
}


// 기본 Resource폴더의 텍스쳐 로드
HRESULT CRMresourceManager::CreateTexture()
{
	InitializeArray();
	
	HRESULT hr = S_FALSE;
	CRMimage* texture = new CRMimage();

	hr = TextureMaker( BG_IMAGE_TITLE, OBJECT_BG_IMAGE_TITLE );
	hr = TextureMaker( BG_IMAGE_SELECT, OBJECT_BG_IMAGE_SELECT );
	hr = TextureMaker( BG_IMAGE_RESULT, OBJECT_BG_IMAGE_RESULT );

	//////////////////////////////////////////////////////////////////////////
	//pause
	//////////////////////////////////////////////////////////////////////////
	hr = TextureMaker( PAUSE_IMAGE_PLAY_CANCEL, OBJECT_PAUSE_IMAGE_PLAY_CANCEL );
	hr = TextureMaker( PAUSE_IMAGE_PLAY_OK, OBJECT_PAUSE_IMAGE_PLAY_OK );
	hr = TextureMaker( PAUSE_IMAGE_TITLE_CANCEL, OBJECT_PAUSE_IMAGE_TITLE_CANCEL );
	hr = TextureMaker( PAUSE_IMAGE_TITLE_OK, OBJECT_PAUSE_IMAGE_TITLE_OK );

	//////////////////////////////////////////////////////////////////////////
	//이하 플레이 화면
	//////////////////////////////////////////////////////////////////////////
	hr = TextureMaker( PLAY_IMAGE_JUDGE_RING, OBJECT_JUDGE_RING );
	hr = TextureMaker( PLAY_IMAGE_BLUE_GAUGE, OBJECT_GAUGE_2P );
	hr = TextureMaker( PLAY_IMAGE_RED_GAUGE, OBJECT_GAUGE_1P );
	


	//////////////////////////////////////////////////////////////////////////
	// 아이템 이미지 리소스 추가
	//////////////////////////////////////////////////////////////////////////
	
	// Item_T1_Duplicate_Color
	hr = TextureMaker( L"./Resource/itemSet/Item_T1_Duplicate_Color.png", OBJECT_ITEM_T1_DUPLICATE_COLOR );
	// Item_T1_Duplicate_Gray
	hr = TextureMaker( L"./Resource/itemSet/Item_T1_Duplicate_Gray.png", OBJECT_ITEM_T1_DUPLICATE_GRAY );
	// Item_T1_Mist_Color
	hr = TextureMaker( L"./Resource/itemSet/Item_T1_Cloud_Color.png", OBJECT_ITEM_T1_MIST_COLOR );
	// Item_T1_Mist_Gray
	hr = TextureMaker( L"./Resource/itemSet/Item_T1_Cloud_Gray.png", OBJECT_ITEM_T1_MIST_GRAY );
	// Item_T1_Rest_Color
	hr = TextureMaker( L"./Resource/itemSet/Item_T1_ScoreUp_Gray.png", OBJECT_ITEM_T1_SCORE_UP_COLOR );
	// Item_T1_Rest_Gray
	hr = TextureMaker( L"./Resource/itemSet/Item_T1_ScoreUp_Gray.png", OBJECT_ITEM_T1_SCORE_UP_GRAY );
	// Item_T2_Barrier_Color
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_Barrier_Color.png", OBJECT_ITEM_T2_BARRIER_COLOR );
	// Item_T2_Barrier_Gray
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_Barrier_Gray.png", OBJECT_ITEM_T2_BARRIER_GRAY );
	// Item_T2_Delay_Color
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_Delay_Color.png", OBJECT_ITEM_T2_DELAY_COLOR );
	// Item_T2_Delay_Gray
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_Delay_Gray.png", OBJECT_ITEM_T2_DELAY_GRAY );
	// Item_T2_GaugeClear_Color
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_GaugeClear_Color.png", OBJECT_ITEM_T2_GAUGE_CLEAR_COLOR );
	// Item_T2_GaugeClear_Gray
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_GaugeClear_Gray.png", OBJECT_ITEM_T2_GAUGE_CLEAR_GRAY );
	// Item_T2_Rotate_Color
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_Rotate_Color.png", OBJECT_ITEM_T2_ROTATE_COLOR );
	// Item_T2_Rotate_Gray
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_Rotate_Gray.png", OBJECT_ITEM_T2_ROTATE_GRAY );
	// Item_T3_Recovery_Color
	hr = TextureMaker( L"./Resource/itemSet/Item_T3_Recovery_Color.png", OBJECT_ITEM_T3_RECOVERY_COLOR );
	// Item_T3_Recovery_Gray
	hr = TextureMaker( L"./Resource/itemSet/Item_T3_Recovery_Gray.png", OBJECT_ITEM_T3_RECOVERY_GRAY );
	// Item_T3_Reverse_Color
	hr = TextureMaker( L"./Resource/itemSet/Item_T3_Reverse_Color.png", OBJECT_ITEM_T3_REVERSE_COLOR );
	// Item_T3_Reverse_Gray
	hr = TextureMaker( L"./Resource/itemSet/Item_T3_Reverse_Gray.png", OBJECT_ITEM_T3_REVERSE_GRAY );


	//////////////////////////////////////////////////////////////////////////
	//아이템 카드 발동
	//////////////////////////////////////////////////////////////////////////
	hr = TextureMaker( L"./Resource/cardSet/card.png", OBJECT_ITEM_CARD );

	return hr;
}

HRESULT CRMresourceManager::TextureMaker( const std::wstring& path, ObjectType type )
{
	HRESULT hr = S_FALSE;
	CRMimage* texture = new CRMimage();
	hr = texture->CreateImage( path );

	if ( hr == S_OK )
	{
		m_TextureArray[type] = texture;
		return hr;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureArray[type] = nullptr;
		SafeDelete(texture);

		return hr;
	}
}

HRESULT CRMresourceManager::CreateTexture( const std::string& folderName )
{
	
	HRESULT hr = S_FALSE;
	CRMimage* texture;

	// 기본 자원 로드
	hr = CreateTexture();
	if ( hr == S_FALSE )
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		InitializeArray();
		return hr;
	}
	

	// 곡마다 바뀌는 정보 로드

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageBackground() ) );
	
	if ( hr == S_OK )
	{
		m_TextureArray[OBJECT_BG_IMAGE_PLAY] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureArray[OBJECT_BG_IMAGE_PLAY] = nullptr;
		InitializeArray();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageShutter() ) );
	
	if ( hr == S_OK )
	{
		m_TextureArray[OBJECT_SHUTTER] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureArray[OBJECT_SHUTTER] = nullptr;
		InitializeArray();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageNote1() ) );
	
	if ( hr == S_OK )
	{
		m_TextureArray[OBJECT_NOTE_NORMAL_1] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureArray[OBJECT_NOTE_NORMAL_1] = nullptr;
		InitializeArray();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageNote2() ) );
	
	if ( hr == S_OK )
	{
		m_TextureArray[OBJECT_NOTE_NORMAL_2] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureArray[OBJECT_NOTE_NORMAL_2] = nullptr;
		InitializeArray();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageNoteEffect() ) );
	
	if ( hr == S_OK )
	{
		m_TextureArray[OBJECT_NOTE_HIT] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureArray[OBJECT_NOTE_HIT] = nullptr;
		InitializeArray();

		return hr;
	}

	return hr;
}


HRESULT CRMresourceManager::CreateTextureAlbum( const std::string& folderName )
{
	InitializeAlbum();

	HRESULT hr = S_FALSE;
	CRMimage* texture;

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageAlbum() ) );
	
	if ( hr == S_OK )
	{
		m_TextureArray[OBJECT_ALBUM_IMAGE] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		InitializeAlbum();
		return hr;
	}

	return hr;
}

std::wstring CRMresourceManager::GetFilePath( const std::string& folderName, const std::string& resourceName ) const
{
	std::string str = MUSIC_FOLDER;
	str.append( folderName );
	str.append( FOLDER_SLASH );
	str.append( resourceName );

	std::wstring wstr(str.length(),L' ');
	copy(str.begin(),str.end(),wstr.begin());

	return wstr;
}

