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
	void						StartNote( PlayerNumber player , ObjectType objectType ) const;
	
	//노트 판정
	void						JudgeNote() const;
	

private:
	void						JudgeNoteByPlayer( PlayerNumber playerNumber ) const;
	void						PrintScore( PlayerNumber player, JudgeType judgeType ) const;
	bool						IsKeyInputRight( CRMobject* note , PlayerNumber player ) const;
};

