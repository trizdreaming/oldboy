#include "stdafx.h"
#include "RMresourceManager.h"

CRMresourceManager*	CRMresourceManager::m_pInstance = nullptr;

CRMresourceManager::CRMresourceManager(void):
	m_pWICFactory(nullptr)
{
	CreateFactory();
	m_TextureMap.clear();
}


CRMresourceManager::~CRMresourceManager(void)
{
	SafeRelease(m_pWICFactory);

	for(auto &iter = m_TextureMap.begin(); iter != m_TextureMap.end(); ++iter)
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
	HRESULT hr = S_OK;

	CRMimage* texture;

	texture = new CRMimage();
	texture->Init( L"./Resource/image_bg_01_01.png" );
	m_TextureMap[BG_IMAGE] = texture;
	
	texture = new CRMimage();
	texture->Init( L"./Resource/image_nt_01_01.png" );
	m_TextureMap[NOTE_NORMAL_1] = texture;

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