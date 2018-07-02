#include <RenderBuffer.h>
#include <Texture.h>

#include "NativeConstants.h"

RenderBuffer::RenderBuffer(T_UINT16 width, T_UINT16 height, GraphicsConstants::TextureFormat format)
{
  LPDIRECT3DSURFACE9 surf;
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  HRESULT hr = device->CreateDepthStencilSurface(
    width,
    height,
    NativeConstants::TEXTURE_FORMATS[format],
    D3DMULTISAMPLE_NONE,
    0,
    TRUE,
    &surf,
    nullptr
  );
  NATIVE_ASSERT(SUCCEEDED(hr), "深度バッファの作成に失敗しました");
  this->native_obj_ = surf;
}

RenderBuffer::RenderBuffer(Texture* texture)
{
  LPDIRECT3DTEXTURE9 tex = (LPDIRECT3DTEXTURE9)texture->GetNativeObject();
  LPDIRECT3DSURFACE9 surf;
  HRESULT hr = tex->GetSurfaceLevel(0, &surf);
  NATIVE_ASSERT(SUCCEEDED(hr), "テクスチャのサーフェイスの取得に失敗しました");
  this->native_obj_ = surf;
}

RenderBuffer::~RenderBuffer()
{
  ((LPDIRECT3DSURFACE9)this->native_obj_)->Release();
}