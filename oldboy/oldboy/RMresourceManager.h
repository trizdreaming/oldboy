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
	HRESULT						CreateTexture( const std::string& folderName );
	HRESULT						CreateTextureAlbum( const std::string& folderName );

	CRMimage*					GetTexture( const ObjectType& key ) { return m_TextureMap[key]; }
	
private:
	void								InitializeMap();
	void								InitializeAlbum();

	std::wstring						GetFilePath( const std::string& folderName, const std::string& resourceName ) const;

	IWICImagingFactory*					m_pWICFactory;
	std::map<ObjectType, CRMimage*>		m_TextureMap;
};

