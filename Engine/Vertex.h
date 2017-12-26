#pragma once
#include "NativeType.h"
#include "Geometry.h"
#include "Color.h"

// =================================================================
// Vertex
// =================================================================
struct Vertex
{
  TVec4f coord;
  T_PACKED_COLOR_UINT32 packed_color;
  Vertex();
  Vertex(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  Vertex(const TVec4f& coord, T_PACKED_COLOR_UINT32 color);
  void Init();
};

// =================================================================
// SpriteVertex
// =================================================================
struct SpriteVertex
{
  TVec4f coord;
  T_PACKED_COLOR_UINT32 packed_color;
  TVec2f uv;
  SpriteVertex();
  SpriteVertex(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT u, T_FLOAT v);
  SpriteVertex(const TVec4f& coord, T_PACKED_COLOR_UINT32 color, const TVec2f& uv);
  void Init();
};

// =================================================================
// Vertex3D
// =================================================================
struct Vertex3D
{
  TVec4f coord;
  TVec3f normal;
  T_PACKED_COLOR_UINT32 packed_color;
  TVec2f uv;
  Vertex3D();
  Vertex3D(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT u, T_FLOAT v, T_FLOAT normal_x, T_FLOAT normal_y, T_FLOAT normal_z);
  Vertex3D(const TVec4f& coord, T_PACKED_COLOR_UINT32 color, const TVec2f& uv, const TVec3f& normal);
  void Init();
};
