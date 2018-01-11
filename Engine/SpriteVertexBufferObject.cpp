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
    this->vertexes_[i].Init();
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
    this->vertexes_[V_VERTEX_V0].coord.x = x0 + w;
    this->vertexes_[V_VERTEX_V1].coord.x = x0 + w;
    this->vertexes_[V_VERTEX_V2].coord.x = x0;
    this->vertexes_[V_VERTEX_V3].coord.x = x0;
  }
  else
  {
    this->vertexes_[V_VERTEX_V0].coord.x = x0;
    this->vertexes_[V_VERTEX_V1].coord.x = x0;
    this->vertexes_[V_VERTEX_V2].coord.x = x0 + w;
    this->vertexes_[V_VERTEX_V3].coord.x = x0 + w;
  }
  if (yReverce)
  {
    this->vertexes_[V_VERTEX_V0].coord.y = y0 + h;
    this->vertexes_[V_VERTEX_V1].coord.y = y0;
    this->vertexes_[V_VERTEX_V2].coord.y = y0 + h;
    this->vertexes_[V_VERTEX_V3].coord.y = y0;
  }
  else
  {
    this->vertexes_[V_VERTEX_V0].coord.y = y0;
    this->vertexes_[V_VERTEX_V1].coord.y = y0 + h;
    this->vertexes_[V_VERTEX_V2].coord.y = y0;
    this->vertexes_[V_VERTEX_V3].coord.y = y0 + h;
  }

  this->vertexes_[V_VERTEX_V0].coord.z = 0.1f;
  this->vertexes_[V_VERTEX_V1].coord.z = 0.1f;
  this->vertexes_[V_VERTEX_V2].coord.z = 0.1f;
  this->vertexes_[V_VERTEX_V3].coord.z = 0.1f;
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

INativeProcess_Graphics::VertexType SpriteVertexBufferObject::GetVertexType()
{
  return INativeProcess_Graphics::VERTEX_TYPE_COORD_COLOR_UV;
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
    this->vertexes_[V_VERTEX_V0].uv.x = u1;
    this->vertexes_[V_VERTEX_V1].uv.x = u1;
    this->vertexes_[V_VERTEX_V2].uv.x = u0;
    this->vertexes_[V_VERTEX_V3].uv.x = u0;
  }
  else
  {
    this->vertexes_[V_VERTEX_V0].uv.x = u0;
    this->vertexes_[V_VERTEX_V1].uv.x = u0;
    this->vertexes_[V_VERTEX_V2].uv.x = u1;
    this->vertexes_[V_VERTEX_V3].uv.x = u1;
  }
  if (yReverce)
  {
    this->vertexes_[V_VERTEX_V0].uv.y = v0;
    this->vertexes_[V_VERTEX_V1].uv.y = v1;
    this->vertexes_[V_VERTEX_V2].uv.y = v0;
    this->vertexes_[V_VERTEX_V3].uv.y = v1;
  }
  else
  {
    this->vertexes_[V_VERTEX_V0].uv.y = v1;
    this->vertexes_[V_VERTEX_V1].uv.y = v0;
    this->vertexes_[V_VERTEX_V2].uv.y = v1;
    this->vertexes_[V_VERTEX_V3].uv.y = v0;
  }

  this->vertex_uv_dirty_ = false;
}

