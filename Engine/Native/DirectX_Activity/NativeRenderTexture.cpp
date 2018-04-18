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

static NativeTextureInstance* CreateTexture(T_UINT16 width, T_UINT16 height)
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
    D3DFMT_A8R8G8B8,
    D3DPOOL_DEFAULT,
    &texture);

  if (FAILED(hr))
  {
    NATIVE_ASSERT(false, "�e�N�X�`���̍쐬�Ɏ��s���܂���");
  }

  return (NativeTextureInstance*)texture;
}

// =================================================================
// Constructor / Destructor
// =================================================================
NativeRenderTexture::NativeRenderTexture(T_UINT16 width, T_UINT16 height)
  : INativeRenderTexture(CreateTexture(width, height))
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
    NATIVE_ASSERT(false, "�e�N�X�`���̃T�[�t�F�C�X�̎擾�Ɏ��s���܂���");
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
    NATIVE_ASSERT(false, "�[�x�o�b�t�@�̍쐬�Ɏ��s���܂���");
  }
}

NativeRenderTexture::~NativeRenderTexture()
{
  NATIVE_ASSERT(!this->surface_temp_ && !this->depth_surface_temp_, "RenderTexture�ւ̕`�撆��RenderTexture��������悤�Ƃ��܂����B");
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

  //���݂̊e�o�b�t�@��ێ����Ă���
  NATIVE_ASSERT(!this->surface_temp_ && !this->depth_surface_temp_, "RenderBegin()���d�ɌĂяo���܂����B");
  device->GetRenderTarget(0, &this->surface_temp_);
  device->GetDepthStencilSurface(&this->depth_surface_temp_);
  
  HRESULT hr = device->SetRenderTarget(0, this->texture_surface_);
  if (FAILED(hr))
  {
    NATIVE_ASSERT(false, "�����_�\�^�[�Q�b�g�̐ݒ�Ɏ��s���܂���");
  }
  hr = device->SetDepthStencilSurface(this->depth_surface_);
  if (FAILED(hr))
  {
    NATIVE_ASSERT(false, "�[�x�o�b�t�@�̐ݒ�Ɏ��s���܂���");
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
    NATIVE_ASSERT(false, "�����_�\�^�[�Q�b�g�̐ݒ�Ɏ��s���܂���");
  }
  hr = device->SetDepthStencilSurface(this->depth_surface_temp_);
  if (FAILED(hr))
  {
    NATIVE_ASSERT(false, "�[�x�o�b�t�@�̐ݒ�Ɏ��s���܂���");
  }

  this->surface_temp_ = nullptr;
  this->depth_surface_temp_ = nullptr;

  device->BeginScene();
}
