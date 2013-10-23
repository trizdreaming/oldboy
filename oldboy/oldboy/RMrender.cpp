#include "stdafx.h"
#include "RMrender.h"


CRMrender* CRMrender::m_pInstance = nullptr;

CRMrender::CRMrender(void):
	m_pDisplayFactory(nullptr),
	m_pDisplayRenderTarget(nullptr)
{
}


CRMrender::~CRMrender(void)
{
	SafeRelease(m_pDisplayFactory);
	SafeRelease(m_pDisplayRenderTarget);
}

HRESULT CRMrender::CreateFactory()
{
	HRESULT hr = S_FALSE;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDisplayFactory);

	return hr;
}

HRESULT CRMrender::CreateRenderTarget()
{
	HRESULT hr = S_FALSE;

	RECT rc;
	GetClientRect(CRMmainLoop::GetInstance()->GetHwnd(), &rc);

	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

	hr = m_pDisplayFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(CRMmainLoop::GetInstance()->GetHwnd(),size),
		&m_pDisplayRenderTarget
		);

	return hr;
}


///////////////////////////////////////////////////////////////////////////////
//RenderInit()과 RenderEnd()는 항상 같이 다녀야 함
//
//Begin 과 End 사이에 각 Object가 각자의 내용을 추가할 수 있도록 함
///////////////////////////////////////////////////////////////////////////////

void CRMrender::RenderInit()
{
	HRESULT hr = S_FALSE;

	m_pDisplayRenderTarget->BeginDraw();
	m_pDisplayRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Aqua));
}

HRESULT CRMrender::RenderEnd()
{
	HRESULT hr = S_FALSE;

	hr =m_pDisplayRenderTarget->EndDraw();

	if(hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		SafeRelease(m_pDisplayRenderTarget);
		SafeRelease(m_pDisplayFactory);
	}

	return hr;
}

///////////////////////////////////////////////////////////////////////////////

CRMrender* CRMrender::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new CRMrender();
	}
	return m_pInstance;
}

void CRMrender::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
