#include "stdafx.h"
#include "RMchildDangerLine.h"
#include "RMmainLoop.h"
#include "RMdefine.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"
#include "RMsound.h"


CRMchildDangerLine::CRMchildDangerLine(void) :
	m_AnimationFrame(0)
{
}


CRMchildDangerLine::~CRMchildDangerLine(void)
{
}


void CRMchildDangerLine::Update()
{
	if ( m_Scene != CRMmainLoop::GetInstance()->GetNowScene() )
	{
		m_Visible = false;
		return;
	}
	m_Visible = true;

	int playerHP = 0;
	if ( m_PlayerNumber == PLAYER_ONE )
	{
		if ( CRMplayer1P::GetInstance()->IsDead() )
		{
			m_Visible = false;
			m_Alpha = 0.0f;
			return;
		}
		playerHP = CRMplayer1P::GetInstance()->GetHP();
	}
	else
	{
		if ( CRMplayer2P::GetInstance()->IsDead() )
		{
			m_Visible = false;
			m_Alpha = 0.0f;
			return;
		}
		playerHP = CRMplayer2P::GetInstance()->GetHP();
	}
	

	

	UINT animationSpeed = 0;
	if ( playerHP > 59 )
	{
		m_Alpha = 0.0f;
		m_AnimationFrame = 0;
		return;
	}

	if ( playerHP < 31 )
	{
		animationSpeed = 10;
	}
	else
	{
		animationSpeed = 50;
	}
	
	++m_AnimationFrame;

	m_Alpha = static_cast<float>(m_AnimationFrame) / animationSpeed;

	if ( m_AnimationFrame > animationSpeed )
	{
		m_Alpha = 1 - ( static_cast<float>( m_AnimationFrame - animationSpeed ) / animationSpeed );
	}

	if ( m_AnimationFrame > ( animationSpeed * 2 ) )
	{
		m_AnimationFrame = 0;
		if ( playerHP < 31 )
		{
			CRMsound::GetInstance()->PlayEffectTier(SOUND_EFFECT_PLAY_DANGER_SIREN1);
		}
	}
}