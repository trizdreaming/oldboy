////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// BandiVideoLibrary 2.1
/// 
/// Copyright(C) 2008-2011 BandiSoft.com All rights reserved.
///
/// Visit http://www.bandisoft.com for more information.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "BandiVideoTexture_DX9.h"

static BOOL GetTextureFormat(LPDIRECT3D9 d3d9, D3DFORMAT &texture_fmt_d3d, BVL_PIXEL_FORMAT &texture_fmt_bvl, int &texture_pixel_size)
{
	struct
	{
		D3DFORMAT			d3d_fmt;
		BVL_PIXEL_FORMAT	bvl_fmt;
		int					pixel_size;
	} fmt_list[] =
	{
		{ D3DFMT_X8R8G8B8,  BVLPF_X8R8G8B8,	4},
		{ D3DFMT_R8G8B8,    BVLPF_R8G8B8,	3},
		{ D3DFMT_R5G6B5,    BVLPF_R5G6B5,	2},
		{ D3DFMT_X1R5G5B5,  BVLPF_R5G5B5,	2},
	};

	D3DDISPLAYMODE d3ddm;
	HRESULT	hr = d3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	if(SUCCEEDED(hr))
	{
		int fmt_count = sizeof(fmt_list)/sizeof(fmt_list[0]);
		for(int i = 0; i < fmt_count; i++ )
		{
			if(SUCCEEDED(d3d9->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3ddm.Format, 0, D3DRTYPE_TEXTURE, fmt_list[i].d3d_fmt)))
			{
				texture_fmt_d3d = fmt_list[i].d3d_fmt;
				texture_fmt_bvl = fmt_list[i].bvl_fmt;
				texture_pixel_size = fmt_list[i].pixel_size;
				return TRUE;
			}
		}
	}

	texture_fmt_d3d = D3DFMT_UNKNOWN;
	texture_fmt_bvl = BVLPF_NULL;
	texture_pixel_size = NULL;

	return FALSE;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// CBandiVideoDevice_DX9 class
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
CBandiVideoDevice_DX9::CBandiVideoDevice_DX9()
{
	// BV_DEVICE_DX9 structure
	m_d3d9 = NULL;
	m_d3d9_device = NULL;
	m_hwnd_parent = NULL;
}


CBandiVideoDevice_DX9::~CBandiVideoDevice_DX9()
{
	Close();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// Open Direct3D9 Device.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT	CBandiVideoDevice_DX9::Open(HWND hWnd)
{
	HRESULT	hr;
	LPDIRECT3D9				d3d9 = NULL;
	LPDIRECT3DDEVICE9		d3d9_device = NULL;
	D3DDISPLAYMODE			d3ddm;
	D3DPRESENT_PARAMETERS	d3dpp = {0};;

	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if(d3d9 == NULL)
	{
		ASSERT(0);
		return E_FAIL;
	}

	hr = d3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	if(FAILED(hr))
	{
		ASSERT(0);
		return hr;
	}

	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	if(FAILED(d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
									D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &d3d9_device)))
	{
		ASSERT(0);
		if(FAILED(d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
									D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3d9_device)))
		{
			ASSERT(0);
			if(FAILED(d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3d9_device)))
			{
				ASSERT(0);
				d3d9->Release();
				return E_FAIL;
			}
		}
	}

	m_d3d9 = d3d9;
	m_d3d9_device = d3d9_device;
	m_hwnd_parent = hWnd;

	return S_OK;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// Close Direct3D9 Device.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
void	CBandiVideoDevice_DX9::Close()
{
	if(m_d3d9_device)
	{
		m_d3d9_device->Release();
		m_d3d9_device = NULL;
	}

	if(m_d3d9)
	{
		m_d3d9->Release( );
		m_d3d9 = NULL;
	}

	m_hwnd_parent = NULL;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// Resize the Direct3D9 viewport. 
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT	CBandiVideoDevice_DX9::Resize(INT width, INT height)
{
	if(m_d3d9_device == NULL)
		return E_FAIL;

	width = max(1, width);
	height = max(1, height);  

	// Create the viewport
	D3DVIEWPORT9 vp = { 0, 0, width, height, 0.0f, 1.0f };

	m_d3d9_device->SetViewport( &vp );

	return S_OK;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// Begin a Direct3D9 frame.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT	CBandiVideoDevice_DX9::StartFrame()
{
	if(m_d3d9_device == NULL)
		return E_FAIL;

	m_d3d9_device->Clear( 0, NULL, D3DCLEAR_TARGET, 0, 1.0f, 0 );
    m_d3d9_device->BeginScene();

	return S_OK;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// End a Direct3D9 frame.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT	CBandiVideoDevice_DX9::EndFrame()
{
	if(m_d3d9_device == NULL)
		return E_FAIL;

    m_d3d9_device->EndScene();
    m_d3d9_device->Present(NULL, NULL, NULL, NULL);

	return S_OK;
}




/// D3DVERTEX structure
typedef struct _D3DVERTEX {						// D3D Vertex
	D3DVECTOR	pos;
	float		rhw;
	float		tu, tv;
} D3DVERTEX;
#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_TEX1)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// CBandiVideoTexture_DX9 class
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
CBandiVideoTexture_DX9::CBandiVideoTexture_DX9(BV_DEVICE_DX9* device)
{
	memcpy(&m_device, device, sizeof(BV_DEVICE_DX9));

	m_texture = NULL;
	m_vertex_buffer = NULL;

	m_vid_width = m_vid_height = 0;
	m_tex_width = m_tex_height = 0;

	if(!GetTextureFormat(device->m_d3d9, m_fmt_d3d, m_fmt_bvl, m_pixel_size))
		ASSERT(0);
}


CBandiVideoTexture_DX9::~CBandiVideoTexture_DX9()
{
	Close();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// Open a Direct3D9 texture
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT	CBandiVideoTexture_DX9::Open(INT vid_width, INT vid_height)
{
	HRESULT	hr;
	LPDIRECT3DTEXTURE9 texture = NULL;
  	LPDIRECT3DDEVICE9 d3d9_device = m_device.m_d3d9_device; 
	BOOL pow2 = TRUE;

	D3DCAPS9 Caps;
	d3d9_device->GetDeviceCaps(&Caps);
	if(!!(Caps.TextureCaps & D3DPTEXTURECAPS_NONPOW2CONDITIONAL))
	{
		pow2 = FALSE;
	}

	int tex_width = CalcTexSize(vid_width, pow2);
	int tex_height = CalcTexSize(vid_height, pow2);
	
	// try to create a dynamic texture first
	hr = d3d9_device->CreateTexture(tex_width, tex_height, 1,D3DUSAGE_DYNAMIC, 
									m_fmt_d3d, D3DPOOL_DEFAULT, &texture, 0);
	if(FAILED(hr))
	{
		hr = d3d9_device->CreateTexture(tex_width, tex_height, 1, 0, 
									m_fmt_d3d, D3DPOOL_MANAGED, &texture, 0);
		if(FAILED(hr))
		{
			Beep(1000, 1000);
			ASSERT(0);
			return hr;
		}
	}

	D3DLOCKED_RECT locked_rect;

	// Clear the texture to black.
	if(SUCCEEDED(texture->LockRect(0, &locked_rect, NULL, NULL)))
	{
		// Clear the pixels.
		BYTE* dest = (BYTE*) locked_rect.pBits;
		int bytes = tex_width*m_pixel_size;

		for(int y = 0 ; y < tex_height ; y++)
		{
			memset(dest, 0, bytes);
			dest += locked_rect.Pitch;
		}

		// Unlock the DirectX texture.
		texture->UnlockRect(NULL);
	}

	m_texture = texture;

	m_vid_width = vid_width;
	m_vid_height = vid_height;
	m_tex_width = tex_width;
	m_tex_height = tex_height;

	return S_OK;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// Close a Direct3D9 texture
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
void	CBandiVideoTexture_DX9::Close()
{
	m_vid_width = m_vid_height = 0;
	m_tex_width = m_tex_height = 0;

	if(m_texture)
	{
		m_texture->Release();
		m_texture = NULL;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// Lock a Direct3D9 teture and return the buffer address and pitch
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
BYTE*	CBandiVideoTexture_DX9::Lock(INT &pitch)
{
	D3DLOCKED_RECT	rc;
	BYTE *buf;

	m_texture->LockRect(0, &rc, NULL, 0);
	buf = (BYTE*)rc.pBits;
	pitch = rc.Pitch;

	return buf;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// Unlock a Direct3D9 texture.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
void	CBandiVideoTexture_DX9::Unlock()
{
	m_texture->UnlockRect(NULL);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// Draw a Direct3D9 texture.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT	CBandiVideoTexture_DX9::Draw(INT x, INT y, INT width, INT height)
{
	HRESULT hr;
	hr = m_device.m_d3d9_device->SetTexture(0, m_texture);
	if(FAILED(hr)) return hr;

	static DWORD dwAddressU, dwAddressV;

	m_device.m_d3d9_device->GetSamplerState(0, D3DSAMP_ADDRESSU, &dwAddressU);
	m_device.m_d3d9_device->GetSamplerState(0, D3DSAMP_ADDRESSV, &dwAddressV);

	m_device.m_d3d9_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	m_device.m_d3d9_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	m_device.m_d3d9_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_device.m_d3d9_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	hr = SetVertices((float)x, (float)y, (float)width, (float)height);

	m_device.m_d3d9_device->SetSamplerState(0, D3DSAMP_ADDRESSU, dwAddressU);
	m_device.m_d3d9_device->SetSamplerState(0, D3DSAMP_ADDRESSV, dwAddressV);

	return hr;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// Set the vertices.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT CBandiVideoTexture_DX9::SetVertices(float scr_x, float scr_y, float scr_width, float scr_height)
{
	D3DVERTEX	vertices[4];

	// Set vertices
	vertices[0].pos.x = scr_x;
	vertices[0].pos.y = scr_y;
	vertices[0].tu    = 0.0f;
	vertices[0].tv    = 0.0f;

	vertices[1].pos.x = scr_x + scr_width;
	vertices[1].pos.y = scr_y;
	vertices[1].tu    = 1.0f * ((float)m_vid_width / m_tex_width);
	vertices[1].tv    = 0.0f;

	vertices[2].pos.x = scr_x;
	vertices[2].pos.y = scr_y + scr_height;
	vertices[2].tu    = 0.0f;
	vertices[2].tv    = 1.0f * ((float)m_vid_height / m_tex_height);

	vertices[3].pos.x = scr_x + scr_width;
	vertices[3].pos.y = scr_y + scr_height;
	vertices[3].tu    = 1.0f * ((float)m_vid_width / m_tex_width);
	vertices[3].tv    = 1.0f * ((float)m_vid_height / m_tex_height);


	vertices[0].pos.z = vertices[1].pos.z = vertices[2].pos.z = vertices[3].pos.z = 0.0f;
	vertices[0].rhw   = vertices[1].rhw   = vertices[2].rhw   = vertices[3].rhw   = 1.0f;

	// Draw the vertices.
	m_device.m_d3d9_device->SetVertexShader(0);
	m_device.m_d3d9_device->SetFVF(D3DFVF_VERTEX);
	
	return m_device.m_d3d9_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(vertices[0]));
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// Calculate texture size.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
int CBandiVideoTexture_DX9::CalcTexSize(int vid_size, BOOL pow2)
{
	// Power-of-2 texture dimensions are required.
	D3DCAPS9 caps;
	m_device.m_d3d9_device->GetDeviceCaps(&caps);
	if(pow2 && caps.TextureCaps & D3DPTEXTURECAPS_POW2)
	{
		int tex_size = 16;
		while (tex_size < vid_size)
			tex_size = tex_size<<1;

		return tex_size;
	}
	
	return vid_size;
}


