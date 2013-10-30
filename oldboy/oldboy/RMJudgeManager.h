#pragma once
#include "RMobject.h"
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
	void						StartNote( PlayerNumber player , ObjectType objectType );
	
	//노트 판정
	void						JudgeNote();

private:
	void						DeleteNote( std::list<CRMobject*>* objectList );
};

