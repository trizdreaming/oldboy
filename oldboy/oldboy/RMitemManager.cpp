#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMitem.h"
#include "RMitemManager.h"
#include "RMitemT1Duplicate.h"
#include "RMitemT1Mist.h"
#include "RMitemT1Rest.h"
#include "RMitemT2Barrier.h"
#include "RMitemT2Delay.h"
#include "RMitemT2GaugeClear.h"
#include "RMitemT2Rotate.h"
#include "RMitemT3Recovery.h"
#include "RMitemT3Reverse.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"
#include "RMinput.h"
#include "RMpauseManager.h"


CRMitemManager::CRMitemManager(void)
{
}


CRMitemManager::~CRMitemManager(void)
{
}

void CRMitemManager::Create()
{
	// 1P Item Pool Init
	CRMitem* item = new CRMitemT1Duplicate();
	m_ItemPool[ITEM_T1_DUPLICATE] = item;
	item = new CRMitemT1Mist();
	m_ItemPool[ITEM_T1_MIST] = item;
	item = new CRMitemT1Rest();
	m_ItemPool[ITEM_T1_REST] = item;
	item = new CRMitemT2Barrier();
	m_ItemPool[ITEM_T2_BARRIER] = item;
	item = new CRMitemT2Delay();
	m_ItemPool[ITEM_T2_DELAY] = item;
	item = new CRMitemT2GaugeClear();
	m_ItemPool[ITEM_T2_GAUGE_CLEAR] = item;
	item = new CRMitemT2Rotate();
	m_ItemPool[ITEM_T2_ROTATE] = item;
	item = new CRMitemT3Recovery();
	m_ItemPool[ITEM_T3_RECOVERY] = item;
	item = new CRMitemT3Reverse();
	m_ItemPool[ITEM_T3_REVERSE] = item;

	// 2P Item Pool Init
	item = new CRMitemT1Duplicate();
	m_ItemPool[ITEM_T1_DUPLICATE] = item;
	item = new CRMitemT1Mist();
	m_ItemPool[ITEM_T1_MIST] = item;
	item = new CRMitemT1Rest();
	m_ItemPool[ITEM_T1_REST] = item;
	item = new CRMitemT2Barrier();
	m_ItemPool[ITEM_T2_BARRIER] = item;
	item = new CRMitemT2Delay();
	m_ItemPool[ITEM_T2_DELAY] = item;
	item = new CRMitemT2GaugeClear();
	m_ItemPool[ITEM_T2_GAUGE_CLEAR] = item;
	item = new CRMitemT2Rotate();
	m_ItemPool[ITEM_T2_ROTATE] = item;
	item = new CRMitemT3Recovery();
	m_ItemPool[ITEM_T3_RECOVERY] = item;
	item = new CRMitemT3Reverse();
	m_ItemPool[ITEM_T3_REVERSE] = item;
}

void CRMitemManager::Release()
{
	for ( auto& toBeDelete : m_ItemPool )
	{
		SafeDelete( toBeDelete );
	}
}

void CRMitemManager::Update()
{
	if ( CRMpauseManager::GetInstance()->IsPause() )
	{
		return;
	}
	// 공격 구현
	
	// 1. 각 플레이어의 MP 체크
	int p1MaxMP = CRMplayer1P::GetInstance()->GetMaxMP();
	int p2MaxMP = CRMplayer2P::GetInstance()->GetMaxMP();

	int p1MP = CRMplayer1P::GetInstance()->GetMP();
	int p2MP = CRMplayer2P::GetInstance()->GetMP();

	// 최대 가질수 있는 mp의 비율 1이면 풀 게이지
	float p1GaugeRate = (float)p1MP / (float)p1MaxMP;
	float p2GaugeRate = (float)p2MP / (float)p2MaxMP;

	// 아이템 포지션 결정
	m_ItemPosition[TIER_1P_ONE] = (float)p1MaxMP * 0.3f;
	m_ItemPosition[TIER_1P_TWO] = (float)p1MaxMP * 0.6f;
	m_ItemPosition[TIER_1P_THREE] = (float)p1MaxMP * 0.9f;

	m_ItemPosition[TIER_2P_ONE] = (float)p2MaxMP * 0.3f;
	m_ItemPosition[TIER_2P_TWO] = (float)p2MaxMP * 0.6f;
	m_ItemPosition[TIER_2P_THREE] = (float)p2MaxMP * 0.9f;

	// 아이템 로테이트로부터 아이템 가져와야함
	if ( p1GaugeRate >= 0.9 )
	{
		m_NowItem[PLAYER_ONE] = ITEM_T3_RECOVERY;
	}
	else if ( p1GaugeRate >= 0.6 )
	{
		m_NowItem[PLAYER_ONE] = ITEM_T2_DELAY;
	}
	else if ( p1GaugeRate >= 0.3 )
	{
		m_NowItem[PLAYER_ONE] = ITEM_T1_MIST;
	}

	if ( p2GaugeRate >= 0.9 )
	{
		m_NowItem[PLAYER_TWO] = ITEM_T3_RECOVERY;
	}
	else if ( p2GaugeRate >= 0.6 )
	{
		m_NowItem[PLAYER_TWO] = ITEM_T2_DELAY;
	}
	else if ( p2GaugeRate >= 0.3 )
	{
		m_NowItem[PLAYER_TWO] = ITEM_T1_MIST;
	}

	// 2. 공격 키 입력 받기
	// 3. MP 상황에 맞춰 공격 가능 최대 티어로 m_NowItem[공격 키 입력 들어온 플레이어]의 아이템 타입 설정 
	if ( CRMinput::GetInstance()->GetKeyStatusByKey( KEY_TABLE_P1_ATTACK ) == KEY_STATUS_DOWN && m_NowItem[PLAYER_ONE] != ITEM_TYPE_NONE )
	{
		printConsole("Player1 Attack \n");
		CRMplayer1P::GetInstance()->ResetMP();
		m_NowItem[PLAYER_ONE] = ITEM_TYPE_NONE;
	}
	else if ( CRMinput::GetInstance()->GetKeyStatusByKey( KEY_TABLE_P2_ATTACK ) == KEY_STATUS_DOWN && m_NowItem[PLAYER_TWO] != ITEM_TYPE_NONE )
	{
		printConsole("Player2 Attack \n");
		CRMplayer2P::GetInstance()->ResetMP();
		m_NowItem[PLAYER_TWO] = ITEM_TYPE_NONE;
	}
	

	// 회전 구현
	// 1. 각 티어별로 틱이 되었는지 확인
	// 2. 해당 티어 Rotate
}

void CRMitemManager::RotateItem( ItemTierType tier )
{
	switch (tier)
	{
	case TIER_NONE:
		break;
	case TIER_1P_ONE:
		break;
	case TIER_1P_TWO:
		break;
	case TIER_1P_THREE:
		break;
	case TIER_2P_ONE:
		break;
	case TIER_2P_TWO:
		break;
	case TIER_2P_THREE:
		break;
	case TIER_MAX:
		break;
	default:
		break;
	}
}
