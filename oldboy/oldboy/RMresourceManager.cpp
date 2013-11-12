#include "stdafx.h"
#include "oldboy.h"
#include "RMimage.h"
#include "RMresourceManager.h"
#include "RMxmlLoader.h"
#include "RMmusicData.h"

CRMresourceManager::CRMresourceManager(void):
	m_pWICFactory(nullptr)
{
	m_TextureMap.clear();
}


CRMresourceManager::~CRMresourceManager(void)
{
	SafeRelease(m_pWICFactory);

	InitializeMap();
}


void CRMresourceManager::InitializeMap()
{
	for ( auto& iter : m_TextureMap )
	{
		auto toBeDelete = iter.second;
		SafeDelete( toBeDelete );
	}
	m_TextureMap.clear();
}


HRESULT CRMresourceManager::CreateFactory()
{
	HRESULT hr = S_FALSE;

	if ( m_pWICFactory == nullptr )
	{
		hr = CoCreateInstance( CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory) );
	}

	return hr;
}


HRESULT CRMresourceManager::CreateTexture()
{
	InitializeMap();

	HRESULT hr = S_FALSE;
	CRMimage* texture;

	texture = new CRMimage();
	hr = texture->CreateImage( BG_IMAGE_DEFAULT );
	LogError(hr); //SM9: 과도한 엔지니어링.. 에러시 로그 찍는게 간단한거면 아래의 else구문에 넣는것이 더 보기 좋다.
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_BG_IMAGE_TITLE] = texture;
	}
	else
	{
		m_TextureMap[OBJECT_BG_IMAGE_TITLE] = nullptr;
		SafeDelete(texture);
	}
	return hr;
}

HRESULT CRMresourceManager::CreateTexture( const std::string& folderName )
{
	InitializeMap();

	HRESULT hr = S_FALSE;
	CRMimage* texture;

	texture = new CRMimage();
	hr = texture->CreateImage( BG_IMAGE_DEFAULT );
	LogError(hr); //SM9: 마찬가지
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_BG_IMAGE_TITLE] = texture;
	}
	else
	{
		m_TextureMap[OBJECT_BG_IMAGE_TITLE] = nullptr;
		InitializeMap();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, *(CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageBackground() ) ) );
	LogError(hr);
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_BG_IMAGE_PLAY] = texture;
	}
	else
	{
		m_TextureMap[OBJECT_BG_IMAGE_PLAY] = nullptr;
		InitializeMap();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, *(CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageShutter() ) ) );
	LogError(hr);
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_SHUTTER] = texture;
	}
	else
	{
		m_TextureMap[OBJECT_SHUTTER] = nullptr;
		InitializeMap();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, *(CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageNote1() ) ) );
	LogError(hr);
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_NOTE_NORMAL_1] = texture;
	}
	else
	{
		m_TextureMap[OBJECT_NOTE_NORMAL_1] = nullptr;
		InitializeMap();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, *(CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageNote2() ) ) );
	LogError(hr);
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_NOTE_NORMAL_2] = texture;
	}
	else
	{
		m_TextureMap[OBJECT_NOTE_NORMAL_2] = nullptr;
		InitializeMap();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, *(CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageNoteEffect() ) ) );
	LogError(hr);
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_NOTE_HIT] = texture;
	}
	else
	{
		m_TextureMap[OBJECT_NOTE_HIT] = nullptr;
		InitializeMap();

		return hr;
	}

	return hr;
}

void CRMresourceManager::LogError(HRESULT hr)
{
	if ( hr != S_OK )
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
	}
}

std::wstring CRMresourceManager::GetFilePath( const std::string& folderName, const std::string& resourceName )
{
	//SM9: 왜? ascii str로 선언하고 리소스 위치 붙이고 유니코드 str로 반환하지? 
	// 스트링을 이렇게 막 혼용해서 쓰지 말고 웬만하면 모두 통일할 것 unicode가 쓰이면 모두 unicode. 
	// unicode가 전혀 쓰이지 않는다면, ascii로 써도 상관 없음.

	std::string str = MUSIC_FOLDER;
	str.append( folderName );
	str.append( FOLDER_SLASH );
	str.append( resourceName );

	std::wstring wstr(str.length(),L' ');
	copy(str.begin(),str.end(),wstr.begin());

	return wstr;
}
