////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// BandiVideoLibrary 2.1
/// 
/// Copyright(C) 2008-2011 BandiSoft.com All rights reserved.
///
/// Visit http://www.bandisoft.com for more information.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "bandivid.h"


class CBandiVideoDevice
{
public:
	virtual ~CBandiVideoDevice() {};

	virtual HRESULT	Open(HWND hWnd) PURE;
	virtual void	Close() PURE;

	virtual HRESULT	Resize(INT width, INT height) PURE;

	virtual HRESULT	StartFrame() PURE;
	virtual HRESULT	EndFrame() PURE;
};



class CBandiVideoTexture
{
public:
	virtual ~CBandiVideoTexture() {};

	virtual HRESULT	Open(INT vid_width, INT vid_height) PURE;
	virtual void	Close() PURE;

	virtual BYTE*	Lock(INT &pitch) PURE;
	virtual void	Unlock() PURE;

	virtual HRESULT	Draw(INT x, INT y, INT width, INT height) PURE;

	virtual void*	GetObject() PURE;
	virtual BVL_PIXEL_FORMAT GetFormat() PURE;
};
