#pragma once

#include "oldboy.h"
#include "RMEnumObjectType.h"
#include "RMEnumSceneType.h"

class CRMobject
{
public:
	CRMobject(void);
	virtual ~CRMobject(void);

public:
	virtual void	Update();		// 자식에서 오버라이딩 후 부모 호출

	void			Render();
	void			SetKey(EnumObjectType key) { m_Key = key; }

	void			SetScene(SCENE_TYPE scene) { m_Scene = scene; }
	
	void			SetVisible(bool visible) { m_Visible = visible; }
	void			SetPosition(float x, float y) { m_PositionX = x; m_PositionY = y; }

protected:

	void			SetVisibleByScene();

	EnumObjectType	m_Key;

	bool			m_Visible;
	SCENE_TYPE		m_Scene;

	float			m_PositionX;
	float			m_PositionY;
	float			m_Width;
	float			m_Height;
	float			m_Alpha;
};

