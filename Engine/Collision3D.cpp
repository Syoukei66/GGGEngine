#include "Collision3D.h"

bool Ray_Sphare(const TVec3f& ray_offset, const TVec3f& direction, const TVec3f& sphare_pos, float radius, TVec3f* intersection)
{
  const TVec3f oc = ray_offset - sphare_pos;
  const T_FLOAT b = TVec3f::InnerProduct(oc, direction);
  const T_FLOAT c = TVec3f::InnerProduct(oc, oc) - radius * radius;
  if (c > 0.0f && b > 0.0f)
  {
    return false;
  }
  const T_FLOAT discriminant = b * b - c;
  if (discriminant < 0.0)
  {
    return false;
  }
  const T_FLOAT t = - b - sqrtf(discriminant);
  if (t < 0.0)
  {
    return false;
  }
  *intersection = ray_offset + direction * t;
  return true;
}
