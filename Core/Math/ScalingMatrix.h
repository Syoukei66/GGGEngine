#pragma once

#include <Eigen/Core.h>
#include <Eigen/Geometry.h>

struct ScalingMatrix
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
  union
  {
    struct
    {
      T_FLOAT x, y, z;
    };
    T_FLOAT data[3];
    Eigen::DiagonalMatrix<T_FLOAT, 3> eigen;
  };

  // =================================================================
  // Constructor
  // =================================================================
public:
  ScalingMatrix(T_FLOAT value)
    : eigen(Eigen::Scaling(value, value, value))
  {}
  ScalingMatrix(T_FLOAT x, T_FLOAT y)
    : eigen(Eigen::Scaling(x, y, 1.0f))
  {}
  ScalingMatrix(const TVec2f& value)
    : eigen(Eigen::Scaling(value.x, value.y, 1.0f))
  {}
  ScalingMatrix(T_FLOAT x, T_FLOAT y, T_FLOAT z)
    : eigen(Eigen::Scaling(x, y, z))
  {}
  ScalingMatrix(const TVec3f& value)
    : eigen(Eigen::Scaling(value.x, value.y, value.z))
  {}
  ScalingMatrix(const Eigen::Vector3f& eigen)
    : eigen(eigen)
  {}

  // =================================================================
  // Copy Constructor / Assign operator
  // =================================================================
public:
  ScalingMatrix(const ScalingMatrix& other)
    : eigen(other.eigen)
  {}

  GG_INLINE ScalingMatrix& operator = (const ScalingMatrix& other)
  {
    this->eigen = other.eigen;
    return *this;
  }

  // =================================================================
  // Cast Operator
  // =================================================================
public:
  GG_INLINE operator Eigen::DiagonalMatrix<T_FLOAT, 3>() const
  {
    return this->eigen;
  }
  //GG_INLINE operator Matrix4x4() const
  //{
  //  return Matrix4x4(Eigen::Matrix4f(this->eigen.toDenseMatrix()));
  //}

  // =================================================================
  // Methods
  // =================================================================
public:
  //GG_INLINE Matrix4x4 ToMatrix()
  //{
  //  return Matrix4x4(Eigen::Matrix4f(this->eigen.toDenseMatrix()));
  //}
};