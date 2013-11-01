#include "stdafx.h"
#include "oldboy.h"
#include "RMlabelManager.h"


CRMlabelManager::CRMlabelManager(void)
{
}


CRMlabelManager::~CRMlabelManager(void)
{
}

void CRMlabelManager::CheckError( HRESULT hr )
{
	if ( hr != S_OK )
	{
		printf_s("Text Loading Error! (%d) \n", hr);
	}
}

