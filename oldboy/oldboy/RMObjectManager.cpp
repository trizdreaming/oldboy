#include "stdafx.h"
#include "RMObjectManager.h"

CRMobjectManager*	CRMobjectManager::m_pInstance = nullptr;

CRMobjectManager::CRMobjectManager(void)
{
	m_ObjectListLayer1.clear();
	m_ObjectListLayer2.clear();
	m_ObjectListLayer3.clear();
	m_ObjectListLayer4.clear();
}


CRMobjectManager::~CRMobjectManager(void)
{
	for(auto &iter = m_ObjectListLayer1.begin(); iter != m_ObjectListLayer1.end(); ++iter)
	{
		SafeDelete(*iter);
	}
	m_ObjectListLayer1.clear();
	for(auto &iter = m_ObjectListLayer2.begin(); iter != m_ObjectListLayer2.end(); ++iter)
	{
		SafeDelete(*iter);
	}
	m_ObjectListLayer2.clear();
	for(auto &iter = m_ObjectListLayer3.begin(); iter != m_ObjectListLayer3.end(); ++iter)
	{
		SafeDelete(*iter);
	}
	m_ObjectListLayer3.clear();
	for(auto &iter = m_ObjectListLayer4.begin(); iter != m_ObjectListLayer4.end(); ++iter)
	{
		SafeDelete(*iter);
	}
	m_ObjectListLayer4.clear();
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

void CRMobjectManager::AddObject( CRMobject* object, LayerType layer )
{
	if(object != nullptr)
	{
		switch (layer)
		{
		case Layer_1:
			m_ObjectListLayer1.push_back(object);
			break;
		case Layer_2:
			m_ObjectListLayer2.push_back(object);
			break;
		case Layer_3:
			m_ObjectListLayer3.push_back(object);
			break;
		case Layer_4:
			m_ObjectListLayer4.push_back(object);
			break;
		case NO_Layer:
			break;
		default:
			break;
		}
	}

	return;
}

void CRMobjectManager::Update()
{
	for(auto &iter = m_ObjectListLayer1.begin(); iter != m_ObjectListLayer1.end(); ++iter)
	{
		(*iter)->Update();
	}
	for(auto &iter = m_ObjectListLayer2.begin(); iter != m_ObjectListLayer2.end(); ++iter)
	{
		(*iter)->Update();
	}
	for(auto &iter = m_ObjectListLayer3.begin(); iter != m_ObjectListLayer3.end(); ++iter)
	{
		(*iter)->Update();
	}
	for(auto &iter = m_ObjectListLayer4.begin(); iter != m_ObjectListLayer4.end(); ++iter)
	{
		(*iter)->Update();
	}
}

void CRMobjectManager::Render()
{
	m_ObjectListLayer1.sort();

	for(auto &iter = m_ObjectListLayer1.begin(); iter != m_ObjectListLayer1.end(); ++iter)
	{
		(*iter)->Render();
	}
	for(auto &iter = m_ObjectListLayer2.begin(); iter != m_ObjectListLayer2.end(); ++iter)
	{
		(*iter)->Render();
	}
	for(auto &iter = m_ObjectListLayer3.begin(); iter != m_ObjectListLayer3.end(); ++iter)
	{
		(*iter)->Render();
	}
	for(auto &iter = m_ObjectListLayer4.begin(); iter != m_ObjectListLayer4.end(); ++iter)
	{
		(*iter)->Render();
	}
}




