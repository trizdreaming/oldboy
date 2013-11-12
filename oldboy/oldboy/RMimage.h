#pragma once

class CRMimage
{
public:
	CRMimage(void);
	~CRMimage(void);

public:
	HRESULT			CreateImage( const std::wstring& path );

	float			GetWidth() const { return m_Width; } //SM9: 이렇게 멤버 변수의 상태를 바꾸지 않는 함수의 경우 최대한 const를 붙여라
	float			GetHeight() const { return m_Height; }

	ID2D1Bitmap*	Get2DImg() const { return m_D2DImg; }

private:
	ID2D1Bitmap*	m_D2DImg;

private:
	float			m_Width;
	float			m_Height;

};

