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
#include "RMwellRandom.h"


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
	item->m_OwnPlayer = PLAYER_ONE;
	item->m_TargetPlayer = PLAYER_TWO;
	m_ItemPool[ITEM_T1_DUPLICATE] = item;

	item = new CRMitemT1Mist();
	item->m_OwnPlayer = PLAYER_ONE;
	item->m_TargetPlayer = PLAYER_TWO;
	m_ItemPool[ITEM_T1_MIST] = item;

	item = new CRMitemT1Rest();
	item->m_OwnPlayer = PLAYER_ONE;
	item->m_TargetPlayer = PLAYER_ONE;
	m_ItemPool[ITEM_T1_REST] = item;

	item = new CRMitemT2Barrier();
	item->m_OwnPlayer = PLAYER_ONE;
	item->m_TargetPlayer = PLAYER_ONE;
	m_ItemPool[ITEM_T2_BARRIER] = item;

	item = new CRMitemT2Delay();
	item->m_OwnPlayer = PLAYER_ONE;
	item->m_TargetPlayer = PLAYER_TWO;
	m_ItemPool[ITEM_T2_DELAY] = item;

	item = new CRMitemT2GaugeClear();
	item->m_OwnPlayer = PLAYER_ONE;
	item->m_TargetPlayer = PLAYER_TWO;
	m_ItemPool[ITEM_T2_GAUGE_CLEAR] = item;

	item = new CRMitemT2Rotate();
	item->m_OwnPlayer = PLAYER_ONE;
	item->m_TargetPlayer = PLAYER_TWO;
	m_ItemPool[ITEM_T2_ROTATE] = item;

	item = new CRMitemT3Recovery();
	item->m_OwnPlayer = PLAYER_ONE;
	item->m_TargetPlayer = PLAYER_ONE;
	m_ItemPool[ITEM_T3_RECOVERY] = item;

	item = new CRMitemT3Reverse();
	item->m_OwnPlayer = PLAYER_ONE;
	item->m_TargetPlayer = PLAYER_TWO;
	m_ItemPool[ITEM_T3_REVERSE] = item;

	// 2P Item Pool Init
	item = new CRMitemT1Duplicate();
	item->m_OwnPlayer = PLAYER_TWO;
	item->m_TargetPlayer = PLAYER_ONE;
	m_ItemPool[ITEM_T3_MAX + ITEM_T1_DUPLICATE] = item;

	item = new CRMitemT1Mist();
	item->m_OwnPlayer = PLAYER_TWO;
	item->m_TargetPlayer = PLAYER_ONE;
	m_ItemPool[ITEM_T3_MAX + ITEM_T1_MIST] = item;

	item = new CRMitemT1Rest();
	item->m_OwnPlayer = PLAYER_TWO;
	item->m_TargetPlayer = PLAYER_TWO;
	m_ItemPool[ITEM_T3_MAX + ITEM_T1_REST] = item;

	item = new CRMitemT2Barrier();
	item->m_OwnPlayer = PLAYER_TWO;
	item->m_TargetPlayer = PLAYER_TWO;
	m_ItemPool[ITEM_T3_MAX + ITEM_T2_BARRIER] = item;

	item = new CRMitemT2Delay();
	item->m_OwnPlayer = PLAYER_TWO;
	item->m_TargetPlayer = PLAYER_ONE;
	m_ItemPool[ITEM_T3_MAX + ITEM_T2_DELAY] = item;

	item = new CRMitemT2GaugeClear();
	item->m_OwnPlayer = PLAYER_TWO;
	item->m_TargetPlayer = PLAYER_ONE;
	m_ItemPool[ITEM_T3_MAX + ITEM_T2_GAUGE_CLEAR] = item;

	item = new CRMitemT2Rotate();
	item->m_OwnPlayer = PLAYER_TWO;
	item->m_TargetPlayer = PLAYER_ONE;
	m_ItemPool[ITEM_T3_MAX + ITEM_T2_ROTATE] = item;

	item = new CRMitemT3Recovery();
	item->m_OwnPlayer = PLAYER_TWO;
	item->m_TargetPlayer = PLAYER_TWO;
	m_ItemPool[ITEM_T3_MAX + ITEM_T3_RECOVERY] = item;

	item = new CRMitemT3Reverse();
	item->m_OwnPlayer = PLAYER_TWO;
	item->m_TargetPlayer = PLAYER_ONE;
	m_ItemPool[ITEM_T3_MAX + ITEM_T3_REVERSE] = item;

	m_TierItem[TIER_1P_ONE] = (ItemType) CRMwellRandom::GetInstance()->WellRandom(ITEM_T1_NONE + 1, ITEM_T1_MAX - 1);
	m_TierItem[TIER_1P_TWO] = (ItemType) CRMwellRandom::GetInstance()->WellRandom(ITEM_T2_NONE + 1, ITEM_T2_MAX - 1);
	m_TierItem[TIER_1P_THREE] = (ItemType) CRMwellRandom::GetInstance()->WellRandom(ITEM_T3_NONE + 1, ITEM_T3_MAX - 1);
	m_TierItem[TIER_2P_ONE] = (ItemType) CRMwellRandom::GetInstance()->WellRandom(ITEM_T1_NONE + 1, ITEM_T1_MAX - 1);
	m_TierItem[TIER_2P_TWO] = (ItemType) CRMwellRandom::GetInstance()->WellRandom(ITEM_T2_NONE + 1, ITEM_T2_MAX - 1);
	m_TierItem[TIER_2P_THREE] = (ItemType) CRMwellRandom::GetInstance()->WellRandom(ITEM_T3_NONE + 1, ITEM_T3_MAX - 1);

	m_TimeSliceForTier[TIER_1P_ONE] = m_TimeSliceForTier[TIER_2P_ONE] = 5000;
	m_TimeSliceForTier[TIER_1P_TWO] = m_TimeSliceForTier[TIER_2P_TWO] = 4000;
	m_TimeSliceForTier[TIER_1P_THREE] = m_TimeSliceForTier[TIER_2P_THREE] = 7000;

	UINT	thisTime = timeGetTime();

	m_PrevTimeTierRotate[TIER_1P_ONE] = m_PrevTimeTierRotate[TIER_1P_TWO] = m_PrevTimeTierRotate[TIER_1P_THREE] = 
	m_PrevTimeTierRotate[TIER_2P_ONE] = m_PrevTimeTierRotate[TIER_2P_TWO] = m_PrevTimeTierRotate[TIER_2P_THREE] = thisTime;
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

	//////////////////////////////////////////////////////////////////////////
	// 공격 구현
	//////////////////////////////////////////////////////////////////////////

	// 1. 각 플레이어의 MP 체크
	int p1MaxMP = CRMplayer1P::GetInstance()->GetMaxMP();
	int p2MaxMP = CRMplayer2P::GetInstance()->GetMaxMP();

	int p1MP = CRMplayer1P::GetInstance()->GetMP();
	int p2MP = CRMplayer2P::GetInstance()->GetMP();

	// 최대 가질수 있는 mp의 비율 1이면 풀 게이지
	float p1GaugeRate = (float)p1MP / (float)p1MaxMP;
	float p2GaugeRate = (float)p2MP / (float)p2MaxMP;

	// 아이템 포지션 결정
	float p1Tier1Position = SCREEN_SIZE_Y - (float)p1MaxMP * 0.3f;
	float p1Tier2Position = SCREEN_SIZE_Y - (float)p1MaxMP * 0.6f;
	float p1Tier3Position = SCREEN_SIZE_Y - (float)p1MaxMP * 0.9f;

	if ( (int)m_ItemPosition[TIER_1P_THREE] != (int)p1Tier3Position )
	{
		m_ItemPosition[TIER_1P_ONE] += (p1Tier1Position - m_ItemPosition[TIER_1P_ONE]) / 100;
		m_ItemPosition[TIER_1P_TWO] += (p1Tier2Position - m_ItemPosition[TIER_1P_TWO]) / 100;
		m_ItemPosition[TIER_1P_THREE] += (p1Tier3Position - m_ItemPosition[TIER_1P_THREE]) / 100;
	}

	float p2Tier1Position = SCREEN_SIZE_Y - (float)p2MaxMP * 0.3f;
	float p2Tier2Position = SCREEN_SIZE_Y - (float)p2MaxMP * 0.6f;
	float p2Tier3Position = SCREEN_SIZE_Y - (float)p2MaxMP * 0.9f;

	if ( (int)m_ItemPosition[TIER_2P_THREE] != (int)p2Tier3Position )
	{
		m_ItemPosition[TIER_2P_ONE] += (p2Tier1Position - m_ItemPosition[TIER_2P_ONE]) / 100;
		m_ItemPosition[TIER_2P_TWO] += (p2Tier2Position - m_ItemPosition[TIER_2P_TWO]) / 100;
		m_ItemPosition[TIER_2P_THREE] += (p2Tier3Position - m_ItemPosition[TIER_2P_THREE]) / 100;
	}


	// 아이템 로테이트로부터 아이템 가져와야함
	if ( p1GaugeRate >= 0.9 )
	{
		m_NowItem[PLAYER_ONE] = m_TierItem[TIER_1P_THREE];
	}
	else if ( p1GaugeRate >= 0.6 )
	{
		m_NowItem[PLAYER_ONE] = m_TierItem[TIER_1P_TWO];
	}
	else if ( p1GaugeRate >= 0.3 )
	{
		m_NowItem[PLAYER_ONE] = m_TierItem[TIER_1P_ONE];
	}
	else
	{
		m_NowItem[PLAYER_ONE] = ITEM_TYPE_NONE;
	}

	if ( p2GaugeRate >= 0.9 )
	{
		m_NowItem[PLAYER_TWO] = m_TierItem[TIER_2P_THREE];
	}
	else if ( p2GaugeRate >= 0.6 )
	{
		m_NowItem[PLAYER_TWO] = m_TierItem[TIER_2P_TWO];
	}
	else if ( p2GaugeRate >= 0.3 )
	{
		m_NowItem[PLAYER_TWO] = m_TierItem[TIER_2P_ONE];
	}
	else
	{
		m_NowItem[PLAYER_TWO] = ITEM_TYPE_NONE;
	}

	// 2. 공격 키 입력 받기
	// 3. MP 상황에 맞춰 공격 가능 최대 티어로 m_NowItem[공격 키 입력 들어온 플레이어]의 아이템 타입 설정 
	if ( ( CRMinput::GetInstance()->GetKeyStatusByKey( KEY_TABLE_P1_ATTACK ) == KEY_STATUS_DOWN ) && m_NowItem[PLAYER_ONE] != ITEM_TYPE_NONE )
	{
		CRMitem* thisItem = m_ItemPool[ m_NowItem[PLAYER_ONE] ];
		if ( thisItem->m_TargetPlayer == PLAYER_ONE )
		{
			if ( m_ActiveItem[PLAYER_ONE] != ITEM_TYPE_NONE )
			{
				return;
			}
			m_ActiveItem[PLAYER_ONE] = m_NowItem[PLAYER_ONE];
		}
		else if ( thisItem->m_TargetPlayer == PLAYER_TWO )
		{
			if ( m_ActiveItem[PLAYER_TWO] != ITEM_TYPE_NONE )
			{
				return;
			}
			m_ActiveItem[PLAYER_TWO] = m_NowItem[PLAYER_ONE];
		}
		m_NowItem[PLAYER_ONE] = ITEM_TYPE_NONE;
		
		if( thisItem != nullptr )
		{
			thisItem->Active();
		}

		printConsole("Player1 Attack Type %d \n", m_NowItem[PLAYER_ONE]);
		CRMplayer1P::GetInstance()->ResetMP();
	}
	else if ( ( CRMinput::GetInstance()->GetKeyStatusByKey( KEY_TABLE_P2_ATTACK ) == KEY_STATUS_DOWN ) && m_NowItem[PLAYER_TWO] != ITEM_TYPE_NONE )
	{
		CRMitem* thisItem = m_ItemPool[ ITEM_T3_MAX + m_NowItem[PLAYER_TWO] ];
		if ( thisItem->m_TargetPlayer == PLAYER_ONE)
		{
			if ( m_ActiveItem[PLAYER_ONE] != ITEM_TYPE_NONE )
			{
				return;
			}
			m_ActiveItem[PLAYER_ONE] = m_NowItem[PLAYER_TWO];
		}
		else if ( thisItem->m_TargetPlayer == PLAYER_TWO )
		{
			if ( m_ActiveItem[PLAYER_TWO] != ITEM_TYPE_NONE )
			{
				return;
			}
			m_ActiveItem[PLAYER_TWO] = m_NowItem[PLAYER_TWO];
		}
		m_NowItem[PLAYER_TWO] = ITEM_TYPE_NONE;

		if( thisItem != nullptr )
		{
			thisItem->Active();
		}

		printConsole("Player2 Attack Type %d \n", m_NowItem[PLAYER_TWO]);
		CRMplayer2P::GetInstance()->ResetMP();
	}
	
	UINT	thisTime = timeGetTime();

	// 회전 구현
	// 1. 각 티어별로 틱이 되었는지 확인
	// 2. 해당 티어 Rotate
	for ( auto i = TIER_1P_ONE ; i < TIER_MAX ; i = (ItemTierType)(i + 1) )
	{
		if ( m_PrevTimeTierRotate[i] + m_TimeSliceForTier[i] < thisTime )
		{
			//printConsole( "회전 시간 - %d : %d 번째 슬롯 회전! 위치 : %f \n", thisTime, i, m_ItemPosition[i] );
			m_PrevTimeTierRotate[i] = thisTime;
			RotateItem(i);
		}
	}

	for ( auto& iter : m_ItemPool )
	{
		if ( iter != nullptr )
		{
			iter->Update();
		}	
	}

}

void CRMitemManager::RotateItem( ItemTierType tier )
{
	switch (tier)
	{
	case TIER_1P_ONE:
		m_TierItem[TIER_1P_ONE] = (ItemType) CRMwellRandom::GetInstance()->WellRandom(ITEM_T1_NONE + 1, ITEM_T1_MAX - 1);
		break;
	case TIER_1P_TWO:
		m_TierItem[TIER_1P_TWO] = (ItemType) CRMwellRandom::GetInstance()->WellRandom(ITEM_T2_NONE + 1, ITEM_T2_MAX - 1);
		break;
	case TIER_1P_THREE:
		m_TierItem[TIER_1P_THREE] = (ItemType) CRMwellRandom::GetInstance()->WellRandom(ITEM_T3_NONE + 1, ITEM_T3_MAX - 1);
		break;
	case TIER_2P_ONE:
		m_TierItem[TIER_2P_ONE] = (ItemType) CRMwellRandom::GetInstance()->WellRandom(ITEM_T1_NONE + 1, ITEM_T1_MAX - 1);
		break;
	case TIER_2P_TWO:
		m_TierItem[TIER_2P_TWO] = (ItemType) CRMwellRandom::GetInstance()->WellRandom(ITEM_T2_NONE + 1, ITEM_T2_MAX - 1);
		break;
	case TIER_2P_THREE:
		m_TierItem[TIER_2P_THREE] = (ItemType) CRMwellRandom::GetInstance()->WellRandom(ITEM_T3_NONE + 1, ITEM_T3_MAX - 1);
		break;
	case TIER_NONE:
	case TIER_MAX:
	default:
		break;
	}
}

ObjectType CRMitemManager::GetObjectType( ItemTierType tier )
{
	ItemType thisItem = m_TierItem[tier];
	PlayerNumber player = PLAYER_ONE;
	
	if ( tier > TIER_1P_2P_DIVIDE )
		player = PLAYER_TWO;

	if ( m_ItemPool[thisItem + ( player == PLAYER_TWO ? ITEM_T3_MAX : 0 )] != nullptr )
	{
		if ( thisItem == m_NowItem[player] )
		{
			return m_ItemPool[thisItem + ( player == PLAYER_TWO ? ITEM_T3_MAX : 0 )]->GetObjectTypeColor();
		}
		else
		{
			return m_ItemPool[thisItem + ( player == PLAYER_TWO ? ITEM_T3_MAX : 0 )]->GetObjectTypeGray();
		}
	}
	
	return OBJECT_NONE;
}

void CRMitemManager::Reset()
{
	m_ActiveItem[PLAYER_ONE] = ITEM_TYPE_NONE;
	m_ActiveItem[PLAYER_TWO] = ITEM_TYPE_NONE;
	m_NowItem[PLAYER_ONE] = ITEM_TYPE_NONE;
	m_NowItem[PLAYER_TWO] = ITEM_TYPE_NONE;
}
