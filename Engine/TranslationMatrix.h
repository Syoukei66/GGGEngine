#pragma once

#include "Eigen\Core.h"
#include "Eigen\Geometry.h"

#include "NativeType.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"  

union TranslationMatrix
{
  // =================================================================
  // Constants
  // =================================================================
public:
  static const TranslationMatrix zero;

  // =================================================================
  // Data Members
  // =================================================================
public:
  struct
  {
    T_FLOAT x, y, z;
  };
  T_FLOAT data[3];
  Eigen::Translation3f eigen;

  // =================================================================
  // Constructor
  // =================================================================
public:
  TranslationMatrix()
    : eigen(0.0f, 0.0f, 0.0f)
  {}

  TranslationMatrix(T_FLOAT x, T_FLOAT y)
    : eigen(x, y, 0.0f)
  {}

  TranslationMatrix(const TVec2f& value)
    : eigen(value.x, value.y, 0.0f)
  {}

  TranslationMatrix(T_FLOAT x, T_FLOAT y, T_FLOAT z)
    : eigen(x, y, z)
  {}

  TranslationMatrix(const Eigen::Vector3f& eigen)
    : eigen(eigen)
  {}

  TranslationMatrix(const Eigen::Translation3f& eigen)
    : eigen(eigen)
  {}

  // =================================================================
  // Copy Constructor / Assign operator
  // =================================================================
public:
  TranslationMatrix(const TranslationMatrix& other)
    : eigen(other.eigen)
  {}

  inline TranslationMatrix& operator = (const TranslationMatrix& other)
  {
    this->eigen = other.eigen;
    return *this;
  }

  // =================================================================
  // Cast Operator
  // =================================================================
public:
  inline operator Eigen::Translation3f() const
  {
    return this->eigen;
  }
  //inline operator Matrix4x4() const
  //{
  //  return Matrix4x4(Eigen::Matrix4f(this->eigen));
  //}

  // =================================================================
  // Methods
  // =================================================================
public:
  //inline Matrix4x4 ToMatrix()
  //{
  //  return Matrix4x4(Eigen::Matrix4f(this->eigen));
  //}
};