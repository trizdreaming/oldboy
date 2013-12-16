#pragma once
#include "RMenumSet.h"

//////////////////////////////////////////////////////////////////////////
template <typename IType, int ROW, int COL>
struct array2d_
{
	typedef std::array< std::array<IType, COL>, ROW> type;
};
// 여기서밖에 사용하지 않으므로 여기 붙여놓음
// 만약 다른 곳에서 2중 배열을 중복 사용하게 된다면 RMmacro.h로 옮길 것


class CRMitem;

typedef array2d_<CRMitem*, PLAYER_MAX, ITEM_TYPE_MAX>::type ItemPools;

class CRMitemManager
{
	SINGLETON(CRMitemManager);

private:
	CRMitemManager(void);
	~CRMitemManager(void);

public:
	void		Create();
	void		Release();
	void		Reset();

	void		Update();
	void		RotateItem(ItemTierType tier);

	ItemType	GetActivatedItem(PlayerNumber player) { return m_ActiveItem[player]; }
	void		DeactiveItem(PlayerNumber player) { m_ActiveItem[player] = ITEM_TYPE_NONE; }
	// 각각의 아이템들은 스스로 종료 될 타이밍에 플레이어의 활성화 된 아이템을 비활성화

	bool		IsActivedItemForSelf(PlayerNumber player) const;

	ItemType	GetStackedItem(ItemTierType tier) { return m_TierItem[tier]; }
	float		GetStackPosition(ItemTierType tier) { return m_ItemPosition[tier]; }
	
	WidgetType	GetWidgetType(ItemTierType tier) const;
	WidgetType	GetWidgetTypeOfCard( PlayerNumber player ) const;

private:
	// 발동 가능한 아이템을 체크 할 배열
	std::array<ItemType, PLAYER_MAX>				m_NowItem;

	// 현재 발동 중인 아이템이 들어갈 배열
	std::array<ItemType, PLAYER_MAX>				m_ActiveItem;

	// 아이템 뷰에 차례대로 티어별로 타입을 보여주기 위한 배열
	std::array<ItemType, TIER_MAX>					m_TierItem;
	
	// 각 티어별 좌표값(y축)을 저장
	std::array<float, TIER_MAX>						m_ItemPosition;

	// 실제 아이템이 생성 관리 되는 메모리풀
	ItemPools										m_ItemPools;

	std::array<UINT, TIER_MAX>						m_PrevTimeTierRotate;
	std::array<UINT, TIER_MAX>						m_TimeSliceForTier;
};

