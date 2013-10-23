#pragma once
#include "oldboy.h"

class CRMrender
{
private:
	CRMrender(void);
	~CRMrender(void);

public:
	// 싱글톤 관련 메소드
	static CRMrender*	GetInstance();
	static void			ReleaseInstance();

	// 팩토리 & 랜더 타겟 생성 및 반환
	HRESULT	CreateFactory();
	HRESULT	CreateRenderTarget();
	ID2D1Factory*			GetRenderFactory() { return m_pDisplayFactory; }
	ID2D1HwndRenderTarget*	GetRenderTarget() { return m_pDisplayRenderTarget; }

	// 랜더링 시작과 종료
	void	RenderInit();
	HRESULT	RenderEnd();

private:
	ID2D1Factory*			m_pDisplayFactory;
	ID2D1HwndRenderTarget*	m_pDisplayRenderTarget;

	// 싱글톤 멤버 변수
	static CRMrender* m_pInstance;
};

