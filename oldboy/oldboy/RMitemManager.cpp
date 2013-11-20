#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMitem.h"
#include "RMitemManager.h"


CRMitemManager::CRMitemManager(void) :
	m_Player1T1item(ITEM_T1_NONE),
	m_Player1T2item(ITEM_T2_NONE),
	m_Player1T3item(ITEM_T3_NONE),
	m_Player2T1item(ITEM_T1_NONE),
	m_Player2T2item(ITEM_T2_NONE),
	m_Player2T3item(ITEM_T3_NONE)
{
	ZeroMemory(m_NowItem, sizeof(m_NowItem));
	ZeroMemory(m_Player1ItemPosition, sizeof(m_Player1ItemPosition));
	ZeroMemory(m_Player2ItemPosition, sizeof(m_Player2ItemPosition));
}


CRMitemManager::~CRMitemManager(void)
{
}
