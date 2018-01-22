#include "NativeProcess_Graphics.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <Texture.h>
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

  //TODO:�؂�ւ����悤��
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

static std::map<T_UINT16, LP_LIGHT> light_map;


T_UINT16 NativeProcess_Graphics::Graphics_CreateLight(LP_LIGHT* light)
{
  //=================��ŏ���======================
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  D3DMATERIAL9 mat;
  ZeroMemory(&mat, sizeof(mat));
  mat.Diffuse.r = 1.0f;
  mat.Diffuse.g = 1.0f;
  mat.Diffuse.b = 1.0f;
  mat.Diffuse.a = 1.0f;
  device->SetMaterial(&mat);
  //==============================================

  T_UINT16 id = 0;
  while (id < T_UINT16_MAX)
  {
    if (light_map.find(id) == light_map.end())
    {
      break;
    }
    id++;
  }
  D3DLIGHT9* d3d_light = new D3DLIGHT9();
  d3d_light->Type = D3DLIGHT_DIRECTIONAL;
  (*light) = (LP_LIGHT)d3d_light;
  light_map[id] = (*light);
  return id;
}

void NativeProcess_Graphics::Graphics_DeleteLight(T_UINT16 light_id, LP_LIGHT light)
{
  if (light_map.find(light_id) == light_map.end())
  {
    return;
  }
  //TODO:���ׂĎ���
}

void NativeProcess_Graphics::Graphics_SetLight(T_UINT16 light_id, LP_LIGHT light)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  device->SetLight(light_id, (D3DLIGHT9*)(light));
}

void NativeProcess_Graphics::Graphics_SetLightEnable(T_UINT16 light_id, LP_LIGHT light, bool enable)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  device->LightEnable(light_id, enable);
}

void NativeProcess_Graphics::Graphics_SetLightDirection(T_UINT16 light_id, LP_LIGHT light, const TVec3f& direction)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  D3DLIGHT9* d3d_light = (D3DLIGHT9*)light;
  TVec3f normalized = direction.Normalized();
  d3d_light->Direction.x = normalized.x;
  d3d_light->Direction.y = normalized.y;
  d3d_light->Direction.z = normalized.z;
}

void NativeProcess_Graphics::Graphics_SetLightDiffuse(T_UINT16 light_id, LP_LIGHT light, const Color4F& color)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  D3DLIGHT9* d3d_light = (D3DLIGHT9*)light;
  d3d_light->Diffuse.r = color.GetRed();
  d3d_light->Diffuse.g = color.GetGreen();
  d3d_light->Diffuse.b = color.GetBlue();
  d3d_light->Diffuse.a = color.GetAlpha();
}

void NativeProcess_Graphics::Graphics_SetAmbient(const Color4F& color)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  device->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(
    color.GetRed(),
    color.GetGreen(),
    color.GetBlue(),
    color.GetAlpha()
  ));
}

//void NativeProcess_Graphics::Graphics_DrawPoint(GameObjectRenderState* state) const
//{
  //LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)state->renderObject;
  //VERTEX_2D vtx = {
  //	D3DXVECTOR4(
  //		state->position.x,
  //		state->position.y,
  //		1.0f,
  //		1.0f
  //	),
  //	D3DCOLOR_RGBA((int)state->color.r, (int)state->color.g, (int)state->color.b, (int)state->color.a)
  //};
  //device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
  //device->SetRenderState(D3DRS_POINTSIZE, 1);
  //device->DrawPrimitiveUP(
  //	D3DPT_POINTLIST,
  //	1,
  //	&vtx,
  //	sizeof(VERTEX_2D)
  //);
//}

//void NativeProcess_Graphics::Graphics_DrawSquare(GameObjectRenderState* state, T_FLOAT width, T_FLOAT height) const
//{
  //const T_FLOAT x = state->position.x;
  //const T_FLOAT y = state->position.y;
  //const T_FLOAT x1 = x;
  //const T_FLOAT y1 = y;
  //const T_FLOAT x2 = x + w;
  //const T_FLOAT y2 = y;
  //const T_FLOAT x3 = x;
  //const T_FLOAT y3 = y + h;
  //const T_FLOAT x4 = x + w;
  //const T_FLOAT y4 = y + h;

  //const D3DCOLOR color = D3DCOLOR_RGBA((int)state->color.r, (int)state->color.g, (int)state->color.b, (int)state->color.a);

  //LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)state->renderObject;
  //VERTEX_2D vtx[] = {
  //	{ D3DXVECTOR4(x1, y1, 1.0f, 1.0f), color },
  //	{ D3DXVECTOR4(x2, y2, 1.0f, 1.0f), color },
  //	{ D3DXVECTOR4(x3, y3, 1.0f, 1.0f), color },
  //	{ D3DXVECTOR4(x4, y4, 1.0f, 1.0f), color },
  //};

  //int* a = new int[5];

  //device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
  //device->DrawPrimitiveUP(
  //	D3DPT_TRIANGLESTRIP,
  //	2,
  //	vtx,
  //	sizeof(VERTEX_2D)
  //);
//}