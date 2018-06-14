#pragma once

#include "TranslationMatrix.h"
#include "Quaternion.h"
#include "ScalingMatrix.h"
//
//Matrix4x4 Matrix4x4::TRS(const TVec3f& pos, const Quaternion& q, const TVec3f& s)
//{
//  Eigen::Affine3f ret;
//  ret = ScalingMatrix(s.eigen) * q.eigen * TranslationMatrix(pos.eigen);
//  return Matrix4x4(ret.matrix());
//}

Matrix4x4 Matrix4x4::TRS(const TranslationMatrix& t, const Quaternion& r, const ScalingMatrix& s)
{
  Eigen::Affine3f ret;
  ret = s.eigen * r.eigen * t.eigen;
  return Matrix4x4(ret.matrix());
}
