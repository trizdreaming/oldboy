#pragma once
class CRMJudgeManager
{
public:
	CRMJudgeManager(void);
	~CRMJudgeManager(void);

	// 싱글톤
	static CRMJudgeManager*		GetInstance();
	static void					ReleaseInstance();

	//노트 관리
	void						StartNote(PLAYER_NUMBER player);
	
	//노트 판정
	void						JudgeNote();

private:
	static CRMJudgeManager*		m_pInstance;

};

