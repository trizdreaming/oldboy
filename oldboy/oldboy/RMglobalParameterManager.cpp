#include "stdafx.h"
#include "RMglobalParameterManager.h"
#include "RMdefine.h"


CRMglobalParameterManager::CRMglobalParameterManager(void)
{
	Initialize();
}


CRMglobalParameterManager::~CRMglobalParameterManager(void)
{
}

void CRMglobalParameterManager::Initialize()
{
	m_ShutterP1PositionY = SHUTTER_START_POSITION_Y;
	m_ShutterP2PositionY = SHUTTER_START_POSITION_Y;
}
