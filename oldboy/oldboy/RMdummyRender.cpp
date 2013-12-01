#include "stdafx.h"
#include "RMmacro.h"
#include "RMdummyRender.h"
#include "RMrender.h"

CRMdummyRender::CRMdummyRender(void)
{
	CRMrender::GetInstance()->RenderInit();
}


CRMdummyRender::~CRMdummyRender(void)
{
	CRMrender::GetInstance()->RenderEnd();
}
