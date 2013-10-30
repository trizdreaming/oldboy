#pragma once

class CRMobject;

class CRMjudgeManager
{
	SINGLETON(CRMjudgeManager);

public:
	CRMjudgeManager(void);
	~CRMjudgeManager(void);

	//노트 관리
	void						StartNote( PlayerNumber player , ObjectType objectType );
	
	//노트 판정
	void						JudgeNote();
	bool						IsKeyInputRight( CRMobject* note );

private:
	void						DeleteNote( std::list<CRMobject*>* objectList );

};

