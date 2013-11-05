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

	//SM9: 레이블 매니저가 자신의 데이터를 통째로 리턴하는것은 뭔가 잘못된 구조다.
	//보통은 key를 받아서 내용물을 리턴한다던가 하는 멤버함수를 만들어주는 식으로 되어야 한다.
	// 즉, 레이블 매니저 안에서 뭔가 일을 하도록 해야 함.
	std::map<std::wstring, CRMlabel*>*	GetLabelMap() { return &m_LabelMap; }

private:
	void								CheckError(HRESULT);

	IDWriteFactory*						m_DWriteFactory;
	std::map<std::wstring, CRMlabel*>	m_LabelMap;
};

