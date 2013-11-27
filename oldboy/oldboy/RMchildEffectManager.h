#pragma once
#include "RMenumSet.h"

struct Position
{
	float x;
	float y;
};

class CRMchildEffectManager
{
	SINGLETON(CRMchildEffectManager);

private:
	CRMchildEffectManager(void);
	~CRMchildEffectManager(void);

public:
	void		SetFlag( PlayerNumber targetPlayer , float m_PositionX, float m_PositionY );
	void		ResetFlag( int highMask );

	Position	GetStartPosition( PlayerNumber targetPlayer ) const;
	char		GetFlag() { return m_BitFlag; }

private:
	UINT	m_FlagSetter1P; //어떤 비트 포지션에 넣을지 모듈러 연산으로 확인
	UINT	m_FlagSetter2P; //어떤 비트 포지션에 넣을지 모듈러 연산으로 확인
	char	m_BitFlag;
	float	m_Effect1PStartPositionX;
	float	m_Effect1PStartPositionY;
	float	m_Effect2PStartPositionX;
	float	m_Effect2PStartPositionY;
};

