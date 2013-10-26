#include "stdafx.h"
#include "RMimage.h"
#include "RMresourceManager.h"
#include "RMrender.h"


CRMimage::CRMimage(void) :
	m_width(0.0),
	m_height(0.0),
	m_2DImg(nullptr)
{
}

CRMimage::~CRMimage(void)
{
	SafeRelease(m_2DImg);
	// 해당 부분 누락으로 인해서 메모리 누수가 발생하였음
}

HRESULT CRMimage::Init( std::wstring path )
{
	IWICImagingFactory*	imageFactory = CRMresourceManager::GetInstance()->GetImageFactory();
	IWICBitmapDecoder* bitmapDecoder = nullptr;
	HRESULT hr = S_FALSE;

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
