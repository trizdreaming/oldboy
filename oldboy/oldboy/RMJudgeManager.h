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
	void						JudgeNote();

	// 리커버리 아이템 설정
	void						StartItemRecovery( PlayerNumber player );
	void						StopItemRecovery( PlayerNumber player );

	void						InitializeJudgeType();
	JudgeType					GetJudgeType( PlayerNumber player );

private:
	void						JudgeNoteByPlayer( PlayerNumber playerNumber );
	void						PrintScore( PlayerNumber player, JudgeType judgeType );
	bool						IsKeyInputRight( CRMobject* note , PlayerNumber player ) const;

	std::array<bool, PLAYER_MAX>	m_IsItemRecoverOn;

	JudgeType						m_P1JudgeTypeTemp;
	JudgeType						m_P2JudgeTypeTemp;
};

