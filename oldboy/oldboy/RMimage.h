#pragma once
#include "oldboy.h"

class CRMimage
{
public:
	CRMimage(void);
	~CRMimage(void);

public:
	HRESULT			CreateImage( const std::wstring& path );

	float			GetWidth() { return m_Width; }
	float			GetHeight() { return m_Height; }

	ID2D1Bitmap*	Get2DImg() { return m_D2DImg; }

private:
	ID2D1Bitmap*	m_D2DImg;

private:
	float			m_Width;
	float			m_Height;

};

