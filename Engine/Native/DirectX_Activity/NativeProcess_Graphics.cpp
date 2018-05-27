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

void NativeProcess_Graphics::Blit(INativeTexture* source, INativeRenderTexture* dest)
{
  //dest->RenderBegin();
  //dest->RenderEnd();
}

void NativeProcess_Graphics::Blit(INativeTexture* source, INativeRenderTexture* dest, Material* mat, T_UINT8 pass)
{
  //dest->RenderBegin();
  //dest->RenderEnd();
}

void NativeProcess_Graphics::Blit(INativeTexture* source, Material* mat, T_UINT8 pass)
{
  //dest->RenderBegin();
  //dest->RenderEnd();
}

