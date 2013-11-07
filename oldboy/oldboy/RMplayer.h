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

	UINT		m_Count[MAX_COUNT];
	
	bool		m_PrevIsCombo;
};

