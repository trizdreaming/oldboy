#pragma once
#include "oldboy.h"


class CRMimage
{
public:
	CRMimage(void);
	~CRMimage(void);

public:
	HRESULT Init(std::wstring path); //SM9: path가 내부에서 변화가 없다면 const std::wstring& 으로 넘길 것.

	float GetWidth() { return m_width; }
	float GetHeight() { return m_height; }

	ID2D1Bitmap* Get2DImg(){return m_2DImg;}

private:
	ID2D1Bitmap* m_2DImg;

private:
	float m_width;
	float m_height;

};

