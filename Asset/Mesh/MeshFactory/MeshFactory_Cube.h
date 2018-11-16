#pragma once

#include <Asset/Mesh/Mesh.h>

namespace MeshFactory
{
namespace Cube
{

// UV1 �����Ŏw�肵��tile_count�𔽉f����UV
// UV2 Plane�S�̂̒��_���W��(0.0f ~ 1.0f)�ɃX�P�[�����O����UV
// UV3 UV1�Ɠ���
// UV4 UV1�Ɠ���
//
UniqueRef<rcMesh> Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z,
  T_FLOAT tile_count_x, T_FLOAT tile_count_y, T_FLOAT tile_count_z
);

//
static GG_INLINE UniqueRef<rcMesh> Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z
)
{
  return Create(format, scale_x, scale_y, scale_z,
    resolution_x, resolution_y, resolution_z,
    (T_FLOAT)resolution_x, (T_FLOAT)resolution_y, (T_FLOAT)resolution_z
  );
}
//
static GG_INLINE UniqueRef<rcMesh> Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z
)
{
  return Create(format, scale_x, scale_y, scale_z,
    (T_UINT32)scale_x, (T_UINT32)scale_y, (T_UINT32)scale_z
  );
}
//
static GG_INLINE UniqueRef<rcMesh> Create(T_UINT32 format, const TVec3f& scale)
{
  return Create(format, scale.x, scale.y, scale.z);
}
//
static GG_INLINE UniqueRef<rcMesh> Create(T_UINT32 format, const TVec3f& scale, const TVec3i& resolution)
{
  return Create(format, scale.x, scale.y, scale.z, resolution.x, resolution.y, resolution.z);
}
//
static GG_INLINE UniqueRef<rcMesh> Create(T_UINT32 format, const TVec3f& scale, const TVec3i& resolution, const TVec3f& tile_count)
{
  return Create(format, scale.x, scale.y, scale.z, resolution.x, resolution.y, resolution.z, tile_count.x, tile_count.y, tile_count.z);
}

} // namespace Cube
} // namespace MeshFactory