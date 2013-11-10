#include "stdafx.h"
#include "oldboy.h"
#include "RMchildEffectImage.h"
#include "RMchildEffectManager.h"
#include "RMmainLoop.h"

CRMchildEffectImage::CRMchildEffectImage(void):
	m_EffectTime(0),
	m_EffectType(0)
{
}


CRMchildEffectImage::~CRMchildEffectImage(void)
{
}

void CRMchildEffectImage::Update()
{
	int highMask = 0;
	
	if ( m_Visible == false && CRMchildEffectManager::GetInstance()->GetFlag() )
	{
		m_EffectTime = 0;

		m_Visible = true;
		
		for ( int i = 0 ; i < 8 ; ++i )
		{
			if ( CRMchildEffectManager::GetInstance()->GetFlag() & ( 0x01 << i ) )
			{				
				// printConsole("테스트!!!! %x \n", CRMchildEffectManager::GetInstance()->GetFlag() & ( 0x01 << i ));

				m_EffectType = i % 4;
				highMask = i / 4;
			}
		}

		// printConsole( "테스트 출력 플래그 [ %x ] 좌표 [ %f , %f ] 타입 [ %d ] \n", 
		//				CRMchildEffectManager::GetInstance()->GetFlag(), m_PositionX, m_PositionY, m_EffectType );

		CRMchildEffectManager::GetInstance()->ResetFlag( highMask );

		if ( highMask > 0)
		{
			CRMchildEffectManager::GetInstance()->GetStartPosition( PLAYER_TWO, &m_PositionX, &m_PositionY );
		}
		else
		{
			CRMchildEffectManager::GetInstance()->GetStartPosition( PLAYER_ONE, &m_PositionX, &m_PositionY );
		}
		
		m_PositionX = m_PositionX-90;
		m_PositionY = m_PositionY-80;
	}

	if ( m_Visible == false )
	{
		return;
	}

	//2p 추가 필요 없음

	m_PositionX -= 10 * m_EffectTime;;
	m_PositionY -= ( 7 - ( m_EffectType * 2) ) * m_EffectTime;

	// 8보다 커지면 2P의 이펙트 효과 이미지가 1P 공간을 침범함
	if ( ++m_EffectTime > 8 )
	{
		CRMobject::m_Visible = false;
	}

	return;
}