#include "stdafx.h"
#include "RMimage.h"
#include "RMresourceManager.h"
#include "RMrender.h"


CRMimage::CRMimage(void)
{
}

CRMimage::~CRMimage(void)
{
}

HRESULT CRMimage::Init( std::wstring path )
{
	IWICImagingFactory*	imageFactory = CRMresourceManager::GetInstance()->GetImageFactory();
	IWICBitmapDecoder* bitmapDecoder = nullptr;
	HRESULT hr = S_OK;

	// 디코더 생성
	hr = imageFactory->CreateDecoderFromFilename( path.c_str(), nullptr, GENERIC_READ, 
		WICDecodeMetadataCacheOnDemand, &bitmapDecoder );

	if(FAILED(hr))
		return hr;

	// 디코더에서 프레임 추출
	IWICBitmapFrameDecode* bitmapFrameDecode = nullptr;
	hr = bitmapDecoder->GetFrame( 0, &bitmapFrameDecode );

	if(FAILED(hr))
	{
		SafeRelease(bitmapDecoder);
		return hr;
	}

	IWICFormatConverter*	formatConverter = nullptr;

	// 프레임을 기반으로 컨버터 생성
	hr = imageFactory->CreateFormatConverter( &formatConverter );

	if(FAILED(hr))
	{
		SafeRelease(bitmapFrameDecode);
		SafeRelease(bitmapDecoder);
		return hr;
	}

	hr = formatConverter->Initialize( bitmapFrameDecode, 
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, nullptr, 0.0f,
		WICBitmapPaletteTypeCustom );

	if(FAILED(hr))
	{
		SafeRelease(bitmapFrameDecode);
		SafeRelease(bitmapDecoder);
	}

	hr = CRMrender::GetInstance()->GetRenderTarget()->CreateBitmapFromWicBitmap(formatConverter, nullptr, &m_2DImg);

	if(FAILED(hr))
	{
		SafeRelease(bitmapFrameDecode);
		SafeRelease(bitmapDecoder);
	}

	m_width = m_2DImg->GetSize().width;
	m_height = m_2DImg->GetSize().height;

	SafeRelease( bitmapFrameDecode );
	SafeRelease( bitmapDecoder );

	return hr;
}
