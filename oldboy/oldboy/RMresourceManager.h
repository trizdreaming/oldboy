#pragma once
#include "oldboy.h"
#include "RMimage.h"
#include "RMobject.h"

class CRMresourceManager
{
private:
	CRMresourceManager(void);
	~CRMresourceManager(void);

public:
	static CRMresourceManager*	GetInstance();
	static void					ReleaseInstance();

	// 팩토리 초기화
	HRESULT						CreateFactory();
	IWICImagingFactory*			GetImageFactory() { return m_pWICFactory; }

	HRESULT						CreateTexture();
	CRMimage*					GetTexture( Object_Type key ) { return m_TextureMap[key]; }
	
private:
	void								CheckError(HRESULT);

	IWICImagingFactory*					m_pWICFactory;
	std::map<Object_Type, CRMimage*>	m_TextureMap;

	static CRMresourceManager*			m_pInstance;

};

