#include "stdafx.h"
#include "RMitemT2GaugeClear.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"

CRMitemT2GaugeClear::CRMitemT2GaugeClear(void)
{
	m_ObjectType = OBJECT_ITEM_T2_GAUGE_CLEAR_GRAY;
	m_ObjectTypeColor = OBJECT_ITEM_T2_GAUGE_CLEAR_COLOR;
}

CRMitemT2GaugeClear::~CRMitemT2GaugeClear(void)
{
}

void CRMitemT2GaugeClear::Active()
{
	CRMitem::Active();

	if ( m_TargetPlayer == PLAYER_ONE )
	{
		CRMplayer1P::GetInstance()->ResetMP();
	}
	if ( m_TargetPlayer == PLAYER_TWO )
	{
		CRMplayer2P::GetInstance()->ResetMP();
	}
}
