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
	IDWriteFactory*				GetTextFactory() const { return m_DWriteFactory; } //SM9: const 붙였데이..

	void						AddLabel(const std::wstring& key , CRMlabel* label ); //SM9: 여기도 const


	
	//std::map<std::wstring, CRMlabel*>	m_LabelMap;

private:
	void								CheckError(HRESULT);

	IDWriteFactory*						m_DWriteFactory;

	// CRMobjectManager에서 friend class로 라벨 맵에 접근
	// 그리고 CRMobjectManager에서 이곳에 접근하기 때문에 private안에 friend class CRMobjectManager; 라고 해줘야 되는겨...

	std::map<std::wstring, CRMlabel*>	m_LabelMap;
};

