#include "stdafx.h"
#include "oldboy.h"
#include "RMinput.h"

CRMinput::CRMinput(void)
{
}


CRMinput::~CRMinput(void)
{
}

bool CRMinput::GetKeyboardInput( KeyTable keyCode )
{
	
	if ( GetAsyncKeyState( GetKeyCode( keyCode ) ) & 0x0001 )
	{
		return true;
	}

	return false;
}

int CRMinput::GetKeyCode( KeyTable keyCode )
{
	switch (keyCode)
	{
	case ESCAPE:
		return VK_ESCAPE;
	case P1_TARGET1:
		return VK_A;
	case P1_TARGET2:
		return VK_D;
	case P1_ATTACK:
		return VK_S;
	case P2_TARGET1:
		return VK_LEFT;
	case P2_TARGET2:
		return VK_RIGHT;
	case P2_ATTACK:
		return VK_DOWN;
	case NO_INPUT:
	default:
		return VK_RETURN;
	}

}
