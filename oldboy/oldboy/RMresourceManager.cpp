#include "stdafx.h"
#include "RMresourceManager.h"

CRMresourceManager*	CRMresourceManager::m_pInstance = nullptr;

CRMresourceManager::CRMresourceManager(void):
	m_pWICFactory(nullptr)
{
	CreateFactory(); //SM9 생성자에서는 에러 핸들링 가능성이 있는 함수들은 쓰지 말 것.
	m_TextureMap.clear();
}


CRMresourceManager::~CRMresourceManager(void)
{
	SafeRelease(m_pWICFactory);

	for(auto &iter = m_TextureMap.begin(); iter != m_TextureMap.end(); ++iter) //SM9: for (auto& iter : m_TextureMap ) 처럼 해도 된다.
	{
		SafeDelete(iter->second);
	}
	m_TextureMap.clear();
}

HRESULT CRMresourceManager::CreateFactory()
{
	HRESULT hr = S_FALSE;

	if(m_pWICFactory == nullptr)
	{
		hr = CoCreateInstance( CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory) );
	}

	return hr;
}


HRESULT CRMresourceManager::InitTexture()
{
	HRESULT hr = S_FALSE;

	CRMimage* texture;

	texture = new CRMimage();
	hr = texture->Init( L"./Resource/image_bg_00_01.png" );
	ErrorCheck(hr);
	if(hr == S_OK)
	{
		m_TextureMap[BG_IMAGE_TITLE] = texture;
	}
	else
	{
		m_TextureMap[BG_IMAGE_TITLE] = nullptr;
		SafeDelete(texture);
	}

	texture = new CRMimage();
	hr = texture->Init( L"./Resource/image_bg_01_01.png" );
	ErrorCheck(hr);
	if(hr == S_OK)
	{
		m_TextureMap[BG_IMAGE_PLAY] = texture;
	}
	else
	{
		m_TextureMap[BG_IMAGE_PLAY] = nullptr;
		SafeDelete(texture);
	}

	texture = new CRMimage();
	hr = texture->Init( L"./Resource/image_sh_temp1.png" );
	ErrorCheck(hr);
	if(hr == S_OK)
	{
		m_TextureMap[SHUTTER_IMAGE] = texture;
	}
	else
	{
		m_TextureMap[SHUTTER_IMAGE] = nullptr;
		SafeDelete(texture);
	}
	
	texture = new CRMimage();
	hr = texture->Init( L"./Resource/image_nt_01_01.png" );
	ErrorCheck(hr);
	if(hr == S_OK)
	{
		m_TextureMap[NOTE_NORMAL_1] = texture;
	}
	else
	{
		m_TextureMap[NOTE_NORMAL_1] = nullptr;
		SafeDelete(texture);
	}

	return hr;
}

CRMresourceManager* CRMresourceManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new CRMresourceManager();
	}

	return m_pInstance;
}

void CRMresourceManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CRMresourceManager::ErrorCheck(HRESULT hr)
{
	if (hr != S_OK)
	{
		TCHAR str[256] = {0,};
		wprintf_s(str, L"Image Loading Error! (%d) \n", hr);
		MessageBox(NULL, str, L"TEST", MB_OK  );
	}
}
