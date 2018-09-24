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
rcMesh* Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z,
  T_FLOAT tile_count_x, T_FLOAT tile_count_y, T_FLOAT tile_count_z,
  bool read_only
);

//
inline rcMesh* Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z,
  bool read_only
)
{
  return Create(format, scale_x, scale_y, scale_z,
    resolution_x, resolution_y, resolution_z,
    (T_FLOAT)resolution_x, (T_FLOAT)resolution_y, (T_FLOAT)resolution_z,
    read_only);
}
//
inline rcMesh* Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  bool read_only
)
{
  return Create(format, scale_x, scale_y, scale_z,
    (T_UINT32)scale_x, (T_UINT32)scale_y, (T_UINT32)scale_z,
    read_only);
}
//
inline rcMesh* Create(T_UINT32 format, const TVec3f& scale, bool read_only)
{
  return Create(format, scale.x, scale.y, scale.z, read_only);
}
//
inline rcMesh* Create(T_UINT32 format, const TVec3f& scale, const TVec3i& resolution, bool read_only)
{
  return Create(format, scale.x, scale.y, scale.z, resolution.x, resolution.y, resolution.z, read_only);
}
//
inline rcMesh* Create(T_UINT32 format, const TVec3f& scale, const TVec3i& resolution, const TVec3f& tile_count, bool read_only)
{
  return Create(format, scale.x, scale.y, scale.z, resolution.x, resolution.y, resolution.z, tile_count.x, tile_count.y, tile_count.z, read_only);
}

} // namespace Cube
} // namespace MeshFactory