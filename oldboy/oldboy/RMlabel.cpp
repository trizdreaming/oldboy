#include "stdafx.h"
#include "oldboy.h"
#include "RMlabel.h"
#include "RMlabelManager.h"
#include "RMrender.h"
#include "RMmainLoop.h"


CRMlabel::CRMlabel(void) :
	m_FontFace(nullptr),	/*m_String(nullptr),*/	m_FontSize(0.f),
	m_ColorR(0.f),			m_ColorG(0.f),		m_ColorB(0.f),
	m_Opacity(1.f),			m_Bold(false),		m_Italic(false),
	m_TextFormat(nullptr),	m_Brush(nullptr)
{
	m_Visible = true;
}

CRMlabel::~CRMlabel(void)
{
	SafeRelease( m_TextFormat );
	SafeRelease( m_Brush );
}

void CRMlabel::CreateLabel( std::wstring key, std::wstring string, wchar_t* fontFace, float fontSize )
{
	swprintf_s( m_String, string.c_str() );
	m_FontFace = fontFace;
	m_FontSize = fontSize;

	CRMlabelManager::GetInstance()->CreateFactory();
	SetTextFormat();

	CRMlabelManager::GetInstance()->AddLabel( key, this );
}


void CRMlabel::Update()
{
	SetVisibleByScene();

	m_Width = wcslen( m_String ) * m_FontSize * 5;
	m_Height = m_FontSize * 2;
	SetTextFormat();
}

void CRMlabel::Render()
{
	if ( m_Visible == false )
	{
		return;
	}

	SafeRelease( m_Brush );
	// 브러쉬 종류 추가하고 싶으면 이곳에 switch case 문으로 위에 매개인자로 enum 타입 받아서 추가
	CRMrender::GetInstance()->GetRenderTarget()->CreateSolidColorBrush( D2D1::ColorF(m_ColorR, m_ColorG, m_ColorB), &m_Brush );

	CRMrender::GetInstance()->GetRenderTarget()->DrawTextW(	
				m_String, 
				wcslen( m_String ), 
				m_TextFormat, D2D1::RectF( m_PositionX, m_PositionY, m_PositionY + m_Width, m_PositionY + m_Height ),
				m_Brush );
}

void CRMlabel::SetTextFormat()
{
	SafeRelease( m_TextFormat );
	CRMlabelManager::GetInstance()->GetTextFactory()->CreateTextFormat( m_FontFace, NULL,
						m_Bold ? DWRITE_FONT_WEIGHT_BOLD : DWRITE_FONT_WEIGHT_NORMAL,
						m_Italic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL,
						DWRITE_FONT_STRETCH_NORMAL, m_FontSize, L"ko", &m_TextFormat );
}
