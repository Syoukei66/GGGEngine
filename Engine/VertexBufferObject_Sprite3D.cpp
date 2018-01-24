#include "VertexBufferObject_Sprite3D.h"
#include "Sprite3D.h"

enum { SPRITE_VERTEX_COORDS_COUNT = 4 };
static TVec2f SPRITE_VERTEX_COORDS[SPRITE_VERTEX_COORDS_COUNT] =
{
  { -0.5f, -0.5f }, //0 ‰Eã
  { -0.5f,  0.5f }, //1 ‰E‰º
  {  0.5f, -0.5f }, //2 ¶‰º
  {  0.5f,  0.5f }, //3 ¶ã
};

enum { SPRITE_VERTEX_TEX_COORDS_COUNT = SPRITE_VERTEX_COORDS_COUNT };
static TVec2f SPRITE_VERTEX_TEX_COORDS[SPRITE_VERTEX_TEX_COORDS_COUNT] =
{
  { 0.0f, 0.0f },
  { 0.0f, 1.0f },
  { 1.0f, 0.0f },
  { 1.0f, 1.0f },
};

enum { SPRITE_SURFS_COUNT = 1 };
enum { SPRITE_TRIANGLES_COUNT = 2 * SPRITE_SURFS_COUNT };
enum { SPRITE_VERTEX_INDEXES_COUNT = 6 };
static const T_UINT16 SPRITE_VERTEX_INDEXES[SPRITE_VERTEX_INDEXES_COUNT] =
{
  0, 1, 2,
  1, 3, 2,
};

static const T_UINT16 SPRITE_VERTEX_TEX_INDEXES[SPRITE_VERTEX_INDEXES_COUNT] =
{
  0, 1, 2,
  1, 3, 2,
};


VertexBufferObject_Sprite3D::VertexBufferObject_Sprite3D()
{
}

void VertexBufferObject_Sprite3D::OnInit()
{
}

void VertexBufferObject_Sprite3D::OnUpdateCoord(GameObject* entity)
{
  Sprite3D* shape = (Sprite3D*)entity;
  const T_FLOAT w = shape->GetWidth();
  const T_FLOAT h = shape->GetHeight();
  const T_FLOAT x0 = -w * 0.5f;
  const T_FLOAT y0 = -h * 0.5f;

  this->vertexes_[V_VERTEX_V0].coord[0] = x0;
  this->vertexes_[V_VERTEX_V1].coord[0] = x0;
  this->vertexes_[V_VERTEX_V2].coord[0] = x0 + w;
  this->vertexes_[V_VERTEX_V3].coord[0] = x0 + w;

  this->vertexes_[V_VERTEX_V0].coord[1] = y0;
  this->vertexes_[V_VERTEX_V1].coord[1] = y0 + h;
  this->vertexes_[V_VERTEX_V2].coord[1] = y0;
  this->vertexes_[V_VERTEX_V3].coord[1] = y0 + h;
}

T_UINT32 VertexBufferObject_Sprite3D::GetVertexesCount() const
{
  return SPRITE_VERTEX_INDEXES_COUNT;
}

const void* VertexBufferObject_Sprite3D::GetVertexes() const
{
  return this->vertexes_;
}

const T_UINT16* VertexBufferObject_Sprite3D::GetIndexes() const
{
  return SPRITE_VERTEX_INDEXES;
}

INativeProcess_Graphics::PrimitiveType VertexBufferObject_Sprite3D::GetPrimitiveType()
{
  return INativeProcess_Graphics::PRIMITIVE_TRIANGLES;
}

Vertex::VertexType VertexBufferObject_Sprite3D::GetVertexType()
{
  return Vertex::VERTEX_TYPE_VCT;
}

void VertexBufferObject_Sprite3D::OnVertexUvDirty()
{
  this->vertex_uv_dirty_ = true;
}

void VertexBufferObject_Sprite3D::UpdateTexture(Sprite3D* entity, ITextureRegion * region)
{
  if (!this->vertex_uv_dirty_)
  {
    return;
  }
  const T_FLOAT u0 = region->GetU0();
  const T_FLOAT v0 = region->GetV0();
  const T_FLOAT u1 = region->GetU1();
  const T_FLOAT v1 = region->GetV1();

  this->vertexes_[V_VERTEX_V0].uv[0] = u0;
  this->vertexes_[V_VERTEX_V1].uv[0] = u0;
  this->vertexes_[V_VERTEX_V2].uv[0] = u1;
  this->vertexes_[V_VERTEX_V3].uv[0] = u1;

  this->vertexes_[V_VERTEX_V0].uv[1] = v1;
  this->vertexes_[V_VERTEX_V1].uv[1] = v0;
  this->vertexes_[V_VERTEX_V2].uv[1] = v1;
  this->vertexes_[V_VERTEX_V3].uv[1] = v0;

  this->vertex_uv_dirty_ = false;
}
