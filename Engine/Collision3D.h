#pragma once

#include "Geometry.h"

namespace Collision3D
{

inline bool Sphare_Sphare(const TVec3f& ap, T_FLOAT ar, const TVec3f& bp, T_FLOAT br)
{
  const T_FLOAT dx = ap.x - bp.x;
  const T_FLOAT dy = ap.y - bp.y;
  const T_FLOAT dz = ap.z - bp.z;
  const T_FLOAT r = ar + br;
  return dx * dx + dy * dy + dz * dz <= r * r;
}

bool Ray_Sphare(const TVec3f& ray_offset, const TVec3f& direction, const TVec3f& sphare_pos, float radius, TVec3f* intersection);

}