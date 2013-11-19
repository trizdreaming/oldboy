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
	IWICImagingFactory*			GetImageFactory() const { return m_pWICFactory; }

	HRESULT						CreateTexture();
	HRESULT						CreateTexture( const std::string& folderName );
	HRESULT						CreateTextureAlbum( const std::string& folderName );

	CRMimage*					GetTexture( const ObjectType& key ) { return m_TextureMap[key]; }
	
private:
	void								InitializeMap();
	void								InitializeAlbum();

	std::wstring						GetFilePath( const std::string& folderName, const std::string& resourceName ) const;

	IWICImagingFactory*					m_pWICFactory;
	std::map<ObjectType, CRMimage*>		m_TextureMap; //SM9: 이걸 맵(레드블랙트리)으로 만들 이유가 전혀 없다. 닭잡는데 소잡는칼 쓰는격. 
	// 어차피 enum타입을 키로 쓸거면 그냥 배열로 해라
	// CRMimage* m_TextureMap[OBJECTTYPE_MAX]; 이런식으로.
};

