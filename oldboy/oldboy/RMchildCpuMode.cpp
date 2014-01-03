#include "stdafx.h"
#include "RMmacro.h"
#include "RMchildCpuMode.h"
#include "RMmainLoop.h"
#include "RMdefine.h"


CRMchildCpuMode::CRMchildCpuMode(void) :
	m_AnimationFrame(0)
{
}


CRMchildCpuMode::~CRMchildCpuMode(void)
{
}


void CRMchildCpuMode::Update()
{
	if ( m_Scene != CRMmainLoop::GetInstance()->GetNowScene() )
	{
		m_AnimationFrame = 0;
		m_Alpha = 0.f;
		m_Visible = false;
		return;
	}


	if ( CRMmainLoop::GetInstance()->IsAirTomoOn() )
	{
		m_Visible = true;

		++m_AnimationFrame;

		m_Alpha = static_cast<float>(m_AnimationFrame) / PLAY_ALERT_GROW_ANIMATION_SPEED;

		if ( m_AnimationFrame > PLAY_ALERT_GROW_ANIMATION_SPEED )
		{
			m_Alpha = 1 - ( static_cast<float>( m_AnimationFrame - PLAY_ALERT_GROW_ANIMATION_SPEED ) / PLAY_ALERT_GROW_ANIMATION_SPEED );
		}

		if ( m_AnimationFrame > ( PLAY_ALERT_GROW_ANIMATION_SPEED * 2 ) )
		{
			m_AnimationFrame = 0;
		}
	}




}
