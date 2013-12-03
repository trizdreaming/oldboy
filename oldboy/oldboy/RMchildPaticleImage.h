#pragma once
#include "rmobject.h"

//////////////////////////////////////////////////////////////////////////
//파티클은 NN프레임 워크를 참고해서 제작 중
//컬러 관련 변경은 적용하지 않는 것으로 함
//카드 회전 및 잔상(ghost 효과 제외)으로 아이템 발동 표현
//////////////////////////////////////////////////////////////////////////

class CRMchildPaticleImage:
	public CRMobject
{
public:
	CRMchildPaticleImage(void);
	~CRMchildPaticleImage(void);

public:
	void SetMatrix();
//	void Update();


	void SetParentMatrix( D2D1::Matrix3x2F matrix ) { m_ParentMatrix = matrix; }
	/*
	void SetPosition( NNPoint position ) { m_Position = position; }
	void SetPosition( float x, float y ) { m_Position.SetPoint(x,y); }
	*/
	void SetStartSpeed( float speed ) { m_StartSpeed = speed; }
	void SetEndSpeed( float speed ) { m_EndSpeed = speed; }
	void SetStartScaleX( float scaleX ) { m_StartScaleX = scaleX; }
	void SetStartScaleY( float scaleY ) { m_StartScaleY = scaleY; }
	void SetEndScaleX( float scaleX ) { m_EndScaleX = scaleX; }
	void SetEndScaleY( float scaleY ) { m_EndScaleY = scaleY; }
	void SetStartScale( float scaleX, float scaleY ) { m_StartScaleX = scaleX; m_StartScaleY = scaleY; }
	void SetEndScale( float scaleX, float scaleY ) { m_EndScaleX = scaleX; m_EndScaleY = scaleY; }
	void SetStartRotationSpeed( float rotation ) { m_StartRotationSpeed = rotation; }
	void SetEndRotationSpeed( float rotation ) { m_EndRotationSpeed = rotation; }
	void SetVisible( bool visible ) { m_Visible = visible; }
	void SetLifeTime( float lifetime ) { m_LifeTime = lifetime; }
	void SetDirection( float direction ) { m_Direction = direction; }

public:
	D2D1::Matrix3x2F GetParentMatrix() const { return m_ParentMatrix; }
	D2D1::Matrix3x2F GetMatrix() const { return m_Matrix; }
	/*
	NNPoint GetPosition() { return m_Position; }
	*/
	float GetStartSpeed() const { return m_StartSpeed; }
	float GetEndSpeed() const { return m_EndSpeed; }
	float GetStartScaleX() const { return m_StartScaleX; }
	float GetStartScaleY() const { return m_StartScaleY; }
	float GetEndScaleX() const { return m_EndScaleX; }
	float GetEndScaleY() const { return m_EndScaleY; }
	float GetImageWidth() const { return m_ImageWidth; }
	float GetImageHeight() const { return m_ImageHeight; }
	float GetStartRotationSpeed() const { return m_StartRotationSpeed; }
	float GetEndRotationSpeed() const { return m_EndRotationSpeed; }
	float GetLifeTime() const { return m_LifeTime; }
	float GetNowLifeTime() const { return m_NowLifeTime; }
	bool IsVisible() const { return m_Visible; }
	float GetDirection() { return m_Direction; }

private:
	D2D1::Matrix3x2F m_ParentMatrix;
	D2D1::Matrix3x2F m_Matrix;

	float m_StartSpeed, m_EndSpeed;
	float m_StartScaleX, m_EndScaleX;
	float m_StartScaleY, m_EndScaleY;
	float m_ImageWidth;
	float m_ImageHeight;
	float m_StartRotationSpeed, m_EndRotationSpeed; // Degree
	float m_LifeTime;
	float m_NowLifeTime;
	bool m_Visible;

	float m_Speed;
	float m_ScaleX, m_ScaleY;
	float m_Rotation;
	float m_RotationSpeed;
	float m_Direction;
};

