#pragma once

#include <Asset/Mesh/DynamicMesh.h>

namespace MeshFactory
{
namespace UVSphere
{

// UV1 �����Ŏw�肵��tile_count�𔽉f����UV
// UV2 Plane�S�̂̒��_���W��(0.0f ~ 1.0f)�ɃX�P�[�����O����UV
// UV3 UV1�Ɠ���
// UV4 UV1�Ɠ���
//

/*!
 * @brief Cube���b�V���𐶐�����
 * @param format ���_�t�H�[�}�b�g
 * @param resolution_x X�����̖ʂ̃��b�V���𑜓x
 * @param resolution_y Y�����̖ʂ̃��b�V���𑜓x
 */
UniqueRef<rcDynamicMesh> Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z,
  T_FLOAT tile_count_x, T_FLOAT tile_count_y, T_FLOAT tile_count_z
);

/*!
 * @brief Cube���b�V���𐶐�����B�e�N�X�`���𑜓x�ƃe�N�X�`�����[�v�񐔂͂P�ŌŒ�
 * @param format ���_�t�H�[�}�b�g
 * @param scale Cube�̑傫��
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