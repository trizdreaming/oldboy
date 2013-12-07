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
	void						StartNote( PlayerNumber player , WidgetType widgetType ) const;
	
	//노트 판정
	void						JudgeNote() const;

	// 리커버리 아이템 설정
	void						StartItemRecovery( PlayerNumber player );
	void						StopItemRecovery( PlayerNumber player );

private:
	void						JudgeNoteByPlayer( PlayerNumber playerNumber ) const;
	void						PrintScore( PlayerNumber player, JudgeType judgeType ) const;
	bool						IsKeyInputRight( CRMobject* note , PlayerNumber player ) const;

	std::array<bool, PLAYER_MAX>	m_IsItemRecoverOn;
};

