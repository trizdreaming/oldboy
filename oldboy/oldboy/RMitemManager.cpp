#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMitem.h"
#include "RMitemManager.h"
#include "RMitemT1Duplicate.h"
#include "RMitemT1Mist.h"
#include "RMitemT1ScoreUp.h"
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
#include "RMrandomGenerator.h"


CRMitemManager::CRMitemManager(void)
{
	ZeroMemory(&m_NowItem, sizeof(m_NowItem));
	ZeroMemory(&m_ItemPool, sizeof(m_ItemPool));
	ZeroMemory(&m_TierItem, sizeof(m_TierItem));
	ZeroMemory(&m_ActiveItem, sizeof(m_ActiveItem));
	ZeroMemory(&m_ItemPosition, sizeof(m_ItemPosition));
	ZeroMemory(&m_PrevTimeTierRotate, sizeof(m_PrevTimeTierRotate));
	ZeroMemory(&m_TimeSliceForTier, sizeof(m_TimeSliceForTier));
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

	item = new CRMitemT1ScoreUp();
	item->m_OwnPlayer = PLAYER_ONE;
	item->m_TargetPlayer = PLAYER_ONE;
	m_ItemPool[ITEM_T1_SCORE_UP] = item;

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

	item = new CRMitemT1ScoreUp();
	item->m_OwnPlayer = PLAYER_TWO;
	item->m_TargetPlayer = PLAYER_TWO;
	m_ItemPool[ITEM_T3_MAX + ITEM_T1_SCORE_UP] = item;

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

	m_TierItem[TIER_1P_ONE] = (ItemType) CRMrandomGenerator::GetInstance()->GetRandom(ITEM_T1_NONE + 1, ITEM_T1_MAX - 1);
	m_TierItem[TIER_1P_TWO] = (ItemType) CRMrandomGenerator::GetInstance()->GetRandom(ITEM_T2_NONE + 1, ITEM_T2_MAX - 1);
	m_TierItem[TIER_1P_THREE] = (ItemType) CRMrandomGenerator::GetInstance()->GetRandom(ITEM_T3_NONE + 1, ITEM_T3_MAX - 1);
	m_TierItem[TIER_2P_ONE] = (ItemType) CRMrandomGenerator::GetInstance()->GetRandom(ITEM_T1_NONE + 1, ITEM_T1_MAX - 1);
	m_TierItem[TIER_2P_TWO] = (ItemType) CRMrandomGenerator::GetInstance()->GetRandom(ITEM_T2_NONE + 1, ITEM_T2_MAX - 1);
	m_TierItem[TIER_2P_THREE] = (ItemType) CRMrandomGenerator::GetInstance()->GetRandom(ITEM_T3_NONE + 1, ITEM_T3_MAX - 1);

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
	float p1MaxMP = CRMplayer1P::GetInstance()->GetMaxMP();
	float p2MaxMP = CRMplayer2P::GetInstance()->GetMaxMP();

	float p1MP = CRMplayer1P::GetInstance()->GetMP();
	float p2MP = CRMplayer2P::GetInstance()->GetMP();

	// 최대 가질수 있는 mp의 비율 1이면 풀 게이지
	float p1GaugeRate = p1MP / p1MaxMP;
	float p2GaugeRate = p2MP / p2MaxMP;

	// 아이템 포지션 결정
	float p1Tier1Position = SCREEN_SIZE_Y - p1MaxMP * 0.3f;
	float p1Tier2Position = SCREEN_SIZE_Y - p1MaxMP * 0.6f;
	float p1Tier3Position = SCREEN_SIZE_Y - p1MaxMP * 0.9f;

	if (p1Tier2Position > ITEM_DEAD_LINE)
	{
		p1Tier1Position = DEFAULT_POSITION_Y;
		p1Tier2Position = SCREEN_SIZE_Y - p1MaxMP * 0.45f;
	}
	if (p1Tier3Position > ITEM_DEAD_LINE)
	{
		p1Tier2Position = DEFAULT_POSITION_Y;
	}

	if ( (int)m_ItemPosition[TIER_1P_THREE] != (int)p1Tier3Position )
	{
		m_ItemPosition[TIER_1P_ONE] += (p1Tier1Position - m_ItemPosition[TIER_1P_ONE]) / 20;
		m_ItemPosition[TIER_1P_TWO] += (p1Tier2Position - m_ItemPosition[TIER_1P_TWO]) / 20;
		m_ItemPosition[TIER_1P_THREE] += (p1Tier3Position - m_ItemPosition[TIER_1P_THREE]) / 20;
	}

	float p2Tier1Position = SCREEN_SIZE_Y - p2MaxMP * 0.3f;
	float p2Tier2Position = SCREEN_SIZE_Y - p2MaxMP * 0.6f;
	float p2Tier3Position = SCREEN_SIZE_Y - p2MaxMP * 0.9f;

	if (p2Tier2Position > ITEM_DEAD_LINE)
	{
		p2Tier1Position = DEFAULT_POSITION_Y;
		p2Tier2Position = SCREEN_SIZE_Y - p1MaxMP * 0.45f;
	}
	if (p2Tier3Position > ITEM_DEAD_LINE)
	{
		p2Tier2Position = DEFAULT_POSITION_Y;
	}

	if ( (int)m_ItemPosition[TIER_2P_THREE] != (int)p2Tier3Position )
	{
		m_ItemPosition[TIER_2P_ONE] += (p2Tier1Position - m_ItemPosition[TIER_2P_ONE]) / 20;
		m_ItemPosition[TIER_2P_TWO] += (p2Tier2Position - m_ItemPosition[TIER_2P_TWO]) / 20;
		m_ItemPosition[TIER_2P_THREE] += (p2Tier3Position - m_ItemPosition[TIER_2P_THREE]) / 20;
	}

	// 아이템 로테이트로부터 아이템 가져와야함
	if ( p1GaugeRate > 0.9f )
	{
		m_NowItem[PLAYER_ONE] = m_TierItem[TIER_1P_THREE];
	}
	else if ( p1Tier2Position < ITEM_DEAD_LINE )
	{
		if ( p1GaugeRate > 0.6f )
		{
			m_NowItem[PLAYER_ONE] = m_TierItem[TIER_1P_TWO];
		}
		else if ( p1GaugeRate > 0.3f )
		{
			m_NowItem[PLAYER_ONE] = m_TierItem[TIER_1P_ONE];
		}
		else
		{
			m_NowItem[PLAYER_ONE] = ITEM_TYPE_NONE;
		}
	}
	else
	{
		if ( p1GaugeRate > 0.45f )
		{
			m_NowItem[PLAYER_ONE] = m_TierItem[TIER_1P_TWO];
		}
		else
		{
			m_NowItem[PLAYER_ONE] = ITEM_TYPE_NONE;
		}
	}

	if ( p2GaugeRate > 0.9f )
	{
		m_NowItem[PLAYER_TWO] = m_TierItem[TIER_2P_THREE];
	}
	else if ( p2Tier2Position < ITEM_DEAD_LINE ) 
	{
		if ( p2GaugeRate > 0.6f )
		{
			m_NowItem[PLAYER_TWO] = m_TierItem[TIER_2P_TWO];
		}
		else if ( p2GaugeRate > 0.3f )
		{
			m_NowItem[PLAYER_TWO] = m_TierItem[TIER_2P_ONE];
		}
		else
		{
			m_NowItem[PLAYER_TWO] = ITEM_TYPE_NONE;
		}
	}
	else
	{
		if ( p2GaugeRate > 0.45f )
		{
			m_NowItem[PLAYER_TWO] = m_TierItem[TIER_2P_TWO];
		}
		else
		{
			m_NowItem[PLAYER_TWO] = ITEM_TYPE_NONE;
		}
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
				if ( m_ActiveItem[PLAYER_ONE] == ITEM_T2_BARRIER )
				{
					DeactiveItem(PLAYER_ONE);
					// 1P 스스로 쉴드를 지우는 것이므로 지워지고 스킬 갱신

					printConsole("삭제! \n");
				}
				else
				{
					return;
				}
			}
			m_ActiveItem[PLAYER_ONE] = m_NowItem[PLAYER_ONE];
		}
		else if ( thisItem->m_TargetPlayer == PLAYER_TWO )
		{
			if ( CRMplayer2P::GetInstance()->IsDead() )
			{
				return;
			}
			if ( m_ActiveItem[PLAYER_TWO] != ITEM_TYPE_NONE )
			{
				if ( m_ActiveItem[PLAYER_TWO] == ITEM_T2_BARRIER )
				{
					DeactiveItem(PLAYER_TWO);
					CRMplayer1P::GetInstance()->ResetMP();
				}
				return;
			}
			m_ActiveItem[PLAYER_TWO] = m_NowItem[PLAYER_ONE];
		}
		m_NowItem[PLAYER_ONE] = ITEM_TYPE_NONE;
		
		if( thisItem != nullptr )
		{
			thisItem->Active();
		}

		printConsole("Player1 Attack Type %d \n", m_ActiveItem[PLAYER_ONE]);
		CRMplayer1P::GetInstance()->ResetMP();
	}
	else if ( ( CRMinput::GetInstance()->GetKeyStatusByKey( KEY_TABLE_P2_ATTACK ) == KEY_STATUS_DOWN ) && m_NowItem[PLAYER_TWO] != ITEM_TYPE_NONE )
	{
		CRMitem* thisItem = m_ItemPool[ ITEM_T3_MAX + m_NowItem[PLAYER_TWO] ];
		if ( thisItem->m_TargetPlayer == PLAYER_ONE)
		{
			if ( CRMplayer1P::GetInstance()->IsDead() )
			{
				return;
			}
			if ( m_ActiveItem[PLAYER_ONE] != ITEM_TYPE_NONE )
			{
				if ( m_ActiveItem[PLAYER_ONE] == ITEM_T2_BARRIER )
				{
					DeactiveItem(PLAYER_ONE);
					CRMplayer2P::GetInstance()->ResetMP();
				}
				return;
			}
			m_ActiveItem[PLAYER_ONE] = m_NowItem[PLAYER_TWO];
		}
		else if ( thisItem->m_TargetPlayer == PLAYER_TWO )
		{
			if ( m_ActiveItem[PLAYER_TWO] != ITEM_TYPE_NONE )
			{
				if ( m_ActiveItem[PLAYER_TWO] == ITEM_T2_BARRIER )
				{
					DeactiveItem(PLAYER_TWO);
					// 2P 스스로 쉴드를 지우는 것이므로 지워지고 스킬 갱신

					printConsole("삭제! \n");
				}
				else
				{
					return;
				}
			}
			m_ActiveItem[PLAYER_TWO] = m_NowItem[PLAYER_TWO];
		}
		m_NowItem[PLAYER_TWO] = ITEM_TYPE_NONE;

		if( thisItem != nullptr )
		{
			thisItem->Active();
		}

		printConsole("Player2 Attack Type %d \n", m_ActiveItem[PLAYER_TWO]);
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
		m_TierItem[TIER_1P_ONE] = (ItemType) CRMrandomGenerator::GetInstance()->GetRandom(ITEM_T1_NONE + 1, ITEM_T1_MAX - 1);
		break;
	case TIER_1P_TWO:
		m_TierItem[TIER_1P_TWO] = (ItemType) CRMrandomGenerator::GetInstance()->GetRandom(ITEM_T2_NONE + 1, ITEM_T2_MAX - 1);
		break;
	case TIER_1P_THREE:
		m_TierItem[TIER_1P_THREE] = (ItemType) CRMrandomGenerator::GetInstance()->GetRandom(ITEM_T3_NONE + 1, ITEM_T3_MAX - 1);
		break;
	case TIER_2P_ONE:
		m_TierItem[TIER_2P_ONE] = (ItemType) CRMrandomGenerator::GetInstance()->GetRandom(ITEM_T1_NONE + 1, ITEM_T1_MAX - 1);
		break;
	case TIER_2P_TWO:
		m_TierItem[TIER_2P_TWO] = (ItemType) CRMrandomGenerator::GetInstance()->GetRandom(ITEM_T2_NONE + 1, ITEM_T2_MAX - 1);
		break;
	case TIER_2P_THREE:
		m_TierItem[TIER_2P_THREE] = (ItemType) CRMrandomGenerator::GetInstance()->GetRandom(ITEM_T3_NONE + 1, ITEM_T3_MAX - 1);
		break;
	case TIER_NONE:
	case TIER_MAX:
	default:
		break;
	}
}

WidgetType CRMitemManager::GetWidgetType( ItemTierType tier )
{
	ItemType thisItem = m_TierItem[tier];
	PlayerNumber player = PLAYER_ONE;
	
	if ( tier > TIER_1P_2P_DIVIDE )
		player = PLAYER_TWO;

	if ( m_ItemPool[thisItem + ( player == PLAYER_TWO ? ITEM_T3_MAX : 0 )] != nullptr )
	{
		if ( thisItem == m_NowItem[player] )
		{
			return m_ItemPool[thisItem + ( player == PLAYER_TWO ? ITEM_T3_MAX : 0 )]->GetWidgetTypeForColor();
		}
		else
		{
			return m_ItemPool[thisItem + ( player == PLAYER_TWO ? ITEM_T3_MAX : 0 )]->GetWidgetTypeForGray();
		}
	}
	
	return WIDGET_NONE;
}

WidgetType CRMitemManager::GetWidgetTypeOfCard( PlayerNumber player )
{
	ItemType thisItemType = m_ActiveItem[player];
	CRMitem* thisItem = m_ItemPool[thisItemType+ (player == PLAYER_TWO ? ITEM_T3_MAX : 0)];
	
	if (thisItem == NULL)
	{
		return WIDGET_NONE;
	}
	
	return thisItem->GetWidgetTypeOfCard();
}

void CRMitemManager::Reset()
{
	m_ActiveItem[PLAYER_ONE] = ITEM_TYPE_NONE;
	m_ActiveItem[PLAYER_TWO] = ITEM_TYPE_NONE;
	m_NowItem[PLAYER_ONE] = ITEM_TYPE_NONE;
	m_NowItem[PLAYER_TWO] = ITEM_TYPE_NONE;
}
