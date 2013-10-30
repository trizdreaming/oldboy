#include "stdafx.h"
#include "oldboy.h"
#include "RMchildEffectImage.h"
#include "RMmainLoop.h"

//////////////////////////////////////////////////////////////////
//BitFlag 사용법													//
//각 비트는 어떤 이펙트를 play 화면에 보여줘야할지 말아야 할지 스위칭		//
//한 화면에 최대 8개까지 판정 가능								    //
//////////////////////////////////////////////////////////////////


CRMchildEffectImage::CRMchildEffectImage(void):
	m_pBitFlag(0)
{
}


CRMchildEffectImage::~CRMchildEffectImage(void)
{
}

void CRMchildEffectImage::Update()
{
	if( m_pBitFlag & 0x80 || m_pBitFlag & 0x08) //1p || 2p 첫 번째 타격
	{
		CRMobject::SetVisibleByScene();
		
		if ( CRMmainLoop::GetInstance()->GetNowScene() == m_Scene)
		{
			return;
		}
		
		//이쪽은 좌표 움직임 관련이라 움직임봐서 바꾸자
		for( int deltaTime = 0 ; deltaTime < 4 ; ++ deltaTime)
		{
			m_PositionY -= 3;
			m_PositionX -= 3;
		}

		m_PositionX = DEFAULT_POSITION_X;
		m_PositionY = DEFAULT_POSITION_Y;
	}

	//2,3,4 항목 추가할 것
}

void CRMchildEffectImage::HitEffectFlag()
{
	m_pBitFlag = (char) 0x80;
	//테스트용 비트 확인 및 입력 추가
}

