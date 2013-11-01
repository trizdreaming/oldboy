#pragma once
#include "rmobject.h"

class CRMchildEffectImage:
		public CRMobject
{
	SINGLETON(CRMchildEffectImage);

public:
	CRMchildEffectImage(void);
	~CRMchildEffectImage(void);

	virtual void	Update();
	void HitEffectFlag(); //비트가 비었는지 아닌지 확인해 넣어주는 메소드

private:
	unsigned char m_pBitFlag;
};

