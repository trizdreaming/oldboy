#pragma once
#include "oldboy.h"


class CRMimage
{
public:
	CRMimage(void);
	~CRMimage(void);

public:
	HRESULT Init(std::wstring path);

	float GetWidth() { return m_width; }
	float GetHeight() { return m_height; }

	ID2D1Bitmap* Get2DImg(){return m_2DImg;}

private:
	ID2D1Bitmap* m_2DImg;

private:
	float m_width;
	float m_height;

};

