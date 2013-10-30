#include "stdafx.h"
#include "oldboy.h"

#include "RMobject.h"
#include "RMObjectManager.h"

CRMobjectManager*	CRMobjectManager::m_pInstance = nullptr;

CRMobjectManager::CRMobjectManager(void)
{
	m_ObjectListLayerBackground.clear();
	m_ObjectListLayerNote.clear();
	m_ObjectListLayerShutter.clear();
	m_ObjectListLayerLabel.clear();
}


CRMobjectManager::~CRMobjectManager(void)
{
	for ( auto &iter : m_ObjectListLayerBackground )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerBackground.clear();

	for ( auto &iter : m_ObjectListLayerNote )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerNote.clear();

	for ( auto &iter : m_ObjectListLayerShutter )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerShutter.clear();

	for ( auto &iter : m_ObjectListLayerLabel )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerLabel.clear();
}

CRMobjectManager* CRMobjectManager::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new CRMobjectManager();
	}

	return m_pInstance;
}

void CRMobjectManager::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CRMobjectManager::AddObject( CRMobject* object, LayerType layer )
{
	if ( object != nullptr )
	{
		switch ( layer )
		{
		case LAYER_BACKGROUND:
			m_ObjectListLayerBackground.push_back(object);
			break;
		case LAYER_NOTE:
			m_ObjectListLayerNote.push_back(object);
			break;
		case LAYER_SHUTTER:
			m_ObjectListLayerShutter.push_back(object);
			break;
		case LAYER_LABEL:
			m_ObjectListLayerLabel.push_back(object);
			break;
		case NO_LAYER:
			break;
		default:
			break;
		}
	}

	return;
}

void CRMobjectManager::Update()
{
	for ( auto &iter : m_ObjectListLayerBackground )
	{
		iter->Update();
	}
	for ( auto &iter : m_ObjectListLayerNote )
	{
		iter->Update();
	}
	for ( auto &iter : m_ObjectListLayerShutter )
	{
		iter->Update();
	}
	for ( auto &iter : m_ObjectListLayerLabel )
	{
		iter->Update();
	}
}

void CRMobjectManager::Render()
{
	m_ObjectListLayerBackground.sort();

	for ( auto &iter : m_ObjectListLayerBackground )
	{
		iter->Render();
	}
	for ( auto &iter : m_ObjectListLayerNote )
	{
		iter->Render();
	}
	for ( auto &iter : m_ObjectListLayerShutter )
	{
		iter->Render();
	}
	for ( auto &iter : m_ObjectListLayerLabel )
	{
		iter->Render();
	}
}

std::list<CRMobject*>* CRMobjectManager::GetObjectListLayer( LayerType layer )
{
	switch ( layer )
	{
	case LAYER_BACKGROUND:
		return &m_ObjectListLayerBackground;
	case LAYER_NOTE:
		return &m_ObjectListLayerNote;
	case LAYER_SHUTTER:
		return &m_ObjectListLayerShutter;
	case LAYER_LABEL:
		return &m_ObjectListLayerLabel;
	case NO_LAYER:
		return &m_ObjectListLayerBackground;
	default:
		return &m_ObjectListLayerBackground;
	}
	return &m_ObjectListLayerBackground;
}




