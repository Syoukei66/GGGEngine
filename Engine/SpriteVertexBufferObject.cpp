#include "SpriteVertexBufferObject.h"
#include <stdlib.h>
#include "Sprite.h"
#include "Vertex.h"

//enum { SPRITE_INDEXES_COUNT = 6 };
//static const T_UINT16 SPRITE_INDEXES[SPRITE_INDEXES_COUNT] =
//{
//  0, 1, 2,
//  1, 3, 2
//};

// =================================================================
// Factory Method
// =================================================================
SpriteVertexBufferObject* SpriteVertexBufferObject::Create()
{
  SpriteVertexBufferObject* ret = new SpriteVertexBufferObject();
  ret->Init();
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
SpriteVertexBufferObject::SpriteVertexBufferObject()
{
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void SpriteVertexBufferObject::OnInit()
{
  for (T_UINT8 i = 0; i < V_VERTEX_MAX; ++i)
  {
    this->vertexes_[i] = Vertex::VCT();
  }
}

void SpriteVertexBufferObject::OnUpdateCoord(GameObject* entity)
{
  Shape* shape = (Shape*)entity;
  const T_FLOAT w = shape->GetWidth();
  const T_FLOAT h = shape->GetHeight();
  const T_FLOAT x0 = -w * 0.5f;
  const T_FLOAT y0 = -h * 0.5f;
  const bool xReverce = shape->GetTransform()->GetScaleX() < 0.0f;
  const bool yReverce = shape->GetTransform()->GetScaleY() < 0.0f;

  if (xReverce)
  {
    this->vertexes_[V_VERTEX_V0].coord[0] = x0 + w;
    this->vertexes_[V_VERTEX_V1].coord[0] = x0 + w;
    this->vertexes_[V_VERTEX_V2].coord[0] = x0;
    this->vertexes_[V_VERTEX_V3].coord[0] = x0;
  }
  else
  {
    this->vertexes_[V_VERTEX_V0].coord[0] = x0;
    this->vertexes_[V_VERTEX_V1].coord[0] = x0;
    this->vertexes_[V_VERTEX_V2].coord[0] = x0 + w;
    this->vertexes_[V_VERTEX_V3].coord[0] = x0 + w;
  }
  if (yReverce)
  {
    this->vertexes_[V_VERTEX_V0].coord[1] = y0 + h;
    this->vertexes_[V_VERTEX_V1].coord[1] = y0;
    this->vertexes_[V_VERTEX_V2].coord[1] = y0 + h;
    this->vertexes_[V_VERTEX_V3].coord[1] = y0;
  }
  else
  {
    this->vertexes_[V_VERTEX_V0].coord[1] = y0;
    this->vertexes_[V_VERTEX_V1].coord[1] = y0 + h;
    this->vertexes_[V_VERTEX_V2].coord[1] = y0;
    this->vertexes_[V_VERTEX_V3].coord[1] = y0 + h;
  }

  this->vertexes_[V_VERTEX_V0].coord[2] = 0.1f;
  this->vertexes_[V_VERTEX_V1].coord[2] = 0.1f;
  this->vertexes_[V_VERTEX_V2].coord[2] = 0.1f;
  this->vertexes_[V_VERTEX_V3].coord[2] = 0.1f;
}

T_UINT32 SpriteVertexBufferObject::GetVertexesCount() const
{
  return V_VERTEX_MAX;
  //return SPRITE_INDEXES_COUNT;
}

const void* SpriteVertexBufferObject::GetVertexes() const
{
  return (void*)this->vertexes_;
}

const T_UINT16* SpriteVertexBufferObject::GetIndexes() const
{
  return nullptr;
  //return SPRITE_INDEXES;
}

inline INativeProcess_Graphics::PrimitiveType SpriteVertexBufferObject::GetPrimitiveType()
{
  return INativeProcess_Graphics::PRIMITIVE_TRIANGLES;
}

Vertex::VertexType SpriteVertexBufferObject::GetVertexType()
{
  return Vertex::VERTEX_TYPE_VCT;
}

void SpriteVertexBufferObject::OnVertexUvDirty()
{
  this->vertex_uv_dirty_ = true;
}

// =================================================================
// Method
// =================================================================
void SpriteVertexBufferObject::UpdateTexture(Shape* entity, ITextureRegion* region)
{
  if (!this->vertex_uv_dirty_)
  {
    return;
  }
  const T_FLOAT u0 = region->GetU0();
  const T_FLOAT v0 = region->GetV0();
  const T_FLOAT u1 = region->GetU1();
  const T_FLOAT v1 = region->GetV1();
  const bool xReverce = entity->GetTransform()->GetScaleX() < 0;
  const bool yReverce = entity->GetTransform()->GetScaleY() < 0;

  if (xReverce)
  {
    this->vertexes_[V_VERTEX_V0].uv[0] = u1;
    this->vertexes_[V_VERTEX_V1].uv[0] = u1;
    this->vertexes_[V_VERTEX_V2].uv[0] = u0;
    this->vertexes_[V_VERTEX_V3].uv[0] = u0;
  }
  else
  {
    this->vertexes_[V_VERTEX_V0].uv[0] = u0;
    this->vertexes_[V_VERTEX_V1].uv[0] = u0;
    this->vertexes_[V_VERTEX_V2].uv[0] = u1;
    this->vertexes_[V_VERTEX_V3].uv[0] = u1;
  }
  if (yReverce)
  {
    this->vertexes_[V_VERTEX_V0].uv[1] = v0;
    this->vertexes_[V_VERTEX_V1].uv[1] = v1;
    this->vertexes_[V_VERTEX_V2].uv[1] = v0;
    this->vertexes_[V_VERTEX_V3].uv[1] = v1;
  }
  else
  {
    this->vertexes_[V_VERTEX_V0].uv[1] = v1;
    this->vertexes_[V_VERTEX_V1].uv[1] = v0;
    this->vertexes_[V_VERTEX_V2].uv[1] = v1;
    this->vertexes_[V_VERTEX_V3].uv[1] = v0;
  }

  this->vertex_uv_dirty_ = false;
}

