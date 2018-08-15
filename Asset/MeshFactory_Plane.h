#pragma once

#include "Mesh.h"

namespace MeshFactory
{
namespace Plane
{

// UV1 引数で指定したtile_countを反映したUV
// UV2 Plane全体の頂点座標を(0.0f ~ 1.0f)にスケーリングしたUV
// UV3 UV1と同じ
// UV4 UV1と同じ

//
Mesh* Create(T_UINT32 format, T_FLOAT scale_x, T_FLOAT scale_y, T_UINT32 resolution_x, T_UINT32 resolution_y, T_FLOAT tile_count_x, T_FLOAT tile_count_y, bool readonly);
//
inline Mesh* Create(T_UINT32 format, T_FLOAT scale_x, T_FLOAT scale_y, T_UINT32 resolution_x, T_UINT32 resolution_y, bool readonly)
{
  return Create(format, scale_x, scale_y, resolution_x, resolution_y, resolution_x, resolution_y, readonly);
}
//
inline Mesh* Create(T_UINT32 format, T_FLOAT scale_x, T_FLOAT scale_y, bool readonly)
{
  return Create(format, scale_x, scale_y, scale_x, scale_y, readonly);
}

}
}
