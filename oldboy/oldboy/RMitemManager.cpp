#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMitem.h"
#include "RMitemManager.h"


CRMitemManager::CRMitemManager(void)
{
	ZeroMemory(m_NowItem, sizeof(m_NowItem));
	ZeroMemory(m_Player1Item, sizeof(m_Player1Item));
	ZeroMemory(m_Player2Item, sizeof(m_Player2Item));
	ZeroMemory(m_Player1ItemPosition, sizeof(m_Player1ItemPosition));
	ZeroMemory(m_Player2ItemPosition, sizeof(m_Player2ItemPosition));
}


CRMitemManager::~CRMitemManager(void)
{
}
