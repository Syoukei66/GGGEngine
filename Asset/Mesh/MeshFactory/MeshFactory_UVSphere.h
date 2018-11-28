#pragma once

#include <Asset/Mesh/DynamicMesh.h>

namespace MeshFactory
{
namespace UVSphere
{

// UV1 引数で指定したtile_countを反映したUV
// UV2 Plane全体の頂点座標を(0.0f ~ 1.0f)にスケーリングしたUV
// UV3 UV1と同じ
// UV4 UV1と同じ
//

/*!
 * @brief Cubeメッシュを生成する
 * @param format 頂点フォーマット
 * @param resolution_x X方向の面のメッシュ解像度
 * @param resolution_y Y方向の面のメッシュ解像度
 */
UniqueRef<rcDynamicMesh> Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z,
  T_FLOAT tile_count_x, T_FLOAT tile_count_y, T_FLOAT tile_count_z
);

/*!
 * @brief Cubeメッシュを生成する。テクスチャ解像度とテクスチャループ回数は１で固定
 * @param format 頂点フォーマット
 * @param scale Cubeの大きさ
 */
static GG_INLINE UniqueRef<rcDynamicMesh> Create(
  T_UINT32 format,
  T_FLOAT scale
)
{
  return Create(
    format,
    scale, scale, scale,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f
  );
}

} // namespace Cube
} // namespace MeshFactory