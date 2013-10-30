#pragma once
#include "RMenumSet.h"

class CRMobject
{
public:
	CRMobject(void);
	virtual ~CRMobject(void);

public:
	virtual void	Update() = 0;

	void			Render();

	void			SetObjectType(Object_Type objectType) { m_ObjectType = objectType; }
	void			SetSceneType(SCENE_TYPE scene) { m_Scene = scene; }
	
	void			SetVisible(bool visible) { m_Visible = visible; }
	void			SetPosition(float x, float y) { m_PositionX = x; m_PositionY = y; }

	float			GetPositionX() { return m_PositionX; }
	float			GetPositionY() { return m_PositionY; }

protected:

	void			SetVisibleByScene();

	Object_Type		m_ObjectType;

	bool			m_Visible;
	SCENE_TYPE		m_Scene;

	float			m_PositionX;
	float			m_PositionY;
	float			m_Width;
	float			m_Height;
	float			m_Alpha;
};

