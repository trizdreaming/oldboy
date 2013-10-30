#pragma once
#include "RMenumSet.h"

class CRMimage;

class CRMresourceManager
{
	SINGLETON(CRMresourceManager);

private:
	CRMresourceManager(void);
	~CRMresourceManager(void);
	
public:
	// 팩토리 초기화
	HRESULT						CreateFactory();
	IWICImagingFactory*			GetImageFactory() { return m_pWICFactory; }

	HRESULT						CreateTexture();
	CRMimage*					GetTexture( ObjectType key ) { return m_TextureMap[key]; }
	
private:
	void								CheckError(HRESULT);

	IWICImagingFactory*					m_pWICFactory;
	std::map<ObjectType, CRMimage*>		m_TextureMap;
};

