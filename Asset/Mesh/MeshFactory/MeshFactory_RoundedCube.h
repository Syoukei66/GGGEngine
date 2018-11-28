#pragma once

#include <Asset/Mesh/DynamicMesh.h>

namespace MeshFactory
{
namespace CubeSphere
{

/*!
 * @brief CubeSphereメッシュを生成する
 * @param format 頂点フォーマット
 * @param scale_x CubeSphereのX方向の大きさ
 * @param scale_y CubeSphereのX方向の大きさ
 * @param scale_z CubeSphereのX方向の大きさ
 * @param resolution_x X方向の面のメッシュ解像度
 * @param resolution_y Y方向の面のメッシュ解像度
 * @param resolution_z Z方向の面のメッシュ解像度
 * @param tile_count_x X方向の面のテクスチャループ回数
 * @param tile_count_y Y方向の面のテクスチャループ回数
 * @param tile_count_z Z方向の面のテクスチャループ回数
 */
UniqueRef<rcDynamicMesh> Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z,
  T_FLOAT tile_count_x, T_FLOAT tile_count_y, T_FLOAT tile_count_z,
  T_UINT32 roundness
);

/*!
 * @brief CubeSphereメッシュを生成する。テクスチャループ回数は１で固定
 * @param format 頂点フォーマット
 * @param scale_x CubeSphereのX方向の大きさ
 * @param scale_y CubeSphereのX方向の大きさ
 * @param scale_z CubeSphereのX方向の大きさ
 * @param resolution_x X方向の面のメッシュ解像度&テクスチャループ回数
 * @param resolution_y Y方向の面のメッシュ解像度&テクスチャループ回数
 * @param resolution_z Z方向の面のメッシュ解像度&テクスチャループ回数
 */
static GG_INLINE UniqueRef<rcDynamicMesh> Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z,
  T_UINT32 roundness
)
{
  return Create(
    format,
    scale_x, scale_y, scale_z,
    resolution_x, resolution_y, resolution_z,
    1.0f, 1.0f, 1.0f,
    roundness
  );
}

/*!
 * @brief CubeSphereメッシュを生成する。テクスチャ解像度とテクスチャループ回数は１で固定
 * @param format 頂点フォーマット
 * @param scale_x CubeSphereのX方向の大きさ
 * @param scale_y CubeSphereのX方向の大きさ
 * @param scale_z CubeSphereのX方向の大きさ
 */
static GG_INLINE UniqueRef<rcDynamicMesh> Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  T_UINT32 roundness
)
{
  return Create(
    format,
    scale_x, scale_y, scale_z,
    1, 1, 1,
    1.0f, 1.0f, 1.0f,
    roundness
  );
}

/*!
 * @brief CubeSphereメッシュを生成する。テクスチャ解像度とテクスチャループ回数は１で固定
 * @param format 頂点フォーマット
 * @param scale CubeSphereの大きさ
 */
static GG_INLINE UniqueRef<rcDynamicMesh> Create(
  T_UINT32 format,
  T_FLOAT scale,
  T_UINT32 roundness
)
{
  return Create(
    format,
    scale, scale, scale,
    1, 1, 1,
    1.0f, 1.0f, 1.0f,
    roundness
  );
}

} // namespace CubeSphere
} // namespace MeshFactory