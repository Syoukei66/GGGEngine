#pragma once
#include "NativeType.h"
#include "Geometry.h"
#include "Color.h"

namespace Vertex
{

// V = Vertex Coord
// C = Color
// T = Texture Coord
// N = Normal

enum VertexType
{
  VERTEX_TYPE_VC,
  VERTEX_TYPE_VCT,
  VERTEX_TYPE_VNCT,

  VERTEX_TYPE_DATANUM,
};

struct VC
{
  T_FLOAT coord[4];
  T_PACKED_COLOR_UINT32 color;
  VC();
  VC(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  VC(const TVec4f& coord);
};

struct VCT
{
  T_FLOAT coord[4];
  T_PACKED_COLOR_UINT32 color;
  T_FLOAT uv[2];
  VCT();
  VCT(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT u, T_FLOAT v);
  VCT(const TVec4f& coord, const TVec2f& uv);
};

struct VNCT
{
  T_FLOAT coord[4];
  T_FLOAT normal[3];
  T_PACKED_COLOR_UINT32 color;
  T_FLOAT uv[2];
  VNCT();
  VNCT(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT u, T_FLOAT v, T_FLOAT normal_x, T_FLOAT normal_y, T_FLOAT normal_z);
  VNCT(const TVec4f& coord, const TVec2f& uv, const TVec3f& normal);
};

static const T_UINT32 VERTEX_SIZE[Vertex::VERTEX_TYPE_DATANUM] =
{
  sizeof(VC),
  sizeof(VCT),
  sizeof(VNCT),
};

} // namespace Vertex
