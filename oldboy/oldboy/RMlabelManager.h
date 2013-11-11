#pragma once

class CRMlabel;

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

	void						AddLabel( std::wstring key , CRMlabel* label );

	// CRMobjectManager에서 friend class로 라벨 맵에 접근
	std::map<std::wstring, CRMlabel*>	m_LabelMap;

private:
	void								CheckError(HRESULT);

	IDWriteFactory*						m_DWriteFactory;
};

