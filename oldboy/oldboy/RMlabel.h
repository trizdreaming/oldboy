#pragma once
#include "RMobject.h"

class CRMlabel :
	public CRMobject
{
public:
	CRMlabel(void);
	~CRMlabel(void);

	void		CreateLabel( std::wstring key, std::wstring string, wchar_t* fontFace, float fontSize );

	virtual void	Update();
	virtual void	Render();

	std::wstring	GetString() const { return m_String; }

	wchar_t*	GetFontFace() const { return m_FontFace; }
	float		GetFontSize() const { return m_FontSize; }
	float		GetRed() const { return m_ColorR; }
	float		GetGreen() const { return m_ColorG; }
	float		GetBlue() const { return m_ColorB; }
	float		GetOpacity() const { return m_Opacity; }
	bool		IsItalic() const { return m_Italic; }
	bool		IsBold() const { return m_Bold; }

	void		SetFontSize( float fontsize ) { m_FontSize = fontsize; }
	void		SetFontFace( wchar_t* fontface ) { m_FontFace = fontface; }
	void		SetBold( bool bold ) { m_Bold = bold; }
	void		SetItalic( bool italic ) { m_Italic = italic; }
	void		SetRed( float r ) { m_ColorR = r; }
	void		SetGreen( float g ) { m_ColorG = g; }
	void		SetBlue( float b ) { m_ColorB = b; }
	void		SetColor( float r, float g, float b ) { m_ColorR = r; m_ColorG = g; m_ColorB = b; }
	void		SetOpacity( float opacity ) { m_Opacity = opacity; }
	void		SetRGBA( float r, float g, float b, float a ) { m_ColorR = r; m_ColorG = g; m_ColorB = b; m_Opacity = a; }

private:
	void		SetTextFormat();

	IDWriteTextFormat*		m_TextFormat;
	ID2D1SolidColorBrush*	m_Brush;

	wchar_t*		m_FontFace;
	std::wstring	m_String;

	float		m_FontSize;
	float		m_ColorR, m_ColorG, m_ColorB;
	float		m_Opacity;
	bool		m_Bold;
	bool		m_Italic;
};

