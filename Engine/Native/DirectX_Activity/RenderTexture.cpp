#include "..\..\RenderTexture.h"
#include <RenderTexture.h>
#include "NativeConstants.h"
#include "NativeProcess.h"

RenderTexture* RenderTexture::Create(T_UINT16 width, T_UINT16 height, GraphicsConstants::TextureFormat format)
{
  return new RenderTexture(width, height, format);
}

static LPDIRECT3DTEXTURE9 CreateTexture(T_UINT16 width, T_UINT16 height, GraphicsConstants::TextureFormat format)
{
  using namespace NativeConstants;
  width = Util::CalcTwoPowerValue(width);
  height = Util::CalcTwoPowerValue(height);
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();

  //
  LPDIRECT3DTEXTURE9 texture = nullptr;

  HRESULT hr = D3DXCreateTexture(
    (LPDIRECT3DDEVICE9)device,
    width,
    height,
    0,
    D3DUSAGE_RENDERTARGET,
    TEXTURE_FORMATS[format],
    D3DPOOL_DEFAULT,
    &texture);

  NATIVE_ASSERT(SUCCEEDED(hr), "テクスチャの作成に失敗しました");

  return texture;
}

RenderTexture::RenderTexture(T_UINT16 width, T_UINT16 height, GraphicsConstants::TextureFormat format)
  : Texture(width, height, CreateTexture(width, height, format))
{
  this->depth_buffer_ = new RenderBuffer(this->GetTwoPoweredWidth(), this->GetTwoPoweredHeight(), GraphicsConstants::TEX_FORMAT_D16);
}

RenderTexture::~RenderTexture()
{
  delete this->depth_buffer_;
}

void RenderTexture::RenderBegin(bool clear)
{
  NativeProcess::Graphics::SetRenderTarget(this->GetColorBuffer(), this->depth_buffer_, clear);
}

void RenderTexture::RenderEnd()
{
  NativeProcess::Graphics::ResetRenderTarget();
}
