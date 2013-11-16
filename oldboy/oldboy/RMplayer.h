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

	bool		IsDead() { return ( m_HP <= 0 ) ? true : false; }
private:
	void		CalcCombo();

	UINT		m_Count[MAX_COUNT];
	
	bool		m_PrevIsCombo;

	int			m_HP;
};

