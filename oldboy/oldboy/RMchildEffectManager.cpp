#include "stdafx.h"
#include "RMchildEffectManager.h"

CRMchildEffectManager::CRMchildEffectManager(void):
	m_BitFlag(0x00),
	m_EffectStartPositionX(0.f),
	m_EffectStartPositionY(0.f),
	m_FlagSetter1P(0),
	m_FlagSetter2P(0)
{
}


CRMchildEffectManager::~CRMchildEffectManager(void)
{
}


//////////////////////////////////////////////////////////////////
//BitFlag 사용법													//
//각 비트는 어떤 이펙트를 play 화면에 보여줘야할지 말아야 할지 스위칭		//
//한 화면에 최대 8개까지 판정 가능								    //
//////////////////////////////////////////////////////////////////

void CRMchildEffectManager::SetFlag( PlayerNumber targetPlayer , float m_PositionX, float m_PositionY )
{
	//노트를 뿌려줄 포지션 결정
	//judgeManager에서 위치값을 던져주면 저장 했다가
	//이펙트 업데이터가 포지션을 받아 쓸 수 있도록 함
	m_EffectStartPositionX = m_PositionX;
	m_EffectStartPositionY = m_PositionY;
	
	//잉여로운 BitFlag 설정
	//모듈러 연산을 통해서 각 비트에 플래그를 세울 수 있도록 함
	int flagPosition1 = 0;
	int flagPosition2 = 0;
	switch (targetPlayer)
	{
	case PLAYER_ONE:
		flagPosition1 = m_FlagSetter1P % 4;
		switch (flagPosition1)
		{
		case 0:
			m_BitFlag = ( m_BitFlag | 0x80);
			++m_FlagSetter1P;
			break;
		case 1:
			m_BitFlag = ( m_BitFlag | 0x40);
			++m_FlagSetter1P;
			break;
		case 2:
			m_BitFlag = ( m_BitFlag | 0x20);
			++m_FlagSetter1P;
			break;
		case 3:
			m_BitFlag = ( m_BitFlag | 0x10);
			++m_FlagSetter1P;
			break;
		default:
			printf_s("Flag Setting Error\n");
			break;
		}
		break;
	case PLAYER_TWO:
		flagPosition2 = m_FlagSetter2P % 4;
		switch (flagPosition2)
		{
		case 0:
			m_BitFlag = ( m_BitFlag | 0x08);
			++m_FlagSetter2P;
			break;
		case 1:
			m_BitFlag = ( m_BitFlag | 0x04);
			++m_FlagSetter2P;
			break;
		case 2:
			m_BitFlag = ( m_BitFlag | 0x02);
			++m_FlagSetter2P;
			break;
		case 3:
			m_BitFlag = ( m_BitFlag | 0x01);
			++m_FlagSetter2P;
			break;
		default:
			printf_s("Flag Setting Error\n");
			break;
		}
		break;
	case NO_PLAYER:
		break;
	default:
		break;
	}
}

void CRMchildEffectManager::ResetFlag()
{
	if(!m_BitFlag)
	{
		return;
	}
	else
	{
		m_BitFlag = 0x00;
	}
}


