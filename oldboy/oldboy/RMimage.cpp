#include "stdafx.h"
#include "RMmacro.h"
#include "RMimage.h"
#include "RMresourceManager.h"
#include "RMrender.h"


CRMimage::CRMimage(void) :
	m_Width(0.0),
	m_Height(0.0),
	m_D2DImg(nullptr)
{
}

CRMimage::~CRMimage(void)
{
	SafeRelease(m_D2DImg);
}

HRESULT CRMimage::CreateImage( const std::wstring& path )
{
	IWICImagingFactory*	imageFactory = CRMresourceManager::GetInstance()->GetImageFactory();
	IWICBitmapDecoder* bitmapDecoder = nullptr;
	HRESULT hr = S_FALSE;

	// 디코더 생성
	hr = imageFactory->CreateDecoderFromFilename( path.c_str(), nullptr, GENERIC_READ, 
		WICDecodeMetadataCacheOnDemand, &bitmapDecoder );

	if ( FAILED(hr) )
	{
		return hr;
	}

	// 디코더에서 프레임 추출
	IWICBitmapFrameDecode* bitmapFrameDecode = nullptr;
	hr = bitmapDecoder->GetFrame( 0, &bitmapFrameDecode );

	if ( FAILED(hr) )
	{
		SafeRelease(bitmapDecoder);
		return hr;
	}

	IWICFormatConverter*	formatConverter = nullptr;

	// 프레임을 기반으로 컨버터 생성
	hr = imageFactory->CreateFormatConverter( &formatConverter );

	if ( FAILED(hr) )
	{
		SafeRelease(bitmapFrameDecode);
		SafeRelease(bitmapDecoder);
		return hr;
	}

	hr = formatConverter->Initialize( bitmapFrameDecode, 
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, nullptr, 0.0f,
		WICBitmapPaletteTypeCustom );

	if ( FAILED(hr) )
	{
		SafeRelease(bitmapFrameDecode);
		SafeRelease(bitmapDecoder);
	}

	hr = CRMrender::GetInstance()->GetRenderTarget()->CreateBitmapFromWicBitmap(formatConverter, nullptr, &m_D2DImg);

	if ( FAILED(hr) )
	{
		SafeRelease(bitmapFrameDecode);
		SafeRelease(bitmapDecoder);
	}

	m_Width = m_D2DImg->GetSize().width;
	m_Height = m_D2DImg->GetSize().height;

	SafeRelease( bitmapFrameDecode );
	SafeRelease( bitmapDecoder );

	return hr;
}
