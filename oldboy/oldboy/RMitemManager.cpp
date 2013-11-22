#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMitem.h"
#include "RMitemManager.h"


CRMitemManager::CRMitemManager(void)
{
	ZeroMemory(m_TearItem, sizeof(m_TearItem));
	ZeroMemory(m_NowItem, sizeof(m_NowItem));
	ZeroMemory(m_ItemPosition, sizeof(m_ItemPosition));
}


CRMitemManager::~CRMitemManager(void)
{
}
