#include "stdafx.h"
#include "RMchildPaticleImage.h"
#include "RMmacro.h"
#include "RMrender.h"


CRMchildPaticleImage::CRMchildPaticleImage(void)
	: 
	//m_Position(0.f,0.f), 
	m_StartScaleX(0.f), 
	m_StartScaleY(0.f), 
	m_EndScaleX(0.f), 
	m_EndScaleY(0.f), 
	m_ImageWidth(0.f), 
	m_ImageHeight(0.f), 
	m_StartRotationSpeed(0.f), 
	m_EndRotationSpeed(0.f),
	m_LifeTime(0.f), 
	m_NowLifeTime(0.f), 
	m_Visible(true),
	m_Speed(0.f), 
	m_ScaleX(1.f), 
	m_ScaleY(1.f), 
	m_Rotation(0.f), 
	m_RotationSpeed(0.f)
{
}


CRMchildPaticleImage::~CRMchildPaticleImage(void)
{
}

void CRMchildPaticleImage::SetMatrix()
{
	m_Matrix = D2D1::Matrix3x2F::Translation( -m_ImageWidth/2.f, -m_ImageHeight/2.f ) *
		D2D1::Matrix3x2F::Rotation( m_Rotation ) *
		D2D1::Matrix3x2F::Scale( m_ScaleX, m_ScaleY ) *
		//D2D1::Matrix3x2F::Translation( m_Position.GetX(), m_Position.GetY() );

	m_Matrix = m_Matrix * m_ParentMatrix;
}
