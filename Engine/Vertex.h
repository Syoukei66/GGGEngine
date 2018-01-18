#pragma once
#include "NativeType.h"
#include "Geometry.h"
#include "Color.h"

// =================================================================
// Vertex
// =================================================================
struct Vertex
{
  T_FLOAT coord[4];
  T_FLOAT color[4];
  Vertex();
  Vertex(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  Vertex(const TVec4f& coord);
  void Init();
};

// =================================================================
// SpriteVertex
// =================================================================
struct SpriteVertex
{
  T_FLOAT coord[4];
  T_FLOAT color[4];
  T_FLOAT uv[2];
  SpriteVertex();
  SpriteVertex(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT u, T_FLOAT v);
  SpriteVertex(const TVec4f& coord, const TVec2f& uv);
  void Init();
};

// =================================================================
// Vertex3D
// =================================================================
struct Vertex3D
{
  T_FLOAT coord[4];
  T_FLOAT normal[3];
  T_FLOAT color[4];
  T_FLOAT uv[2];
  Vertex3D();
  Vertex3D(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT u, T_FLOAT v, T_FLOAT normal_x, T_FLOAT normal_y, T_FLOAT normal_z);
  Vertex3D(const TVec4f& coord, const TVec2f& uv, const TVec3f& normal);
  void Init();
};
