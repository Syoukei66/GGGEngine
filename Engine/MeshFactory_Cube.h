#pragma once

#include "Mesh.h"

namespace MeshFactory
{
namespace Cube
{

// UV1 �����Ŏw�肵��tile_count�𔽉f����UV
// UV2 Plane�S�̂̒��_���W��(0.0f ~ 1.0f)�ɃX�P�[�����O����UV
// UV3 UV1�Ɠ���
// UV4 UV1�Ɠ���
//
Mesh* Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z,
  T_FLOAT tile_count_x, T_FLOAT tile_count_y, T_FLOAT tile_count_z,
  bool readonly
);

//
inline Mesh* Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z,
  bool readonly
)
{
  return Create(format, scale_x, scale_y, scale_z, resolution_x, resolution_y, resolution_z, resolution_x, resolution_y, resolution_z, readonly);
}
//
inline Mesh* Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  bool readonly
)
{
  return Create(format, scale_x, scale_y, scale_z, (T_UINT32)scale_x, (T_UINT32)scale_y, (T_UINT32)scale_z, readonly);
}
//
inline Mesh* Create(T_UINT32 format, const TVec3f& scale, bool readonly)
{
  return Create(format, scale.x, scale.y, scale.z, readonly);
}
//
inline Mesh* Create(T_UINT32 format, const TVec3f& scale, const TVec3i& resolution, bool readonly)
{
  return Create(format, scale.x, scale.y, scale.z, resolution.x, resolution.y, resolution.z, readonly);
}
//
inline Mesh* Create(T_UINT32 format, const TVec3f& scale, const TVec3i& resolution, const TVec3f& tile_count, bool readonly)
{
  return Create(format, scale.x, scale.y, scale.z, resolution.x, resolution.y, resolution.z, tile_count.x, tile_count.y, tile_count.z, readonly);
}

} // namespace Cube
} // namespace MeshFactory