#include "NativeProcess_Graphics.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <Texture.h>
#include <ITextureRegion.h>
#include <Director.h>
#include "DirectXDirector.h"

static const D3DPRIMITIVETYPE PRIMITIVE_TYPES[INativeProcess_Graphics::PrimitiveType::PRIMITIVE_DATANUM] =
{
  D3DPT_POINTLIST,
  D3DPT_LINELIST,
  D3DPT_LINESTRIP,
  D3DPT_TRIANGLELIST,
  D3DPT_TRIANGLESTRIP,
  D3DPT_TRIANGLEFAN,
};

static const D3DBLEND BLENDMODE_TYPES[BlendFunction::BL_DATANUM] =
{
  D3DBLEND_ZERO,
  D3DBLEND_ONE,
  D3DBLEND_SRCCOLOR,
  D3DBLEND_INVSRCCOLOR,
  D3DBLEND_SRCALPHA,
  D3DBLEND_INVSRCALPHA,
  D3DBLEND_DESTCOLOR,
  D3DBLEND_INVDESTCOLOR,
  D3DBLEND_DESTALPHA,
  D3DBLEND_INVDESTALPHA,
};

static const DWORD FVF_TYPES[INativeProcess_Graphics::VERTEX_TYPE_DATANUM] =
{
  D3DFVF_XYZW | D3DFVF_DIFFUSE,
  D3DFVF_XYZW | D3DFVF_DIFFUSE | D3DFVF_TEX1,
  D3DFVF_XYZW | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL,
};

static const T_UINT32 VERTEX_SIZE[INativeProcess_Graphics::VERTEX_TYPE_DATANUM] =
{
  sizeof(Vertex),
  sizeof(SpriteVertex),
  sizeof(Vertex3D),
};

static int PRIMITIVE_SURF_NUM(INativeProcess_Graphics::PrimitiveType type, int num)
{
  if (type == INativeProcess_Graphics::PRIMITIVE_POINTS)
  {
    return num;
  }
  if (type == INativeProcess_Graphics::PRIMITIVE_LINES)
  {
    return num;
  }
  if (type == INativeProcess_Graphics::PRIMITIVE_LINESTRIP)
  {
    return num;
  }
  if (type == INativeProcess_Graphics::PRIMITIVE_TRIANGLES)
  {
    return num / 3;
  }
  if (type == INativeProcess_Graphics::PRIMITIVE_TRIANGLESTRIP)
  {
    return num - 2;
  }
  if (type == INativeProcess_Graphics::PRIMITIVE_TRIANGLEFAN)
  {
    return num - 2;
  }
  return num;
}

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

void NativeProcess_Graphics::Graphics_SetTransformView(NativeMatrixInstance* mat)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  device->SetTransform(D3DTS_VIEW, (LPD3DXMATRIX)mat);
}

void NativeProcess_Graphics::Graphics_SetTransformProjection(NativeMatrixInstance* mat)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  device->SetTransform(D3DTS_PROJECTION, (LPD3DXMATRIX)mat);
}

void NativeProcess_Graphics::Graphics_SetTransformWorld(NativeMatrixInstance* mat)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  device->SetTransform(D3DTS_WORLD, (LPD3DXMATRIX)mat);
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

void NativeProcess_Graphics::Graphics_SetBlendMode(BlendFunction::BlendMode src, BlendFunction::BlendMode dst)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  if (src == BlendFunction::BL_NOBLEND || dst == BlendFunction::BL_NOBLEND)
  {
    device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    return;
  }
  device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); 
  device->SetRenderState(D3DRS_SRCBLEND, BLENDMODE_TYPES[src]);
  device->SetRenderState(D3DRS_DESTBLEND, BLENDMODE_TYPES[dst]);
}

void NativeProcess_Graphics::Graphics_SetTexture(const Texture* texture)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  const LPDIRECT3DTEXTURE9 d3dTexture = texture ? (LPDIRECT3DTEXTURE9)texture->GetContents()->GetNativeInstance() : nullptr;
  if (this->texture_ != d3dTexture)
  {
    device->SetTexture(0, d3dTexture);
    this->texture_ = d3dTexture;
  }
}

void NativeProcess_Graphics::Graphics_SetMaterial(const Material* material)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  const D3DMATERIAL9* d3dMaterial = material ? (D3DMATERIAL9*)material->GetNativeMaterial() : nullptr;

  if (this->material_ != d3dMaterial)
  {
    device->SetMaterial(d3dMaterial);
    this->material_ = d3dMaterial;
  }
}

void NativeProcess_Graphics::Graphics_SetLightingEnabled(bool enabled)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  device->SetRenderState(D3DRS_LIGHTING, enabled);
}

void NativeProcess_Graphics::Graphics_PackColor4u8(T_PACKED_COLOR_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
{
  (*color) = (T_PACKED_COLOR_UINT32)D3DCOLOR_RGBA(r, g, b, a);
}

void NativeProcess_Graphics::Graphics_DrawPrimitive(GameObjectRenderState* state, PrimitiveType type, const Vertex* vertexes, T_UINT16 vertexes_count)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)state->GetRenderObject();

  device->SetFVF(D3DFVF_XYZW | D3DFVF_DIFFUSE);
  HRESULT hr = device->DrawPrimitiveUP(
    PRIMITIVE_TYPES[type],
    PRIMITIVE_SURF_NUM(type, vertexes_count),
    vertexes,
    sizeof(Vertex)
  );
}

void NativeProcess_Graphics::Graphics_DrawIndexedPrimitive(GameObjectRenderState * state, PrimitiveType type, const Vertex * vertexes, T_UINT16 vertexes_count, const T_UINT16 * indexes)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)state->GetRenderObject();

  device->SetFVF(D3DFVF_XYZW | D3DFVF_DIFFUSE);
  HRESULT hr = device->DrawIndexedPrimitiveUP(
    PRIMITIVE_TYPES[type],
    0,
    vertexes_count,
    PRIMITIVE_SURF_NUM(type, vertexes_count),
    indexes,
    D3DFMT_INDEX16,
    vertexes,
    sizeof(Vertex)
  );
}

void NativeProcess_Graphics::Graphics_DrawSprite(GameObjectRenderState* state, PrimitiveType type, const SpriteVertex* vertexes, T_UINT16 vertexes_count)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)state->GetRenderObject();

  device->SetFVF(D3DFVF_XYZW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
  HRESULT hr = device->DrawPrimitiveUP(
    PRIMITIVE_TYPES[type],
    PRIMITIVE_SURF_NUM(type, vertexes_count),
    vertexes,
    sizeof(SpriteVertex)
  );
}

void NativeProcess_Graphics::Graphics_DrawIndexedSprite(GameObjectRenderState* state, PrimitiveType type, const SpriteVertex * vertexes, T_UINT16 vertexes_count, const T_UINT16* indexes)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)state->GetRenderObject();

  //TODO:Ø‚è‘Ö‚¦‚ê‚é‚æ‚¤‚É
  //device->SetRenderState(D3DRS_LIGHTING, true);
  device->SetFVF(D3DFVF_XYZW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
  HRESULT hr = device->DrawIndexedPrimitiveUP(
    PRIMITIVE_TYPES[type],
    0,
    vertexes_count,
    PRIMITIVE_SURF_NUM(type, vertexes_count),
    indexes,
    D3DFMT_INDEX16,
    vertexes,
    sizeof(SpriteVertex)
  );
}

void NativeProcess_Graphics::Graphics_DrawVertexes(GameObjectRenderState* state, PrimitiveType primitive_type, VertexType vertex_type, const void* vertexes, T_UINT16 vertexes_count)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)state->GetRenderObject();
  device->SetFVF(FVF_TYPES[vertex_type]);
  HRESULT hr = device->DrawPrimitiveUP(
    PRIMITIVE_TYPES[primitive_type],
    PRIMITIVE_SURF_NUM(primitive_type, vertexes_count),
    vertexes,
    VERTEX_SIZE[vertex_type]
  );
}

void NativeProcess_Graphics::Graphics_DrawIndexedVertexes(GameObjectRenderState* state, PrimitiveType primitive_type, VertexType vertex_type, const void* vertexes, T_UINT16 vertexes_count, const T_UINT16* indexes)
{
  static const D3DFORMAT format = sizeof(T_UINT16) == 2 ? D3DFMT_INDEX16 : D3DFMT_INDEX32;
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)state->GetRenderObject();
  device->SetFVF(FVF_TYPES[vertex_type]);
  HRESULT hr = device->DrawIndexedPrimitiveUP(
    PRIMITIVE_TYPES[primitive_type],
    0,
    vertexes_count,
    PRIMITIVE_SURF_NUM(primitive_type, vertexes_count),
    indexes,
    format,
    vertexes,    
    VERTEX_SIZE[vertex_type]
  );
}

static std::map<T_UINT16, LP_LIGHT> light_map;


T_UINT16 NativeProcess_Graphics::Graphics_CreateLight(LP_LIGHT* light)
{
  //=================Œã‚ÅÁ‚·======================
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
  //TODO:’²‚×‚ÄŽÀ‘•
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

void NativeProcess_Graphics::Graphics_SetLightDiffuse(T_UINT16 light_id, LP_LIGHT light, const Color & color)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  D3DLIGHT9* d3d_light = (D3DLIGHT9*)light;
  d3d_light->Diffuse.r = color.GetRed() / 255.0f;
  d3d_light->Diffuse.g = color.GetGreen() / 255.0f;
  d3d_light->Diffuse.b = color.GetBlue() / 255.0f;
  d3d_light->Diffuse.a = color.GetAlpha() / 255.0f;
}

void NativeProcess_Graphics::Graphics_SetAmbient(const Color& color)
{
  const LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  device->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(
    color.GetRed() / 255.0f,
    color.GetGreen() / 255.0f,
    color.GetBlue() / 255.0f,
    color.GetAlpha() / 255.0f
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