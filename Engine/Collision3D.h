#pragma once

#include "../Core/Vector3.h"
#include "../Core/Matrix4x4.h"

namespace Collision3D
{

bool Sphare_Sphare(const TVec3f& ap, T_FLOAT ar, const TVec3f& bp, T_FLOAT br);
bool Ray_Sphare(const TVec3f& ray_offset, const TVec3f& direction, const TVec3f& sphare_pos, float radius, TVec3f* intersection);

//first_index�ɂ͓����̏ꍇ��0,����ȊO�̏ꍇ�͖ʂ̃C���f�b�N�X(1~6)���߂��Ă���
//positive�ŊO���������ꍇ�͐��̒l�Anegative�̏ꍇ�͕��̒l�Ƃ��ċA���Ă���
//�O�񔻒肳�ꂽ�C���f�b�N�X���ŏ��ɔ��肷�鎖�ŁA����̍��������s����
//nullptr�̏ꍇ�͍����������Ŏ��s
//1 left 2 right 3 bottom 4 top 5 near 6 far 
bool Frustum_AABB(const Matrix4x4& view_proj_matrix, const TVec3f& positive, const TVec3f& negative, T_INT8* first_index = nullptr);

}