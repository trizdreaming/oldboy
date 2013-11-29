#pragma once
#include "RMenumSet.h"

class CRMitem;

class CRMitemManager
{
	SINGLETON(CRMitemManager);

private:
	CRMitemManager(void);
	~CRMitemManager(void);

public:
	void		Create();
	void		Release();

	void		Update();
	void		RotateItem(ItemTierType tier);
	// 일정 시간마다 각 티어의 아이템들이 무작위로 회전하면서 교체 됨
	//   <-- [3티어] -->
	//   <-- [2티어] -->
	//   <-- [1티어] -->

	// 아이템의 세부 작동은 각 아이템 객체들이 확인 할 것임

	ItemType	GetActivatedItem(PlayerNumber player) { return m_NowItem[player]; }
	ItemType	GetStackedItem(ItemTierType tier) { return m_TierItem[tier]; }
	float		GetStackPosition(ItemTierType tier) { return m_ItemPosition[tier]; }

private:
	// 현재 발동 중인 아이템이 들어갈 배열
	std::array<ItemType, PLAYER_MAX>	m_NowItem;

	// 아이템 뷰에 차례대로 티어별로 타입을 보여주기 위한 배열
	std::array<ItemType, TIER_MAX>		m_TierItem;
	
	// 각 티어별 좌표값(y축)을 저장
	std::array<float, TIER_MAX>			m_ItemPosition;

	// 실제 아이템이 생성 관리 되는 메모리풀
	std::array<CRMitem*, ITEM_TYPE_MAX * 2>	m_ItemPool;

	std::array<UINT, TIER_MAX>	m_TimeOfTierRotate;
};

