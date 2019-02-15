#pragma once

#include <Asset/Mesh/DynamicMesh.h>

namespace MeshFactory
{
namespace CubeSphere
{

/*!
 * @brief CubeSphere���b�V���𐶐�����
 * @param format ���_�t�H�[�}�b�g
 * @param scale_x CubeSphere��X�����̑傫��
 * @param scale_y CubeSphere��X�����̑傫��
 * @param scale_z CubeSphere��X�����̑傫��
 * @param resolution_x X�����̖ʂ̃��b�V���𑜓x
 * @param resolution_y Y�����̖ʂ̃��b�V���𑜓x
 * @param resolution_z Z�����̖ʂ̃��b�V���𑜓x
 * @param tile_count_x X�����̖ʂ̃e�N�X�`�����[�v��
 * @param tile_count_y Y�����̖ʂ̃e�N�X�`�����[�v��
 * @param tile_count_z Z�����̖ʂ̃e�N�X�`�����[�v��
 */
UniqueRef<rcDynamicMesh> Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z,
  T_FLOAT tile_count_x, T_FLOAT tile_count_y, T_FLOAT tile_count_z,
  T_UINT32 roundness
);

/*!
 * @brief CubeSphere���b�V���𐶐�����B�e�N�X�`�����[�v�񐔂͂P�ŌŒ�
 * @param format ���_�t�H�[�}�b�g
 * @param scale_x CubeSphere��X�����̑傫��
 * @param scale_y CubeSphere��X�����̑傫��
 * @param scale_z CubeSphere��X�����̑傫��
 * @param resolution_x X�����̖ʂ̃��b�V���𑜓x&�e�N�X�`�����[�v��
 * @param resolution_y Y�����̖ʂ̃��b�V���𑜓x&�e�N�X�`�����[�v��
 * @param resolution_z Z�����̖ʂ̃��b�V���𑜓x&�e�N�X�`�����[�v��
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
 * @brief CubeSphere���b�V���𐶐�����B�e�N�X�`���𑜓x�ƃe�N�X�`�����[�v�񐔂͂P�ŌŒ�
 * @param format ���_�t�H�[�}�b�g
 * @param scale_x CubeSphere��X�����̑傫��
 * @param scale_y CubeSphere��X�����̑傫��
 * @param scale_z CubeSphere��X�����̑傫��
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
 * @brief CubeSphere���b�V���𐶐�����B�e�N�X�`���𑜓x�ƃe�N�X�`�����[�v�񐔂͂P�ŌŒ�
 * @param format ���_�t�H�[�}�b�g
 * @param scale CubeSphere�̑傫��
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