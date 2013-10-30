#pragma once
class CRMjudgeManager
{
public:
	CRMjudgeManager(void);
	~CRMjudgeManager(void);

	// �̱���
	static CRMjudgeManager*		GetInstance();
	static void					ReleaseInstance();

	//��Ʈ ����
	void						StartNote( PLAYER_NUMBER player );
	
	//��Ʈ ����
	void						JudgeNote();

private:
	static CRMjudgeManager*		m_pInstance;

};

