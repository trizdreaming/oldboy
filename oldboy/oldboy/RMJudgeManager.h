#pragma once
class CRMjudgeManager
{
	SINGLETON(CRMjudgeManager);

public:
	CRMjudgeManager(void);
	~CRMjudgeManager(void);



	// 싱글톤
	// static CRMjudgeManager*		GetInstance();
	// static void					ReleaseInstance();

	//노트 관리
	void						StartNote( PlayerNumber player );
	
	//노트 판정
	void						JudgeNote();

private:
	//static CRMjudgeManager*		m_pInstance;
};

