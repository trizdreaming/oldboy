#include "stdafx.h"
#include "oldboy.h"
#include "RMchildNote.h"
#include "RMmainLoop.h"


CRMchildNote::CRMchildNote(void)
{
}


CRMchildNote::~CRMchildNote(void)
{
}

void CRMchildNote::Update()
{
	CRMobject::SetVisibleByScene();

	if ( m_Scene != CRMmainLoop::GetInstance()->GetNowScene() )
	{
		return;
	}
	//520 good ½ÃÀÛ
	//545 perfect
	//+- 10   535 ÆÛÆÑ½ÃÀÛ, 555ÆÛÆå³¡
	//+- 30   515 ±» ½ÃÀÛ, 575±» ³¡ 
	if( m_PositionY == 515 )
	{
		return;
	}
	m_PositionY += 5;

	if (m_PositionY > SCREEN_SIZE_Y)
	{
		m_PositionY = -150;
	}
	
	return;
}
