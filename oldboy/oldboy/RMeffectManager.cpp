#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMeffectManager.h"

CRMeffectManager::CRMeffectManager(void):
	m_BitFlag(0x00),
	m_Effect1PStartPositionX(0.f),
	m_Effect1PStartPositionY(0.f),
	m_Effect2PStartPositionX(0.f),
	m_Effect2PStartPositionY(0.f),
	m_FlagSetter1P(0),
	m_FlagSetter2P(0)
{
}

CRMeffectManager::~CRMeffectManager(void)
{
}


//////////////////////////////////////////////////////////////////////////////
//BitFlag 사용법															//
//각 비트는 어떤 이펙트를 play 화면에 보여줘야할지 말아야 할지 스위칭		//
//한 화면에 최대 8개까지 판정 가능											//
//////////////////////////////////////////////////////////////////////////////

void CRMeffectManager::SetFlag( PlayerNumber targetPlayer , float positionX, float positionY )
{
	// 노트를 뿌려줄 포지션 결정
	// judgeManager에서 위치값을 던져주면 저장 했다가
	// 이펙트 업데이터가 포지션을 받아 쓸 수 있도록 함
	
	// printConsole( "1P flag : %d , 2P flag: %d \n", m_FlagSetter1P, m_FlagSetter2P );

	if ( targetPlayer == PLAYER_ONE )
	{
		m_FlagSetter1P = ++m_FlagSetter1P % 4;

		m_Effect1PStartPositionX = positionX;
		m_Effect1PStartPositionY = positionY;

		m_BitFlag |= ( 0x0010 << (3 - m_FlagSetter1P) );

		// printConsole("1P BitFlag 발동! %x \n", m_BitFlag);
	}
	else
	{
		m_FlagSetter2P = ++m_FlagSetter2P % 4;

		m_Effect2PStartPositionX = positionX;
		m_Effect2PStartPositionY = positionY;

		m_BitFlag |= ( 0x0001 << (3 - m_FlagSetter2P) );

		// printConsole("2P BitFlag 발동! %x \n", m_BitFlag);
	}
	
}

void CRMeffectManager::ResetFlag( int highMask )
{
	if ( highMask == 1 )
	{
		m_BitFlag &= 0x000F;
	}
	else
	{
		m_BitFlag &= 0x00F0;
	}
}

Position CRMeffectManager::GetStartPosition( PlayerNumber targetPlayer ) const
{
	Position pos = { 0, };

	if ( targetPlayer == PLAYER_ONE )
	{
		pos.x = m_Effect1PStartPositionX;
		pos.y = m_Effect1PStartPositionY;
	}
	else
	{
		pos.x = m_Effect2PStartPositionX;
		pos.y = m_Effect2PStartPositionY;
	}

	return pos;
}



