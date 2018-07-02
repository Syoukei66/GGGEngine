#include <NativeProcess.h>

#define NOMINMAX
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <Director.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <ITextureRegion.h>
#include <Director.h>
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
  fps_ = Director::GetInstance()->GetFrameRate();
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
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  device->Clear(
    0, NULL,
    (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
    D3DCOLOR_RGBA(0, 0, 0, 0),
    1.0f, 0
  );
}

void SetViewport(T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h, T_FLOAT minZ, T_FLOAT maxZ)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
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

void SetRenderTarget(RenderBuffer* color_buffer, RenderBuffer* depth_buffer, bool clear)
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  device->EndScene();

  //現在の各バッファを保持しておく
  NATIVE_ASSERT(!temp_color_buffer && !temp_depth_buffer, "RenderBegin()を二重に呼び出しました。");
  device->GetRenderTarget(0, &temp_color_buffer);
  device->GetDepthStencilSurface(&temp_depth_buffer);

  HRESULT hr = device->SetRenderTarget(0, (LPDIRECT3DSURFACE9)color_buffer->GetNativeObject());
  NATIVE_ASSERT(SUCCEEDED(hr), "レンダ―ターゲットの設定に失敗しました");

  hr = device->SetDepthStencilSurface((LPDIRECT3DSURFACE9)depth_buffer->GetNativeObject());
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
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();

  device->EndScene();

  HRESULT hr = device->SetRenderTarget(0, temp_color_buffer);
  NATIVE_ASSERT(SUCCEEDED(hr), "レンダ―ターゲットの設定に失敗しました");
  hr = device->SetDepthStencilSurface(temp_depth_buffer);
  NATIVE_ASSERT(SUCCEEDED(hr), "深度バッファの設定に失敗しました");

  temp_color_buffer = nullptr;
  temp_depth_buffer = nullptr;

  device->BeginScene();
}

} // namespace Graphics

//=========================================================================================
// Resource
//=========================================================================================
namespace Resource
{

void* TextureLoad(const std::string& path)
{
  LP_DEVICE device = Director::GetInstance()->GetDevice();
  LPDIRECT3DTEXTURE9 dest = nullptr;

  HRESULT hr = D3DXCreateTextureFromFileEx(
    (LPDIRECT3DDEVICE9)device,
    path.c_str(),
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

  return dest;
}

void* CreateTexture(T_UINT16 width, T_UINT16 height, GraphicsConstants::TextureFormat format)
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

void DeleteTexture(void* native_obj)
{
  ((LPDIRECT3DTEXTURE9)native_obj)->Release();
}

void GetTextureSize(const std::string& path, T_UINT16* width_dest, T_UINT16* height_dest)
{
  D3DXIMAGE_INFO info;
  HRESULT hr = D3DXGetImageInfoFromFile(
    path.c_str(),
    &info
  );
  NATIVE_ASSERT(SUCCEEDED(hr), "テクスチャサイズの取得に失敗しました");
  (*width_dest) = info.Width;
  (*height_dest) = info.Height;
}

void GetTextureSize(void* native_obj, T_UINT16* width_dest, T_UINT16* height_dest)
{
  LPDIRECT3DTEXTURE9 tex = (LPDIRECT3DTEXTURE9)native_obj;

  D3DSURFACE_DESC desc;
  HRESULT hr = tex->GetLevelDesc(0, &desc);
  NATIVE_ASSERT(SUCCEEDED(hr), "テクスチャの情報の取得に失敗しました");
  (*width_dest) = desc.Width;
  (*height_dest) = desc.Height;
}

}

//=========================================================================================
// Factory
//=========================================================================================
namespace Factory
{

INativeVertexBuffer* CreateVertexBuffer(T_UINT16 vertex_count, T_UINT16 polygon_count, T_UINT32 format)
{
  return new NativeVertexBuffer(vertex_count, polygon_count, format);
}
INativeIndexBuffer* CreateIndexBuffer(T_UINT32 indexes_count)
{
  return new NativeIndexBuffer(indexes_count);
}
INativeSound* CreateSound(const char* path)
{
  return new NativeSound(path);
}
INativeShader* CreateShader(const char* path)
{
  return new NativeShader(path);
}

} // namespace Factory

} // namespace NativeProcess
