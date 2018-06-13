#pragma once

#include "Eigen\Core.h"
#include "Eigen\Geometry.h"

#include "NativeType.h"

#include "Vector2.h"
#include "Vector3.h"

union ScalingMatrix
{
  // =================================================================
  // Constants
  // =================================================================
public:
  static const ScalingMatrix identity;

  // =================================================================
  // Data Members
  // =================================================================
public:
  struct
  {
    T_FLOAT x, y, z;
  };
  T_FLOAT data[3];
  Eigen::DiagonalMatrix<T_FLOAT, 3> eigen;

  // =================================================================
  // Constructor
  // =================================================================
public:
  //ScalingMatrix(T_FLOAT value)
  //  : eigen
  //{
  //  return Matrix4x4(Eigen::Scaling(value, value, value));
  //}
  //ScalingMatrix(T_FLOAT x, T_FLOAT y)
  //{
  //  return Matrix4x4(Eigen::Scaling(x, y, 1.0f));
  //}
  //ScalingMatrix(const TVec2f& value)
  //{
  //  return Matrix4x4(Eigen::Scaling(value.x, value.y, 1.0f));
  //}
  //ScalingMatrix(T_FLOAT x, T_FLOAT y, T_FLOAT z)
  //{
  //  return Matrix4x4(Eigen::Scaling(x, y, z));
  //}
  //ScalingMatrix(const TVec3f& value)
  //{
  //  return Matrix4x4(Eigen::Scaling(value.x, value.y, value.z));
  //}
  //ScalingMatrix(T_FLOAT x)
  //{
  //  return Matrix4x4(Eigen::Scaling(x, 1.0f, 1.0f));
  //}
  //ScalingMatrix(T_FLOAT y)
  //{
  //  return Matrix4x4(Eigen::Scaling(1.0f, y, 1.0f));
  //}
  //ScalingMatrix(T_FLOAT z)
  //{
  //  return Matrix4x4(Eigen::Scaling(1.0f, 1.0f, z));
  //}


  // =================================================================
  // Copy Constructor / Assign operator
  // =================================================================
public:

};