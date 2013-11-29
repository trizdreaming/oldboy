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
	// 공격 구현
	// 1. 공격 키 입력 받기
	// 2. 각 플레이어의 MP 체크
	// 3. MP 상황에 맞춰 공격 가능 최대 티어로 m_NowItem[공격 키 입력 들어온 플레이어]의 아이템 타입 설정 

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
