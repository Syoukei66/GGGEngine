#include "NativeProcess_Graphics.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <ITextureRegion.h>
#include <Director.h>
#include "DirectXDirector.h"
#include "NativeConstants.h"

void NativeProcess_Graphics::Graphics_Cheat(T_UINT16 cheat_id)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
}

void NativeProcess_Graphics::Graphics_Clear()
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  device->Clear(
    0, NULL,
    (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
    D3DCOLOR_RGBA(0, 0, 0, 0),
    1.0f, 0
  );
}

void NativeProcess_Graphics::Graphics_SetViewport(T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h, T_FLOAT minZ, T_FLOAT maxZ)
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

void NativeProcess_Graphics::Graphics_PackColor4u8(T_PACKED_COLOR_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
{
  (*color) = (T_PACKED_COLOR_UINT32)D3DCOLOR_RGBA(r, g, b, a);
}

static LPDIRECT3DSURFACE9 temp_color_buffer = nullptr;
static LPDIRECT3DSURFACE9 temp_depth_buffer = nullptr;

void NativeProcess_Graphics::SetRenderTarget(RenderBuffer* color_buffer, RenderBuffer* depth_buffer, bool clear)
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

void NativeProcess_Graphics::ResetRenderTarget()
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
