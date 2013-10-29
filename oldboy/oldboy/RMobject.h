#pragma once

#include "oldboy.h"

enum SCENE_TYPE{
	SCENE_TITLE,
	SCENE_PLAY,
	SCENE_RESULT,
	NO_SCENE
};

enum LayerType
{
	LAYER_BACKGROUND,
	LAYER_NOTE,
	LAYER_SHUTTER,
	LAYER_LABEL,
	NO_LAYER
};

enum Object_Type
{
	OBJECT_BG_IMAGE_TITLE,
	OBJECT_BG_IMAGE_PLAY,
	OBJECT_NOTE_NORMAL_1,
	OBJECT_NOTE_NORMAL_2,
	OBJECT_SHUTTER,
	NO_OBJECT
};

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

