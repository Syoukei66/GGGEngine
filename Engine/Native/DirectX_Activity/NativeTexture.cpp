#include "NativeTexture.h"

#include <Director.h>

static NativeTextureInstance* TextureLoad(const char* path)
{
  LP_DEVICE device = Director::GetInstance()->GetDevice();
  LPDIRECT3DTEXTURE9 dest = nullptr;
  HRESULT hr = D3DXCreateTextureFromFile(
    (LPDIRECT3DDEVICE9)device,
    path,
    &dest);

  if (FAILED(hr))
  {
    MessageBox(NULL, "テクスチャのロードに失敗しました", "お知らせ", MB_OK);
  }
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
  return (T_UINT16)this->desc_.Width;
}

T_UINT16 NativeTexture::GetHeight() const
{
  return (T_UINT16)this->desc_.Height;
}

