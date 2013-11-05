#include "stdafx.h"
#include "oldboy.h"
#include "RMimage.h"
#include "RMresourceManager.h"

CRMresourceManager::CRMresourceManager(void):
	m_pWICFactory(nullptr)
{
	m_TextureMap.clear();
}


CRMresourceManager::~CRMresourceManager(void)
{
	SafeRelease(m_pWICFactory);

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
	HRESULT hr = S_FALSE;

	CRMimage* texture;

	texture = new CRMimage();
	hr = texture->CreateImage( L"./Resource/image_bg_00_01.png" );
	CheckError(hr);
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_BG_IMAGE_TITLE] = texture;
	}
	else
	{
		m_TextureMap[OBJECT_BG_IMAGE_TITLE] = nullptr;
		SafeDelete(texture);
	}

	texture = new CRMimage();
	hr = texture->CreateImage( L"./Resource/image_bg_01_01.png" );
	CheckError(hr);
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_BG_IMAGE_PLAY] = texture;
	}
	else
	{
		m_TextureMap[OBJECT_BG_IMAGE_PLAY] = nullptr;
		SafeDelete(texture);
	}

	texture = new CRMimage();
	hr = texture->CreateImage( L"./Resource/image_sh_01_01.png" );
	CheckError(hr);
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_SHUTTER] = texture;
	}
	else
	{
		m_TextureMap[OBJECT_SHUTTER] = nullptr;
		SafeDelete(texture);
	}
	
	texture = new CRMimage();
	hr = texture->CreateImage( L"./Resource/image_nt_01_01.png" );
	CheckError(hr);
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_NOTE_NORMAL_1] = texture;
	}
	else
	{
		m_TextureMap[OBJECT_NOTE_NORMAL_1] = nullptr;
		SafeDelete(texture);
	}

	texture = new CRMimage();
	hr = texture->CreateImage( L"./Resource/image_nt_02_01.png" );
	CheckError(hr);
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_NOTE_NORMAL_2] = texture;
	}
	else
	{
		m_TextureMap[OBJECT_NOTE_NORMAL_2] = nullptr;
		SafeDelete(texture);
	}

	texture = new CRMimage();
	hr = texture->CreateImage( L"./Resource/image_nt_01_02.png" );
	CheckError(hr);
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_NOTE_HIT] = texture;
	}
	else
	{
		m_TextureMap[OBJECT_NOTE_HIT] = nullptr;
		SafeDelete(texture);
	}

	return hr;
}

void CRMresourceManager::CheckError(HRESULT hr)
{
	if ( hr != S_OK )
	{
#ifdef DEBUG
		printf_s("Image Loading Error! (%d) \n", hr);
#endif // DEBUG
	}
}
