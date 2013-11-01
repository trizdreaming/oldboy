#pragma once
#include "RMenumSet.h"

class CRMplayer
{
public:
	CRMplayer(void);
	virtual ~CRMplayer(void);
	
	void		AddEvent( JudgeType judgeEventType );
	UINT		GetCount( CountType countType );
	void		SetCount( CountType countType, UINT count );
	
private:
	void		CalcCombo();

	UINT		m_PerfectCount;
	UINT		m_GoodCount;
	UINT		m_MissCount;
	UINT		m_ComboCount;
	UINT		m_ScoreCount;
	
	bool		m_PrevIsCombo;
};

