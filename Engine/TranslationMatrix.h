#pragma once

#include "Eigen\Core.h"
#include "Eigen\Geometry.h"

#include "NativeType.h"

#include "Vector2.h"
#include "Vector3.h"

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

  TranslationMatrix(const TVec2f& value)
    : eigen(value.x, value.y, 0.0f)
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

  TranslationMatrix& operator = (const TranslationMatrix& other)
  {
    this->eigen = other.eigen;
    return *this;
  }

};