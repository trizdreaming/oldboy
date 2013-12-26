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

	virtual void	SetWidgetType(WidgetType widgetType) { m_WidgetType = widgetType; }
	void			SetSceneType(SceneType scene) { m_Scene = scene; }
	
	void			SetVisible(bool visible) { m_Visible = visible; }
	bool			GetVisible() { return m_Visible; }
	virtual void	SetPosition(float x, float y) { m_PositionX = x; m_PositionY = y; }
	void			SetPosition(int x, int y) { SetPosition(static_cast<float>(x), static_cast<float>(y)); }

	float			GetPositionX() { return m_PositionX; }
	float			GetPositionY() { return m_PositionY; }
	float			GetAlpha() { return m_Alpha; }
	SceneType		SetSceneType() { return m_Scene; }
	WidgetType		GetWidgetType() { return m_WidgetType; }

	void			SetPlayer( PlayerNumber playerNumber ) { m_PlayerNumber = playerNumber; }
	PlayerNumber	GetPlayer() { return m_PlayerNumber; }

protected:

	void			SetVisibleByScene();
	WidgetType		m_WidgetType;

	PlayerNumber	m_PlayerNumber;
	bool			m_Visible;
	SceneType		m_Scene;

	D2D1::Matrix3x2F m_PrevMatrix;
	D2D1::Matrix3x2F m_Matrix;

	float			m_ScaleX;
	float			m_ScaleY;
	float			m_Rotation;

	float			m_PositionX;
	float			m_PositionY;
	float			m_Width;
	float			m_Height;
	float			m_Alpha;
};

