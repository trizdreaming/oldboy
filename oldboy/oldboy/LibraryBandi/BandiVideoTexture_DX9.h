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

#include <d3d9.h>
#include "BandiVideoTexture.h"


struct BV_DEVICE_DX9
{
	LPDIRECT3D9			m_d3d9;
	LPDIRECT3DDEVICE9	m_d3d9_device;
	HWND				m_hwnd_parent;
};



class CBandiVideoDevice_DX9 : public CBandiVideoDevice, public BV_DEVICE_DX9
{
public:
	CBandiVideoDevice_DX9();
	virtual ~CBandiVideoDevice_DX9();

	virtual HRESULT	Open(HWND hWnd);
	virtual void	Close();

	virtual HRESULT	Resize(INT width, INT height);

	virtual HRESULT	StartFrame();
	virtual HRESULT	EndFrame();
};



class CBandiVideoTexture_DX9 : public CBandiVideoTexture
{
public:
	CBandiVideoTexture_DX9(BV_DEVICE_DX9* device);
	virtual ~CBandiVideoTexture_DX9();

	virtual HRESULT	Open(INT vid_width, INT vid_height);
	virtual void	Close();

	virtual BYTE*	Lock(INT &pitch);
	virtual void	Unlock();

	virtual HRESULT	Draw(INT x, INT y, INT width, INT height);

	virtual void*	GetObject() { return m_texture; };
	virtual BVL_PIXEL_FORMAT GetFormat() { return m_fmt_bvl; };

protected:
	HRESULT SetVertices(float scr_x, float scr_y, float scr_width, float scr_height);
	int		CalcTexSize(int vid_size, BOOL pow2);

	BV_DEVICE_DX9			m_device;
	LPDIRECT3DTEXTURE9		m_texture;
	LPDIRECT3DVERTEXBUFFER9	m_vertex_buffer;

	D3DFORMAT				m_fmt_d3d;
	BVL_PIXEL_FORMAT		m_fmt_bvl;
	
	int	m_vid_width;
	int m_vid_height;
	int	m_tex_width;
	int m_tex_height;
	int m_pixel_size;
};


