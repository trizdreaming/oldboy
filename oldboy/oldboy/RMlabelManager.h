#pragma once

class CRMlabel;

class CRMlabelManager
{
	SINGLETON(CRMlabelManager);
	friend class CRMobjectManager;

private:
	CRMlabelManager(void);
	~CRMlabelManager(void);

public:
	// 팩토리 초기화
 	HRESULT						CreateFactory();
	IDWriteFactory*				GetTextFactory() const { return m_DWriteFactory; }

	void						AddLabel( std::wstring key , CRMlabel* label );

private:
	void								CheckError(HRESULT);

	IDWriteFactory*						m_DWriteFactory;
	std::map<std::wstring, CRMlabel*>	m_LabelMap;
};

