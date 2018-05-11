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

void NativeProcess_Graphics::Graphics_DrawPrimitive(GameObjectRenderState* state, PrimitiveType type, const Vertex::VC* vertexes, T_UINT16 vertexes_count)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)state->GetRenderObject();

  device->SetFVF(D3DFVF_XYZW | D3DFVF_DIFFUSE);
  HRESULT hr = device->DrawPrimitiveUP(
    NativeConstants::PRIMITIVE_TYPES[type],
    INativeProcess_Graphics::PRIMITIVE_SURF_NUM(type, vertexes_count),
    vertexes,
    sizeof(Vertex::VC)
  );
}

void NativeProcess_Graphics::Graphics_DrawIndexedPrimitive(GameObjectRenderState * state, PrimitiveType type, const Vertex::VC * vertexes, T_UINT16 vertexes_count, const T_UINT16 * indexes)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)state->GetRenderObject();

  device->SetFVF(D3DFVF_XYZW | D3DFVF_DIFFUSE);
  HRESULT hr = device->DrawIndexedPrimitiveUP(
    NativeConstants::PRIMITIVE_TYPES[type],
    0,
    vertexes_count,
    INativeProcess_Graphics::PRIMITIVE_SURF_NUM(type, vertexes_count),
    indexes,
    D3DFMT_INDEX16,
    vertexes,
    sizeof(Vertex::VC)
  );
}

void NativeProcess_Graphics::Graphics_DrawSprite(GameObjectRenderState* state, PrimitiveType type, const Vertex::VCT* vertexes, T_UINT16 vertexes_count)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)state->GetRenderObject();

  device->SetFVF(D3DFVF_XYZW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
  HRESULT hr = device->DrawPrimitiveUP(
    NativeConstants::PRIMITIVE_TYPES[type],
    INativeProcess_Graphics::PRIMITIVE_SURF_NUM(type, vertexes_count),
    vertexes,
    sizeof(Vertex::VCT)
  );
}

void NativeProcess_Graphics::Graphics_DrawIndexedSprite(GameObjectRenderState* state, PrimitiveType type, const Vertex::VCT* vertexes, T_UINT16 vertexes_count, const T_UINT16* indexes)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)state->GetRenderObject();

  //TODO:Ø‚è‘Ö‚¦‚ê‚é‚æ‚¤‚É
  //device->SetRenderState(D3DRS_LIGHTING, true);
  device->SetFVF(D3DFVF_XYZW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
  HRESULT hr = device->DrawIndexedPrimitiveUP(
    NativeConstants::PRIMITIVE_TYPES[type],
    0,
    vertexes_count,
    INativeProcess_Graphics::PRIMITIVE_SURF_NUM(type, vertexes_count),
    indexes,
    D3DFMT_INDEX16,
    vertexes,
    sizeof(Vertex::VCT)
  );
}

void NativeProcess_Graphics::Graphics_DrawVertexes(GameObjectRenderState* state, PrimitiveType primitive_type, Vertex::VertexType vertex_type, const void* vertexes, T_UINT16 vertexes_count)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)state->GetRenderObject();
  device->SetFVF(NativeConstants::FVF_TYPES[vertex_type]);
  HRESULT hr = device->DrawPrimitiveUP(
    NativeConstants::PRIMITIVE_TYPES[primitive_type],
    INativeProcess_Graphics::PRIMITIVE_SURF_NUM(primitive_type, vertexes_count),
    vertexes,
    Vertex::VERTEX_SIZE[vertex_type]
  );
}

void NativeProcess_Graphics::Graphics_DrawIndexedVertexes(GameObjectRenderState* state, PrimitiveType primitive_type, Vertex::VertexType vertex_type, const void* vertexes, T_UINT16 vertexes_count, const T_UINT16* indexes)
{
  static const D3DFORMAT format = sizeof(T_UINT16) == 2 ? D3DFMT_INDEX16 : D3DFMT_INDEX32;
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)state->GetRenderObject();
  device->SetFVF(NativeConstants::FVF_TYPES[vertex_type]);
  HRESULT hr = device->DrawIndexedPrimitiveUP(
    NativeConstants::PRIMITIVE_TYPES[primitive_type],
    0,
    vertexes_count,
    INativeProcess_Graphics::PRIMITIVE_SURF_NUM(primitive_type, vertexes_count),
    indexes,
    format,
    vertexes,    
    Vertex::VERTEX_SIZE[vertex_type]
  );
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

