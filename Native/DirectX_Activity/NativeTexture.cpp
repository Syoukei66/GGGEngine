#include "NativeTexture.h"

#include "../../Engine/Director.h"

#define texture_ GetNativeInstance<IDirect3DTexture9>()

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
  LPDIRECT3DTEXTURE9 tex = (LPDIRECT3DTEXTURE9)this->texture_;
  tex->GetLevelDesc(0, &this->desc_);
}

NativeTexture::~NativeTexture()
{
  this->texture_->Release();
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
T_FLOAT NativeTexture::GetWidth() const
{
  return this->desc_.Width;
}

T_FLOAT NativeTexture::GetHeight() const
{
  return this->desc_.Height;
}

