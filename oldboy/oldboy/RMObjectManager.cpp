#include "stdafx.h"
#include "RMObjectManager.h"

CRMobjectManager*	CRMobjectManager::m_pInstance = nullptr;

CRMobjectManager::CRMobjectManager(void)
{
	m_ObjectList.clear();
}


CRMobjectManager::~CRMobjectManager(void)
{
}

CRMobjectManager* CRMobjectManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new CRMobjectManager();
	}

	return m_pInstance;
}

void CRMobjectManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CRMobjectManager::AddObject( CRMobject* object )
{
	if(object != nullptr)
	{
		m_ObjectList.push_back(object);
	}

	return;
}

void CRMobjectManager::Update()
{
	for(auto &iter = m_ObjectList.begin(); iter != m_ObjectList.end(); ++iter)
	{
		(*iter)->Update();
	}
}

void CRMobjectManager::Render()
{
	m_ObjectList.sort();

	for(auto &iter = m_ObjectList.begin(); iter != m_ObjectList.end(); ++iter)
	{
		(*iter)->Render();
	}
}




