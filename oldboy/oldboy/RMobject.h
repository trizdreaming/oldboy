#pragma once
#include "RMenumSet.h"

class CRMobject
{
public:
	CRMobject(void);
	virtual ~CRMobject(void);

public:
	virtual void	Update() = 0;

	virtual void	Render();

	void			SetObjectType(ObjectType objectType) { m_ObjectType = objectType; }
	void			SetSceneType(SceneType scene) { m_Scene = scene; }
	
	void			SetVisible(bool visible) { m_Visible = visible; }
	void			SetPosition(float x, float y) { m_PositionX = x; m_PositionY = y; }

	float			GetPositionX() { return m_PositionX; }
	float			GetPositionY() { return m_PositionY; }
	ObjectType		GetObjectType() { return m_ObjectType; }

protected:

	void			SetVisibleByScene();

	ObjectType		m_ObjectType;

	bool			m_Visible;
	SceneType		m_Scene;

	float			m_PositionX;
	float			m_PositionY;
	float			m_Width;
	float			m_Height;
	float			m_Alpha;
};

