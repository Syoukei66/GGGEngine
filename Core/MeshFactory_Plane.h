#pragma once

#include "Mesh.h"

namespace MeshFactory
{
namespace Plane
{

// UV1 �����Ŏw�肵��tile_count�𔽉f����UV
// UV2 Plane�S�̂̒��_���W��(0.0f ~ 1.0f)�ɃX�P�[�����O����UV
// UV3 UV1�Ɠ���
// UV4 UV1�Ɠ���

//
rcMesh* Create(T_UINT32 format, T_FLOAT scale_x, T_FLOAT scale_y, T_UINT32 resolution_x, T_UINT32 resolution_y, T_FLOAT tile_count_x, T_FLOAT tile_count_y, bool read_only);
//
inline rcMesh* Create(T_UINT32 format, T_FLOAT scale_x, T_FLOAT scale_y, T_UINT32 resolution_x, T_UINT32 resolution_y, bool read_only)
{
  return Create(format, scale_x, scale_y, resolution_x, resolution_y, (T_FLOAT)resolution_x, (T_FLOAT)resolution_y, read_only);
}
//
inline rcMesh* Create(T_UINT32 format, T_FLOAT scale_x, T_FLOAT scale_y, bool read_only)
{
  return Create(format, scale_x, scale_y, (T_UINT32)scale_x, (T_UINT32)scale_y, read_only);
}

}
}
