#pragma once
#include "RMenumSet.h"
#include "RMmacro.h"

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

	void						StartItemRecovery( PlayerNumber player );
	void						StopItemRecovery( PlayerNumber player );

private:
	void						JudgeNoteByPlayer( PlayerNumber playerNumber ) const;
	void						PrintScore( PlayerNumber player, JudgeType judgeType ) const;
	bool						IsKeyInputRight( CRMobject* note , PlayerNumber player ) const;

private:
	bool						IsItemP1RecoveryON;
	bool						IsItemP2RecoveryON;

};

