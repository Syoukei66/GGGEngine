#include "../Core/NativeProcess.h"

#define NOMINMAX
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <d3d9.h>
#include <d3dx9.h>
#include "DirectXDirector.h"
#include "NativeConstants.h"

#include <fstream>
#include <iostream>

#include "NativeIndexBuffer.h"
#include "NativeVertexBuffer.h"
#include "NativeShader.h"
#include "NativeSound.h"

namespace NativeProcess
{

//=========================================================================================
// Time
//=========================================================================================
namespace Time
{

#ifdef _DEBUG

static T_FLOAT fps_;
static T_FLOAT frame_time_;
static LARGE_INTEGER time_start_;
static LARGE_INTEGER time_end_;
static LARGE_INTEGER time_freq_;

void FPS_Init()
{
  fps_ = Director::GetFrameRate();
  QueryPerformanceFrequency(&time_freq_);
  QueryPerformanceCounter(&time_start_);
}

void FPS_PreUpdate()
{
  QueryPerformanceCounter(&time_end_);
  frame_time_ = static_cast<float>(time_end_.QuadPart - time_start_.QuadPart) / static_cast<float>(time_freq_.QuadPart);
}

void FPS_PostUpdate()
{
  fps_ = (fps_ * 0.99f) + (0.01f / frame_time_);
  time_start_ = time_end_;
}

T_FLOAT FPS_GetValue()
{
  return fps_;
}
#endif

} // namespace Time

//=========================================================================================
// IO
//=========================================================================================
namespace IO
{

const std::string TextFile_Read(const char* path)
{
  std::ifstream ifs(path);
  if (ifs.fail())
  {
    return nullptr;
  }
  return std::string(
    std::istreambuf_iterator<char>(ifs),
    std::istreambuf_iterator<char>()
  );
}

void TextFile_Write(const char* path, const std::string& str)
{
  std::ofstream ofs(path);
  if (ofs.fail())
  {
    return;
  }
  ofs.write(str.c_str(), str.length());
}

} // namespace IO

//=========================================================================================
// Graphics
//=========================================================================================
namespace Graphics
{

void ViewportClear()
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetDevice();
  device->Clear(
    0, NULL,
    (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
    D3DCOLOR_RGBA(0, 0, 0, 0),
    1.0f, 0
  );
}

void SetViewport(T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h, T_FLOAT minZ, T_FLOAT maxZ)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetDevice();
  D3DVIEWPORT9 viewport;
  viewport.X = (DWORD)x;
  viewport.Y = (DWORD)y;
  viewport.Width = (DWORD)w;
  viewport.Height = (DWORD)h;
  viewport.MinZ = minZ;
  viewport.MaxZ = maxZ;
  device->SetViewport(&viewport);
}

void PackColor4u8(T_PACKED_COLOR_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
{
  (*color) = (T_PACKED_COLOR_UINT32)D3DCOLOR_RGBA(r, g, b, a);
}

static LPDIRECT3DSURFACE9 temp_color_buffer = nullptr;
static LPDIRECT3DSURFACE9 temp_depth_buffer = nullptr;

static SharedRef<rcRenderBuffer> use_color_buffer = nullptr;
static SharedRef<rcRenderBuffer> use_depth_stencil_buffer = nullptr;

void SetRenderTarget(const SharedRef<rcRenderBuffer>& color_buffer, const SharedRef<rcRenderBuffer>& depth_stencil_buffer, bool clear)
{
  use_color_buffer = color_buffer;
  use_depth_stencil_buffer = depth_stencil_buffer;

  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetDevice();
  device->EndScene();

  //現在の各バッファを保持しておく
  NATIVE_ASSERT(!temp_color_buffer && !temp_depth_buffer, "RenderBegin()を二重に呼び出しました。");
  device->GetRenderTarget(0, &temp_color_buffer);
  device->GetDepthStencilSurface(&temp_depth_buffer);

  HRESULT hr = device->SetRenderTarget(0, (LPDIRECT3DSURFACE9)use_color_buffer->GetNativeObject());
  NATIVE_ASSERT(SUCCEEDED(hr), "レンダ―ターゲットの設定に失敗しました");

  hr = device->SetDepthStencilSurface((LPDIRECT3DSURFACE9)use_depth_stencil_buffer->GetNativeObject());
  NATIVE_ASSERT(SUCCEEDED(hr), "深度バッファの設定に失敗しました");

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

void ResetRenderTarget()
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetDevice();

  device->EndScene();

  HRESULT hr = device->SetRenderTarget(0, temp_color_buffer);
  NATIVE_ASSERT(SUCCEEDED(hr), "レンダ―ターゲットの設定に失敗しました");
  hr = device->SetDepthStencilSurface(temp_depth_buffer);
  NATIVE_ASSERT(SUCCEEDED(hr), "深度バッファの設定に失敗しました");

  temp_color_buffer = nullptr;
  temp_depth_buffer = nullptr;

  use_color_buffer = nullptr;
  use_depth_stencil_buffer = nullptr;

  device->BeginScene();
}

} // namespace Graphics

//=========================================================================================
// Resource
//=========================================================================================
namespace Resource
{

UniqueResource<rcTexture> TextureLoad(const char* path)
{
  LP_DEVICE device = Director::GetDevice();

  D3DXIMAGE_INFO info;
  HRESULT hr = D3DXGetImageInfoFromFile(
    path,
    &info
  );
  NATIVE_ASSERT(SUCCEEDED(hr), "テクスチャサイズの取得に失敗しました");

  LPDIRECT3DTEXTURE9 tex = nullptr;
  hr = D3DXCreateTextureFromFileEx(
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
    &tex);

  NATIVE_ASSERT(SUCCEEDED(hr), "テクスチャのロードに失敗しました");

  return rcTexture::Create((T_UINT16)info.Width, (T_UINT16)info.Height, tex);
}

void DeleteTexture(rcTexture* texture)
{
  ((LPDIRECT3DTEXTURE9)texture->GetNativeObject())->Release();
}

void GetTextureSize(const rcTexture* texture, T_UINT16* width_dest, T_UINT16* height_dest)
{
  LPDIRECT3DTEXTURE9 tex = (LPDIRECT3DTEXTURE9)texture->GetNativeObject();

  D3DSURFACE_DESC desc;
  HRESULT hr = tex->GetLevelDesc(0, &desc);
  NATIVE_ASSERT(SUCCEEDED(hr), "テクスチャの情報の取得に失敗しました");
  (*width_dest) = desc.Width;
  (*height_dest) = desc.Height;
}

UniqueResource<rcRenderBuffer> CreateColorBuffer(const SharedRef<const rcTexture>& texture)
{
  LPDIRECT3DTEXTURE9 tex = (LPDIRECT3DTEXTURE9)texture->GetNativeObject();
  LPDIRECT3DSURFACE9 surf;
  HRESULT hr = tex->GetSurfaceLevel(0, &surf);
  NATIVE_ASSERT(SUCCEEDED(hr), "テクスチャのサーフェイスの取得に失敗しました");
  return rcRenderBuffer::Create(surf);
}

UniqueResource<rcRenderBuffer> CreateDepthStencilBuffer(T_UINT16 width, T_UINT16 height, rcRenderBuffer::Format format)
{
  LPDIRECT3DSURFACE9 surf;
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetDevice();
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
  return rcRenderBuffer::Create(surf);
}

void DeleteRenderBuffer(rcRenderBuffer* render_buffer)
{
  ((LPDIRECT3DSURFACE9)render_buffer->GetNativeObject())->Release();
}

UniqueResource<rcRenderTexture> CreateRenderTexture(T_UINT16 width, T_UINT16 height, rcRenderBuffer::Format format, rcRenderBuffer::Format depth_format)
{
  using namespace NativeConstants;
  width = Mathf::CalcTwoPowerValue(width);
  height = Mathf::CalcTwoPowerValue(height);
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetDevice();

  //
  LPDIRECT3DTEXTURE9 tex = nullptr;

  HRESULT hr = D3DXCreateTexture(
    (LPDIRECT3DDEVICE9)device,
    width,
    height,
    0,
    D3DUSAGE_RENDERTARGET,
    TEXTURE_FORMATS[format],
    D3DPOOL_DEFAULT,
    &tex);

  NATIVE_ASSERT(SUCCEEDED(hr), "テクスチャの作成に失敗しました");

  return rcRenderTexture::Create(width, height, tex, depth_format);
}

UniqueResource<rcShader> ShaderLoad(const char* path)
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetDevice();
  LPD3DXEFFECT dest = nullptr;

  HRESULT hr = D3DXCreateEffectFromFile(
    device,
    path,
    NULL,
    NULL,
    D3DXSHADER_SKIPVALIDATION,
    NULL,
    &dest,
    NULL
  );
  NATIVE_ASSERT(SUCCEEDED(hr), "シェーダーのロードに失敗しました");
  return UniqueResource<rcShader>(new NativeShader(dest));
}

UniqueResource<rcSound> SoundLoad(const char* path)
{
  return UniqueResource<rcSound>(new NativeSound(path));
}

UniqueResource<rcVertexBuffer> CreateVertexBuffer(T_UINT16 vertex_count, T_UINT16 polygon_count, T_UINT32 format)
{
  return UniqueResource<rcVertexBuffer>(new NativeVertexBuffer(vertex_count, polygon_count, format));
}

UniqueResource<rcIndexBuffer> CreateIndexBuffer(T_UINT32 indexes_count)
{
  return UniqueResource<rcIndexBuffer>(new NativeIndexBuffer(indexes_count));
}
}

} // namespace NativeProcess
