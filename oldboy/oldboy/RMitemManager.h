#pragma once
#include "RMenumSet.h"

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
	// 1P용 아이템 1~3티어까지 식별을 위한 enum이 들어갈 배열
	ItemType	m_Player1Item[3];
	ItemType	m_Player2Item[3];
};

