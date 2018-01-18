#include "Vertex.h"
#include <stdlib.h>

// =================================================================
// Vertex
// =================================================================
Vertex::Vertex()
  : coord()
  , color{ 1.0f, 1.0f, 1.0f, 1.0f }
{}

Vertex::Vertex(T_FLOAT x, T_FLOAT y, T_FLOAT z)
  : coord{ x, y, z, 1.0f }
  , color{ 1.0f, 1.0f, 1.0f, 1.0f }
{}

Vertex::Vertex(const TVec4f& coord)
  : coord{ coord.x, coord.y, coord.z, coord.w }
  , color{ 1.0f, 1.0f, 1.0f, 1.0f }
{}

void Vertex::Init()
{
  this->coord[0] = 0.0f;
  this->coord[1] = 0.0f;
  this->coord[2] = 0.0f;
  this->coord[3] = 1.0f;

  this->color[0] = 1.0f;
  this->color[1] = 1.0f;
  this->color[2] = 1.0f;
  this->color[3] = 1.0f;
}

// =================================================================
// SpriteVertex
// =================================================================
SpriteVertex::SpriteVertex()
  : coord{ 0.0f, 0.0f, 0.0f, 1.0f }
  , color{ 1.0f, 1.0f, 1.0f, 1.0f }
  , uv{0.0f, 0.0f}
{}

SpriteVertex::SpriteVertex(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT u, T_FLOAT v)
  : coord{ x, y, z, 1.0f }
  , color{ 1.0f, 1.0f, 1.0f, 1.0f }
  , uv{ u, v }
{}

SpriteVertex::SpriteVertex(const TVec4f& coord, const TVec2f& uv)
  : coord{ coord.x, coord.y, coord.z, coord.w }
  , color{ 1.0f, 1.0f, 1.0f, 1.0f }
  , uv{ uv.x, uv.y }
{}

void SpriteVertex::Init()
{
  this->coord[0] = 0.0f;
  this->coord[1] = 0.0f;
  this->coord[2] = 0.0f;
  this->coord[3] = 1.0f;

  this->color[0] = 1.0f;
  this->color[1] = 1.0f;
  this->color[2] = 1.0f;
  this->color[3] = 1.0f;

  this->uv[0] = 0.0f;
  this->uv[1] = 0.0f;
}

// =================================================================
// Vertex3D
// =================================================================
Vertex3D::Vertex3D()
  : coord{ 0.0f, 0.0f, 0.0f, 1.0f }
  , normal{ 0.0f, 0.0f, 0.0f }
  , color{ 1.0f, 1.0f, 1.0f, 1.0f }
  , uv{ 0.0f, 0.0f }
{}

Vertex3D::Vertex3D(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT u, T_FLOAT v, T_FLOAT normal_x, T_FLOAT normal_y, T_FLOAT normal_z)
  : coord{ x, y, z, 1.0f }
  , normal{ normal_x, normal_y, normal_z }
  , color{ 1.0f, 1.0f, 1.0f, 1.0f }
  , uv{ u, v }
{}

Vertex3D::Vertex3D(const TVec4f& coord, const TVec2f& uv, const TVec3f& normal)
  : coord{ coord.x, coord.y, coord.z, coord.w }
  , normal{ normal.x, normal.y, normal.z }
  , color{ 1.0f, 1.0f, 1.0f, 1.0f }
  , uv{ uv.x, uv.y }
{}

void Vertex3D::Init()
{
  this->coord[0] = 0.0f;
  this->coord[1] = 0.0f;
  this->coord[2] = 0.0f;
  this->coord[3] = 1.0f;

  this->normal[0] = 0.0f;
  this->normal[1] = 0.0f;
  this->normal[2] = 0.0f;

  this->color[0] = 1.0f;
  this->color[1] = 1.0f;
  this->color[2] = 1.0f;
  this->color[3] = 1.0f;

  this->uv[0] = 0.0f;
  this->uv[1] = 0.0f;
}
