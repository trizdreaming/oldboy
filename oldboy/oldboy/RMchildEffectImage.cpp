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
	CRMobject::SetVisibleByScene();
	++m_EffectTime;

	if ( CRMchildEffectManager::GetInstance()->GetFlag() )
	{
		m_EffectTime = 0;

		m_PositionX = CRMchildEffectManager::GetInstance()->GetStartPositionX() - 22;
		m_PositionY = CRMchildEffectManager::GetInstance()->GetStartPositionY() - 22;

		m_Visible = true;
		
		for ( int i = 0 ; i < 8 ; ++i )
		{
			if ( CRMchildEffectManager::GetInstance()->GetFlag() & ( 0x01 << i ) )
			{
				m_EffectType = m_EffectType++ % 4;
			}
		}
#ifdef _DEBUG
		printf_s( "테스트 출력 플래그 [ %x ] 좌표 [ %f , %f ] 타입 [ %d ] \n", 
			CRMchildEffectManager::GetInstance()->GetFlag(), 
			m_PositionX, m_PositionY, m_EffectType );
#endif
		CRMchildEffectManager::GetInstance()->ResetFlag();
	}

	//2p 추가 필요 없음

	switch ( m_EffectType )
	{
	case 1:
		m_PositionX -= 10 * m_EffectTime;
		m_PositionY -= 7 * m_EffectTime;

		break;
	case 2:
		m_PositionX -= 10 * m_EffectTime;
		m_PositionY -= 5 * m_EffectTime;

		break;
	case 3:
		m_PositionX -= 10 * m_EffectTime;
		m_PositionY -= 3 * m_EffectTime;

		break;
	case 4:
		m_PositionX -= 10 * m_EffectTime;
		m_PositionY -= 1 * m_EffectTime;

		break;

	default:
		break;
	}
	
	// 8보다 커지면 2P의 이펙트 효과 이미지가 1P 공간을 침범함
	if ( m_EffectTime > 8 )
	{
		CRMobject::m_Visible = false;
	}

	return;
}