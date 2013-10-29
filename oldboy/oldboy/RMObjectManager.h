#pragma once
#include "oldboy.h"
#include "RMobject.h"
#include <list>
#include "RMEnumLayerType.h"

class CRMobjectManager
{
private:
	CRMobjectManager(void);
	~CRMobjectManager(void);

public:
	static CRMobjectManager*	GetInstance();
	static void					ReleaseInstance();

	void	Update();
	void	Render();

	void	AddObject(CRMobject* object, LayerType layer);
	std::list<CRMobject*>*		GetObjectListLayer(LayerType layer);
private:
	std::list<CRMobject*>		m_ObjectListLayer1; //SM9: 변수 이름 뒤에 숫자 붙이지 말고, 정확한 이름으로 표시할 것. 예를 들어 Background라든가...
	std::list<CRMobject*>		m_ObjectListLayer2;
	std::list<CRMobject*>		m_ObjectListLayer3;
	std::list<CRMobject*>		m_ObjectListLayer4;

	static	CRMobjectManager*	m_pInstance;
};

