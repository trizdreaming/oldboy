#pragma once
#include "RMobject.h"

class CRMchildNote :
	public CRMobject
{
public:
	CRMchildNote(void);
	virtual ~CRMchildNote(void);

	virtual void	Update();
	virtual void	Render();
	virtual void	SetWidgetType(WidgetType widgetType);

private:
	WidgetType		m_Original_type;
};

