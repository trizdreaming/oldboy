#include "stdafx.h"
#include "oldboy.h"
#include "RMlabelManager.h"
#include "RMlabel.h"


CRMlabelManager::CRMlabelManager(void) :
	m_DWriteFactory(nullptr)
{
	m_LabelMap.clear();
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
#ifdef DEBUG
		printf_s("Text Loading Error! (%d) \n", hr);
#endif // DEBUG
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

