#pragma once
#include "RMenumSet.h"
#include "RMdefine.h"

class CRMplayer
{
public:
	CRMplayer(void);
	virtual ~CRMplayer(void);

	void		Init();
	
	void		AddEvent( JudgeType judgeEventType );
	UINT		GetCount( CountType countType ) const;
	void		SetCount( CountType countType, UINT count );
	
	void		AddHP( int hpUp );
	void		SubHP();
	int			GetHP() { return m_HP; }

	void		ResetMP() { m_MP = 0; }
	float		GetMP() { return m_MP; }
	float		GetMaxMP() { return m_HP * PLAYER_HP_MP_RATE; }

	void		End() { m_HP = 0; }
	bool		IsEnd() { return (m_HP == 0); }
	bool		IsDead() { return ( m_HP <= 20 ); }

	void		StartScoreBoost() { m_IsItemBoostOn = true; }
	void		StopScoreBoost() { m_IsItemBoostOn = false; }

private:
	void		CalcCombo();

	std::array<UINT, COUNT_MAX>		m_Count;
	
	bool		m_PrevIsCombo;

	int			m_HP;	// 셔터를 관리하기 위함[Health Point]
	float		m_MP;	// 게이지를 관리하기 위함[Mana Point]

	bool		m_IsItemBoostOn;
};

