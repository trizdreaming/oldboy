#include "stdafx.h"
#include "RMmacro.h"
#include "RMchildSelectBar.h"
#include "RMmainLoop.h"
#include "RMxmlLoader.h"
#include "RMmusicData.h"

CRMchildSelectBar::CRMchildSelectBar(void)
{
}


CRMchildSelectBar::~CRMchildSelectBar(void)
{
}

void CRMchildSelectBar::Update()
{
	SetVisibleByScene();

	if ( m_Scene != CRMmainLoop::GetInstance()->GetNowScene() )
	{
		return;
	}

	std::string levelData = CRMxmlLoader::GetInstance()->GetMusicData( CRMmainLoop::GetInstance()->GetPlayMusicName() )->GetLevel();

	int level = std::stoi( levelData );

	switch ( level )
	{
	case 0:
		m_WidgetType = WIDGET_UI_IMAGE_SELECT_BAR_0;
		break;
	case 1:
		m_WidgetType = WIDGET_UI_IMAGE_SELECT_BAR_1;
		break;
	case 2:
		m_WidgetType = WIDGET_UI_IMAGE_SELECT_BAR_2;
		break;
	case 3:
		m_WidgetType = WIDGET_UI_IMAGE_SELECT_BAR_3;
		break;
	case 4:
		m_WidgetType = WIDGET_UI_IMAGE_SELECT_BAR_4;
		break;
	case 5:
		m_WidgetType = WIDGET_UI_IMAGE_SELECT_BAR_5;
		break;
	default:
		m_WidgetType = WIDGET_UI_IMAGE_SELECT_BAR_0;
		break;
	}
}
