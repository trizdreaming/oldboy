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


HRESULT CRMresourceManager::CreateTexture()
{
	InitializeMap();

	HRESULT hr = S_FALSE;
	CRMimage* texture;

	texture = new CRMimage();
	hr = texture->CreateImage( BG_IMAGE_DEFAULT );
	LogError(hr);
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
	LogError(hr);
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
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageBackground() ) );
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
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageShutter() ) );
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
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageNote1() ) );
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
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageNote2() ) );
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
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageNoteEffect() ) );
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
	std::string str = MUSIC_FOLDER;
	str.append( folderName );
	str.append( FOLDER_SLASH );
	str.append( resourceName );

	std::wstring wstr(str.length(),L' ');
	copy(str.begin(),str.end(),wstr.begin());

	return wstr;
}
