﻿#pragma once
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
	HRESULT						CreateTexture( const std::string& folderName, ModeType modeType );
	HRESULT						CreateTextureAlbum( const std::string& folderName, ModeType modeType, AlbumImageType imageType = ALBUM_IMAGE_STATIC );

	CRMimage*					GetTexture( const WidgetType key ) { return m_TextureArray[key]; }
	
private:
	void								InitializeArray();
	void								InitializeAlbum( AlbumImageType imageType );

	std::wstring						GetFilePath( const std::string& folderName, const std::string& resourceName, ModeType modeType ) const;
	HRESULT								TextureMaker( const std::wstring& path, WidgetType type );

	IWICImagingFactory*					m_pWICFactory;
	std::array<CRMimage*, WIDGET_MAX>	m_TextureArray;
};

