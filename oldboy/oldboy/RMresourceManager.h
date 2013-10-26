#pragma once
#include "oldboy.h"
#include "RMimage.h"
#include "RMEnumObjectType.h"

class CRMresourceManager
{
private:
	CRMresourceManager(void);
	~CRMresourceManager(void);

public:
	static CRMresourceManager*	GetInstance();
	static void					ReleaseInstance();

public:
	HRESULT								CreateFactory();
	
	HRESULT								InitTexture();
	std::map<EnumObjectType, CRMimage*>	GetTextureMap() { return m_TextureMap; }
	CRMimage*							GetTexture( EnumObjectType key ) { return m_TextureMap[key]; }
	
	IWICImagingFactory*					GetImageFactory() { return m_pWICFactory; }



private:
	IWICImagingFactory*					m_pWICFactory;
	std::map<EnumObjectType, CRMimage*>	m_TextureMap;

private:
	static CRMresourceManager*			m_pInstance;

};

