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
	m_pBitFlag((char)0x00)
{
}


CRMchildEffectImage::~CRMchildEffectImage(void)
{
}

void CRMchildEffectImage::Update()
{
	if( m_pBitFlag & 0x80) //1p 첫 번째 타격
	{
		CRMobject::SetVisibleByScene();
		
		if ( CRMmainLoop::GetInstance()->GetNowScene() == m_Scene)
		{
			return;
		}
		
		//이쪽은 좌표 움직임 관련이라 움직임봐서 바꾸자
		m_PositionY -= 3;
		m_PositionX -= 3;

		m_PositionX = DEFAULT_POSITION_X;
		m_PositionY = DEFAULT_POSITION_Y;

		m_pBitFlag = m_pBitFlag & 0x7f;
	}

	else if( m_pBitFlag & 0x40)
	{
		CRMobject::SetVisibleByScene();

		if ( CRMmainLoop::GetInstance()->GetNowScene() == m_Scene)
		{
			return;
		}

		//이쪽은 좌표 움직임 관련이라 움직임봐서 바꾸자
		m_PositionY -= 3;
		m_PositionX += 3;

		m_PositionX = DEFAULT_POSITION_X;
		m_PositionY = DEFAULT_POSITION_Y;

		m_pBitFlag = m_pBitFlag & 0xbf;
	}

	else if( m_pBitFlag & 0x20)
	{
		CRMobject::SetVisibleByScene();

		if ( CRMmainLoop::GetInstance()->GetNowScene() == m_Scene)
		{
			return;
		}

		//이쪽은 좌표 움직임 관련이라 움직임봐서 바꾸자
		m_PositionY -= 3;
		m_PositionX -= 3;

		m_PositionX = DEFAULT_POSITION_X;
		m_PositionY = DEFAULT_POSITION_Y;

		m_pBitFlag = m_pBitFlag & 0xdf;
	}

	else if( m_pBitFlag & 0x10)
	{
		CRMobject::SetVisibleByScene();

		if ( CRMmainLoop::GetInstance()->GetNowScene() == m_Scene)
		{
			return;
		}

		//이쪽은 좌표 움직임 관련이라 움직임봐서 바꾸자
		m_PositionY -= 3;
		m_PositionX += 3;

		m_PositionX = DEFAULT_POSITION_X;
		m_PositionY = DEFAULT_POSITION_Y;

		m_pBitFlag = m_pBitFlag & 0xef;
	}

	

	//2p 동일한 형태로 비트 순서만 변경해서 추가 할 것(예정)
	//1p 테스트 후 진행
}

void CRMchildEffectImage::HitEffectFlag()
{



	m_pBitFlag = (char) 0x80;
	//테스트용 비트 확인 및 입력 추가


}

