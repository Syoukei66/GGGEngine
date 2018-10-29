#pragma once

#include "../Core/Vector3.h"
#include "../Core/Matrix4x4.h"

namespace Collision3D
{

bool Sphare_Sphare(const TVec3f& ap, T_FLOAT ar, const TVec3f& bp, T_FLOAT br);
bool Ray_Sphare(const TVec3f& ray_offset, const TVec3f& direction, const TVec3f& sphare_pos, float radius, TVec3f* intersection);

//first_indexには内側の場合は0,それ以外の場合は面のインデックス(1~6)が戻ってくる
//positiveで外側だった場合は正の値、negativeの場合は負の値として帰ってくる
//前回判定されたインデックスを最初に判定する事で、判定の高速化が行える
//nullptrの場合は高速化無しで実行
//1 left 2 right 3 bottom 4 top 5 near 6 far 
bool Frustum_AABB(const Matrix4x4& view_proj_matrix, const TVec3f& positive, const TVec3f& negative, T_INT8* first_index = nullptr);

}