#pragma once

class CRMobject;

class CRMjudgeManager
{
	SINGLETON(CRMjudgeManager);

private:
	CRMjudgeManager(void);
	~CRMjudgeManager(void);

public:
	//노트 관리
	void						StartNote( PlayerNumber player , ObjectType objectType );
	
	//노트 판정
	void						JudgeNote();
	bool						IsKeyInputRight( CRMobject* note , std::list<CRMobject*>* objectList );

private:
	void						DeleteNote( std::list<CRMobject*>* objectList );

};

