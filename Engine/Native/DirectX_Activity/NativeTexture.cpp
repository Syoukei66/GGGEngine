#include "NativeTexture.h"

#include <Director.h>

static NativeTextureInstance* TextureLoad(const char* path)
{
  LP_DEVICE device = Director::GetInstance()->GetDevice();
  LPDIRECT3DTEXTURE9 dest = nullptr;

  HRESULT hr = D3DXCreateTextureFromFileEx(
    (LPDIRECT3DDEVICE9)device,
    path,
    D3DX_DEFAULT,
    D3DX_DEFAULT,
    D3DX_DEFAULT,
    0,
    D3DFMT_UNKNOWN,
    D3DPOOL_MANAGED,
    D3DX_FILTER_NONE,
    D3DX_DEFAULT,
    0,
    NULL,
    NULL,
    &dest);

  NATIVE_ASSERT(SUCCEEDED(hr), "テクスチャのロードに失敗しました");
  
  return (NativeTextureInstance*)dest;
}

// =================================================================
// Constructor / Destructor
// =================================================================
NativeTexture::NativeTexture(const char* path)
  : INativeTexture(TextureLoad(path))
{
  LPDIRECT3DTEXTURE9 tex = this->GetNativeInstance<IDirect3DTexture9>();
  tex->GetLevelDesc(0, &this->desc_);
  
  HRESULT hr = D3DXGetImageInfoFromFile(
    path,
    &this->info_
  );

  NATIVE_ASSERT(SUCCEEDED(hr), "テクスチャの情報の取得に失敗しました");
}

NativeTexture::~NativeTexture()
{
  this->GetNativeInstance<IDirect3DTexture9>()->Release();
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
T_UINT16 NativeTexture::GetWidth() const
{
  return (T_UINT16)this->info_.Width;
}

T_UINT16 NativeTexture::GetHeight() const
{
  return (T_UINT16)this->info_.Height;
}

T_UINT16 NativeTexture::GetTwoPoweredWidth() const
{
  return (T_UINT16)this->desc_.Width;
}

T_UINT16 NativeTexture::GetTwoPoweredHeight() const
{
  return (T_UINT16)this->desc_.Height;
}

