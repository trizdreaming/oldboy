#pragma once
#include "RMkeyMapping.h"
#include "RMenumSet.h"

class CRMinput
{
	SINGLETON(CRMinput);

private:
	CRMinput(void);
	~CRMinput(void);

public:
	bool				GetKeyboardInput( KeyTable keyCode );

private:
	int					GetKeyCode( KeyTable keyCode );

};
