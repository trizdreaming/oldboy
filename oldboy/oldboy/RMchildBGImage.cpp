#include "stdafx.h"
#include "oldboy.h"
#include "RMchildBGImage.h"

CRMchildBGImage::CRMchildBGImage(void)
{
}


CRMchildBGImage::~CRMchildBGImage(void)
{
}

void CRMchildBGImage::Update()
{
	//CRMobject::SetVisibleByScene(); //SM9: 오버라이딩이 아닌 경우 괜히 부모의 이름을 적을 필요 없다.

	SetVisibleByScene();

	return;
}

