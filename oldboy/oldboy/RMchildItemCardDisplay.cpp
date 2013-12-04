#include "stdafx.h"
#include "RMchildItemCardDisplay.h"
#include "RMmacro.h"
#include "RMitemManager.h"


CRMchildItemCardDisplay::CRMchildItemCardDisplay(void):
	m_timeSlice(100),
	m_prevTime(0),
	m_flickFlag(true)
{
}


CRMchildItemCardDisplay::~CRMchildItemCardDisplay(void)
{
}

void CRMchildItemCardDisplay::Update()
{
	SetVisibleByScene();

	UINT	thisTime = timeGetTime();

	if( m_prevTime + m_timeSlice < thisTime )
	{
		if( m_flickFlag == true )
		{
			m_Alpha -= 0.1f;

			if( m_Alpha <= 0.0f )
			{
				m_flickFlag = false;
			}
		}
		else
		{
			m_Alpha += 0.2f;

			if ( m_Alpha >= 1.0f )
			{
				m_flickFlag = true;
			}
		}

		//printConsole("알파 값: %f \n", m_Alpha);
		
		m_prevTime = thisTime;

	}
	

	//아이템이 발동되면 해당 카드가 떠 있도록 함
	if ( CRMitemManager::GetInstance()->GetActivatedItem(m_playerNumber) == ITEM_TYPE_NONE )
	{
		m_Visible = false;
	}

}
