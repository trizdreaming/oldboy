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
	
	void		AddHP() { ++m_HP; }
	void		SubHP() { --m_HP; }
	int			GetHP() { return m_HP; }

	void		ResetMP() { m_MP = 0; }
	int			GetMP() { return m_MP; }

	bool		IsDead() { return ( m_HP <= 0 ) ? true : false; }

private:
	void		CalcCombo();

	UINT		m_Count[COUNT_MAX];
	
	bool		m_PrevIsCombo;

	int			m_HP;	// 셔터를 관리하기 위함[Health Point]
	int			m_MP;	// 게이지를 관리하기 위함[Mana Point]
};

