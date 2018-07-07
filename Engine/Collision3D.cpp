#include "Collision3D.h"

namespace Collision3D
{

bool Sphare_Sphare(const TVec3f & ap, T_FLOAT ar, const TVec3f & bp, T_FLOAT br)
{
  const T_FLOAT dx = ap.x - bp.x;
  const T_FLOAT dy = ap.y - bp.y;
  const T_FLOAT dz = ap.z - bp.z;
  const T_FLOAT r = ar + br;
  return dx * dx + dy * dy + dz * dz <= r * r;
}

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
  const T_FLOAT t = -b - sqrtf(discriminant);
  if (t < 0.0)
  {
    return false;
  }
  *intersection = ray_offset + direction * t;
  return true;
}

bool Frustum_AABB(const Matrix4x4& mat, const TVec3f& positive, const TVec3f& negative, T_INT8* first_index)
{
  //http://edom18.hateblo.jp/entry/2017/10/29/112908
  // 0: Left, 1: Right, 2: Bottm, 3: Top
  //for (T_UINT8 i = 0; i < 4; i++)
  //{
  //  T_FLOAT a, b, c, d;
  //  const T_UINT8 r = i / 2;
  //  if (i % 2 == 0)
  //  {
  //    // •½–Ê‚Ì•û’öŽ®
  //    // ax + by + cz + d = 0
  //    a = (*mat)[3][0] - (*mat)[r][0];
  //    b = (*mat)[3][1] - (*mat)[r][1];
  //    c = (*mat)[3][2] - (*mat)[r][2];
  //    d = (*mat)[3][3] - (*mat)[r][3];
  //  }
  //  else
  //  {
  //    a = (*mat)[3][0] + (*mat)[r][0];
  //    b = (*mat)[3][1] + (*mat)[r][1];
  //    c = (*mat)[3][2] + (*mat)[r][2];
  //    d = (*mat)[3][3] + (*mat)[r][3];
  //  }
  //  const TVec3f normal = -TVec3f(a, b, c).Normalized();
  //  const TVec3f offset = 
  //  const T_FLOAT dp = TVec3f::InnerProduct(positive, normal);
  //  if (dp < 0)
  //  {
  //    return State.Outside;
  //  }

  //  float dn = planes[i].GetDistanceToPoint(vn);
  //  if (dn < 0)
  //  {
  //    result = State.Intersect;
  //  }
  //}


  //for (int i = 0; i < 4; i++)
  //{
  //  float a, b, c, d;
  //  int r = i / 2;
  //  if (i % 2 == 0)
  //  {
  //    // •½–Ê‚Ì•û’öŽ®
  //    // ax + by + cz + d = 0
  //    a = pmat[3, 0] - pmat[r, 0];
  //    b = pmat[3, 1] - pmat[r, 1];
  //    c = pmat[3, 2] - pmat[r, 2];
  //    d = pmat[3, 3] - pmat[r, 3];
  //  }
  //  else
  //  {
  //    a = pmat[3, 0] + pmat[r, 0];
  //    b = pmat[3, 1] + pmat[r, 1];
  //    c = pmat[3, 2] + pmat[r, 2];
  //    d = pmat[3, 3] + pmat[r, 3];
  //  }

  //  Vector3 normal = -new Vector3(a, b, c).normalized;
  //  normal = eyeTrans.rotation * normal;

  //  result[i] = new Plane(normal, eyeTrans.position);
  //}



  //TVec3f p = positive;
  //proj->Apply(&p);

  return 0;
}

}
