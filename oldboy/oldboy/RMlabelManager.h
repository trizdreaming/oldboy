#pragma once

class CRMlabelManager
{
	SINGLETON(CRMlabelManager);

private:
	CRMlabelManager(void);
	~CRMlabelManager(void);

public:
	// 팩토리 초기화
 	HRESULT						CreateFactory();
	IDWriteFactory*				GetTextFactory() { return m_DWriteFactory; }
// 
// 	HRESULT						CreateTexture();
// 	CRMimage*					GetTexture( ObjectType key ) { return m_TextureMap[key]; }

private:
	void						CheckError(HRESULT);

	IDWriteFactory*				m_DWriteFactory;

	// 	IDWriteTextFormat*		m_TextFormat;
	// 	ID2D1SolidColorBrush*	m_Brush;
	// 이 두개는 각 라벨로.
};

