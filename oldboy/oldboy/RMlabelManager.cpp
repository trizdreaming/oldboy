#include "stdafx.h"
#include "RMmacro.h"
#include "RMlabelManager.h"
#include "RMlabel.h"

CRMlabelManager::CRMlabelManager(void) :
	m_DWriteFactory(nullptr)
{
}


CRMlabelManager::~CRMlabelManager(void)
{
	SafeRelease( m_DWriteFactory );

	for ( auto& iter : m_LabelMap )
	{
		auto toBeDelete = iter.second;
		SafeDelete( toBeDelete );
	}
	m_LabelMap.clear();
}

void CRMlabelManager::CheckError( HRESULT hr )
{
	if ( hr != S_OK )
	{
		printConsole( "Text Loading Error! (%d) \n", hr );
	}
}

HRESULT CRMlabelManager::CreateFactory()
{
	HRESULT hr = S_FALSE;

	if ( m_DWriteFactory == nullptr )
	{
		hr = DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_DWriteFactory), reinterpret_cast<IUnknown**>(&m_DWriteFactory) );
	}

	return hr;
}

void CRMlabelManager::AddLabel( std::wstring key , CRMlabel* label )
{
	SafeDelete( m_LabelMap[key] );
	m_LabelMap[key] = label;
}

