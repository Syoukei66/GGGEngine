#include "NativeRenderTexture.h"

#include <Director.h>

static T_UINT16 CalcTwoPowerValue(T_UINT16 val)
{
  T_UINT16 t = 1;
  while (t < val)
  {
    t <<= 1;
  }
  return t;
}

static D3DFORMAT TEXTURE_FORMATS[INativeRenderTexture::TEXTURE_FORMAT_DATANUM] =
{
  D3DFMT_A8B8G8R8,
  D3DFMT_A16B16G16R16,
  D3DFMT_A16B16G16R16F,
};

static NativeTextureInstance* CreateTexture(T_UINT16 width, T_UINT16 height, INativeRenderTexture::Format format)
{
  width = CalcTwoPowerValue(width);
  height = CalcTwoPowerValue(height);
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

  if (FAILED(hr))
  {
    NATIVE_ASSERT(false, "テクスチャの作成に失敗しました");
  }

  return (NativeTextureInstance*)texture;
}

// =================================================================
// Constructor / Destructor
// =================================================================
NativeRenderTexture::NativeRenderTexture(T_UINT16 width, T_UINT16 height, INativeRenderTexture::Format format)
  : INativeRenderTexture(CreateTexture(width, height, format))
  , surface_temp_(nullptr)
  , depth_surface_temp_(nullptr)
{
  LPDIRECT3DTEXTURE9 texture = this->GetNativeInstance<IDirect3DTexture9>();
  texture->GetLevelDesc(0, &this->desc_);

  width = (T_UINT16)this->desc_.Width;
  height = (T_UINT16)this->desc_.Height;

  HRESULT hr = texture->GetSurfaceLevel(0, &this->texture_surface_);
  if (FAILED(hr))
  {
    NATIVE_ASSERT(false, "テクスチャのサーフェイスの取得に失敗しました");
  }

  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  hr = device->CreateDepthStencilSurface(
    width,
    height,
    D3DFMT_D16,
    D3DMULTISAMPLE_NONE,
    0,
    TRUE,
    &this->depth_surface_,
    nullptr
  );
  if (FAILED(hr))
  {
    NATIVE_ASSERT(false, "深度バッファの作成に失敗しました");
  }
}

NativeRenderTexture::~NativeRenderTexture()
{
  NATIVE_ASSERT(!this->surface_temp_ && !this->depth_surface_temp_, "RenderTextureへの描画中にRenderTextureを解放しようとしました。");
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  this->GetNativeInstance<IDirect3DTexture9>()->Release();
  this->texture_surface_->Release();
  this->depth_surface_->Release();
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
T_UINT16 NativeRenderTexture::GetWidth() const
{
  return (T_UINT16)this->desc_.Width;
}

T_UINT16 NativeRenderTexture::GetHeight() const
{
  return (T_UINT16)this->desc_.Height;
}

void NativeRenderTexture::RenderBegin(bool clear)
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();

  device->EndScene();

  //現在の各バッファを保持しておく
  NATIVE_ASSERT(!this->surface_temp_ && !this->depth_surface_temp_, "RenderBegin()を二重に呼び出しました。");
  device->GetRenderTarget(0, &this->surface_temp_);
  device->GetDepthStencilSurface(&this->depth_surface_temp_);
  
  HRESULT hr = device->SetRenderTarget(0, this->texture_surface_);
  if (FAILED(hr))
  {
    NATIVE_ASSERT(false, "レンダ―ターゲットの設定に失敗しました");
  }
  hr = device->SetDepthStencilSurface(this->depth_surface_);
  if (FAILED(hr))
  {
    NATIVE_ASSERT(false, "深度バッファの設定に失敗しました");
  }

  device->BeginScene();

  if (clear)
  {
    device->Clear(0,
      NULL,
      D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
      D3DCOLOR_ARGB(0, 255, 0, 0),
      1.0f,
      0);
  }
}

void NativeRenderTexture::RenderEnd()
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();

  device->EndScene();

  HRESULT hr = device->SetRenderTarget(0, this->surface_temp_);
  if (FAILED(hr))
  {
    NATIVE_ASSERT(false, "レンダ―ターゲットの設定に失敗しました");
  }
  hr = device->SetDepthStencilSurface(this->depth_surface_temp_);
  if (FAILED(hr))
  {
    NATIVE_ASSERT(false, "深度バッファの設定に失敗しました");
  }

  this->surface_temp_ = nullptr;
  this->depth_surface_temp_ = nullptr;

  device->BeginScene();
}
