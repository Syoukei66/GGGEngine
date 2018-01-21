#include "Vertex.h"
#include <stdlib.h>

namespace Vertex
{

// =================================================================
// Vertex
// =================================================================
VC::VC()
  : coord()
  , color(0xffffffff)
{}

VC::VC(T_FLOAT x, T_FLOAT y, T_FLOAT z)
  : coord{ x, y, z, 1.0f }
  , color(0xffffffff)
{}

VC::VC(const TVec4f& coord)
  : coord{ coord.x, coord.y, coord.z, coord.w }
  , color(0xffffffff)
{}

// =================================================================
// SpriteVertex
// =================================================================
VCT::VCT()
  : coord{ 0.0f, 0.0f, 0.0f, 1.0f }
  , color(0xffffffff)
  , uv{0.0f, 0.0f}
{}

VCT::VCT(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT u, T_FLOAT v)
  : coord{ x, y, z, 1.0f }
  , color(0xffffffff)
  , uv{ u, v }
{}

VCT::VCT(const TVec4f& coord, const TVec2f& uv)
  : coord{ coord.x, coord.y, coord.z, coord.w }
  , color(0xffffffff)
  , uv{ uv.x, uv.y }
{}

// =================================================================
// Vertex3D
// =================================================================
VNCT::VNCT()
  : coord{ 0.0f, 0.0f, 0.0f, 1.0f }
  , normal{ 0.0f, 0.0f, 0.0f }
  , color(0xffffffff)
  , uv{ 0.0f, 0.0f }
{}

VNCT::VNCT(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT u, T_FLOAT v, T_FLOAT normal_x, T_FLOAT normal_y, T_FLOAT normal_z)
  : coord{ x, y, z, 1.0f }
  , color(0xffffffff)
  , normal{ normal_x, normal_y, normal_z }
  , uv{ u, v }
{}

VNCT::VNCT(const TVec4f& coord, const TVec2f& uv, const TVec3f& normal)
  : coord{ coord.x, coord.y, coord.z, coord.w }
  , color(0xffffffff)
  , normal{ normal.x, normal.y, normal.z }
  , uv{ uv.x, uv.y }
{}

} // namespace Vertex
