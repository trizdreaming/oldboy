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
	void		RotateItem();
	// 일정 시간마다 각 티어의 아이템들이 무작위로 회전하면서 교체 됨
	//   <-- [3티어] -->
	//   <-- [2티어] -->
	//   <-- [1티어] -->

	// 아이템의 세부 작동은 각 아이템 객체들이 확인 할 것임

private:
	// 현재 발동 중인 아이템이 들어갈 배열
	ItemType	m_NowItem[PLAYER_MAX];

	// 아이템 뷰에 차례대로 티어별로 타입을 보여주기 위한 배열
	ItemType	m_TearItem[TIER_MAX];
	
	// 각 티어별 좌표값(y축)을 저장
	float		m_ItemPosition[TIER_MAX];
};

