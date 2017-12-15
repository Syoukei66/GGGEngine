#include "Vertex.h"
#include <stdlib.h>

// =================================================================
// Vertex
// =================================================================
Vertex::Vertex()
  : coord()
  , packed_color(Color::PACKED_WHITE)
{}

Vertex::Vertex(T_FLOAT x, T_FLOAT y, T_FLOAT z)
  : coord(x, y, z, 1.0f)
  , packed_color(Color::PACKED_WHITE)
{}

Vertex::Vertex(const TVec4f& coord, T_PACKED_COLOR_UINT32 color)
  : coord(coord)
  , packed_color(color)
{}

void Vertex::Init()
{
  this->coord = TVec4f(0.0f, 0.0f, 0.0f, 1.0f);
  this->packed_color = Color::PACKED_WHITE;
}

// =================================================================
// SpriteVertex
// =================================================================
SpriteVertex::SpriteVertex()
  : coord()
  , packed_color(Color::PACKED_WHITE)
  , uv()
{}

SpriteVertex::SpriteVertex(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT u, T_FLOAT v)
  : coord(x, y, z, 1.0f)
  , packed_color(Color::PACKED_WHITE)
  , uv(u, v)
{}

SpriteVertex::SpriteVertex(const TVec4f& coord, T_PACKED_COLOR_UINT32 color, const TVec2f& uv)
  : coord(coord)
  , packed_color(color)
  , uv(uv) 
{}

void SpriteVertex::Init()
{
  this->coord = TVec4f(0.0f, 0.0f, 0.0f, 1.0f);
  this->packed_color = Color::PACKED_WHITE;
  this->uv = TVec2f(0.0f, 0.0f);
}

// =================================================================
// Vertex3D
// =================================================================
Vertex3D::Vertex3D()
  : coord()
  , packed_color(Color::PACKED_WHITE)
  , uv() 
  , normal()
{
}

Vertex3D::Vertex3D(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT u, T_FLOAT v, T_FLOAT normal_x, T_FLOAT normal_y, T_FLOAT normal_z)
  : coord(x, y, z, 1.0f)
  , packed_color(Color::PACKED_WHITE)
  , uv(u, v)
  , normal(normal_x, normal_y, normal_z)
{
}

Vertex3D::Vertex3D(const TVec4f& coord, T_PACKED_COLOR_UINT32 color, const TVec2f& uv, const TVec3f& normal)
  : coord(coord)
  , packed_color(color)
  , uv(uv)
  , normal(normal)
{
}

void Vertex3D::Init()
{
  this->coord = TVec4f(0.0f, 0.0f, 0.0f, 1.0f);
  this->packed_color = Color::PACKED_WHITE;
  this->uv = TVec2f(0.0f, 0.0f);
  this->normal = TVec3f(0.0f, 0.0f, 0.0f);
}
