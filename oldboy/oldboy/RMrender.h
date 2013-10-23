#pragma once
#include "oldboy.h"

class CRMrender
{
private:
	CRMrender(void);
	~CRMrender(void);

public:
	static CRMrender* GetInstance();
	static void ReleaseInstance();

public:
	HRESULT CreateFactory();
	HRESULT CreateRenderTarget();
	void	RenderInit();
	HRESULT RenderEnd();


private:
	ID2D1Factory* m_pDisplayFactory;
	ID2D1HwndRenderTarget* m_pDisplayRenderTarget;

private:
	static CRMrender* m_pInstance;
};

