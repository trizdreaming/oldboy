#pragma once

#include "RMenumSet.h"

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
	bool						IsKeyInputRight( CRMobject* note , PlayerNumber player );

private:
	void						JudgeNoteByPlayer( PlayerNumber playerNumber );
	void						PrintScore( PlayerNumber player, JudgeType judgeType );

	JudgeType					m_Player1Judge;
	JudgeType					m_Player2Judge;
};

