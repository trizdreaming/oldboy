#include "stdafx.h"
#include "RMmacro.h"
#include "RMchildGauge.h"
#include "RMmainLoop.h"
#include "RMchildShutter.h"
#include "RMobjectManager.h"
#include "RMdefine.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"

CRMchildGauge::CRMchildGauge(void)
{
}


CRMchildGauge::~CRMchildGauge(void)
{
}

void CRMchildGauge::Update()
{
	SetVisibleByScene();

	//////////////////////////////////////////////////////////////////////////
	//gauge init
	//////////////////////////////////////////////////////////////////////////

	if ( m_Scene != CRMmainLoop::GetInstance()->GetNowScene() )
	{
		if ( m_PositionY != 650 )
		{
			printConsole( "게이지 초기화 \n" );
			m_PositionY = 650;
		}
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	//각 플레이어별 게이지 계산 방안
	//1. 셔터의 높이를 역산 해 역산 내용을 저장
	//2. 게이지의 높이를 셔터의 높이 확인(셔터 하단 값 역산)
	//3. 셔터 높이 와 게이지 높이 비교 후 게이지가 낮은 경우 게이지 상승 연산
	//4. 게이지의 높이가 셔터 높이 보다 길거나 같은 경우 -> 강제로 끌어내림
	//4-1. 셔터에서 신경 안쓰게 할 것
	//////////////////////////////////////////////////////////////////////////

	float nowShutterPosition = 0.0f;
	float resultPosition = 0.0f;

	int hp = 0;
	float mp = 0;
	
	if ( m_PlayerNumber == PLAYER_ONE )
	{
		hp = CRMplayer1P::GetInstance()->GetHP();
		mp = CRMplayer1P::GetInstance()->GetMP();
	}
	else
	{
		hp = CRMplayer2P::GetInstance()->GetHP();
		mp = CRMplayer2P::GetInstance()->GetMP();
	}

	nowShutterPosition = SHUTTER_START_POSITION_Y + (PLAYER_HP_MAX - (float) hp ) * -((float) SHUTTER_START_POSITION_Y / PLAYER_HP_MAX) + 668;

	// 이동해야 할 좌표를 계산
	resultPosition = (float)( SCREEN_SIZE_Y - 12 - mp );

	// 셔터가 내려와버리면 게이지도 내려감
	if (resultPosition < nowShutterPosition)
	{
		resultPosition = nowShutterPosition;
	}

	// 게이지가 천천히 움직이도록 계산
	if ( (int)m_PositionY != (int)resultPosition )
	{
		m_PositionY += (resultPosition - m_PositionY) / 20;
	}

}