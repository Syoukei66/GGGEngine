#pragma once

#include "Eigen\Core.h"
#include "Eigen\Geometry.h"

#include "NativeType.h"

#include "EasingFunction.h"

#include "Vector4.h"

template <typename T>
union TVec2
{
  // =================================================================
  // Constants
  // =================================================================
public:
  static const TVec2<T> zero;
  static const TVec2<T> one;
  static const TVec2<T> right;
  static const TVec2<T> left;
  static const TVec2<T> up;
  static const TVec2<T> down;

  // =================================================================
  // Data Members
  // =================================================================
public:
  struct
  {
    T x, y;
  };
  T vec[2];
  Eigen::Matrix<T, 2, 1> eigen;

  // =================================================================
  // Constructor
  // =================================================================
public:
  TVec2()
    : eigen(0, 0)
  {}

  TVec2(T x, T y)
    : eigen(x, y)
  {}

  TVec2(const Eigen::Matrix<T, 2, 1>& eigen)
    : eigen(eigen)
  {}

  // =================================================================
  // Copy Constructor / Assign operator
  // =================================================================
public:
  TVec2(const TVec2<T>& other)
    : eigen(other.eigen)
  {}

  inline TVec2<T>& operator=(const TVec2<T>& other)
  {
    this->eigen = other.eigen;
    return *this;
  }

  // =================================================================
  // Cast Operator
  // =================================================================
public:
  operator Eigen::Matrix<T, 2, 1>() const
  {
    return this->eigen;
  }
  operator Eigen::Matrix<T, 4, 1>() const
  {
    Eigen::Matrix<T, 4, 1> ret = this->eigen;
    ret[3] = 1.0f;
    return this->eigen;
  }

  // =================================================================
  // Static Methods
  // =================================================================
public:
  static TVec2<T> EaseIn(EasingFunction::EasingFunction& easing_function, const TVec2<T>& a, const TVec2<T>& b, T_FLOAT t)
  {
    if (t <= 0.0f)
    {
      return a;
    }
    if (t >= 1.0f)
    {
      return b;
    }
    t = easing_function.In(t);
    return TVec2<T>(a.eigen * (1.0f - t) + b.eigen * t);
  }

  static TVec2<T> EaseOut(EasingFunction::EasingFunction& easing_function, const TVec2<T>& a, const TVec2<T>& b, T_FLOAT t)
  {
    if (t <= 0.0f)
    {
      return a;
    }
    if (t >= 1.0f)
    {
      return b;
    }
    t = easing_function.Out(t);
    return TVec2<T>(a.eigen * (1.0f - t) + b.eigen * t);
  }

  static TVec2<T> EaseInOut(EasingFunction::EasingFunction& easing_function, const TVec2<T>& a, const TVec2<T>& b, T_FLOAT t)
  {
    if (t <= 0.0f)
    {
      return a;
    }
    if (t >= 1.0f)
    {
      return b;
    }
    t = easing_function.InOut(t);
    return TVec2<T>(a.eigen * (1.0f - t) + b.eigen * t);
  }

  static TVec2<T> Lerp(const TVec2<T>& a, const TVec2<T>& b, T_FLOAT t)
  {
    if (t <= 0.0f)
    {
      return a;
    }
    if (t >= 1.0f)
    {
      return b;
    }
    return TVec2<T>(a.eigen * (1.0f - t) + b.eigen * t);
  }

  // =================================================================
  // Operator
  // =================================================================
public:
  //+
  inline const TVec2<T> operator + () const
  {
    return *this;
  }
  //-
  inline const TVec2<T> operator - () const
  {
    return TVec2<T>(-this->eigen);
  }
  //２項+
  inline const TVec2<T> operator + (const TVec2<T>& other) const
  {
    return TVec2<T>(this->eigen + other.eigen);
  }
  inline TVec2<T>& operator += (const TVec2<T>& other)
  {
    this->eigen += other.eigen;
    return *this;
  }
  //２項-
  inline const TVec2<T> operator - (const TVec2<T>& other) const
  {
    return TVec2<T>(this->eigen - other.eigen);
  }
  inline TVec2<T>& operator -= (const TVec2<T>& other)
  {
    this->eigen -= other.eigen;
    return *this;
  }
  //２項*
  inline const TVec2<T> operator * (T s) const
  {
    return TVec2<T>(this->eigen * s);
  }
  inline TVec2<T>& operator *= (const TVec2<T>& other)
  {
    this->eigen *= other.eigen;
    return *this;
  }
  inline TVec2<T>& operator *= (const T& other)
  {
    this->eigen *= other;
    return *this;
  }
  //２項/
  inline const TVec2<T> operator / (T s) const
  {
    return TVec2<T>(this->eigen / s);
  }
  inline TVec2<T>& operator /= (const TVec2<T>& other)
  {
    this->eigen /= other.eigen;
    return *this;
  }
  inline TVec2<T>& operator /= (const T& other)
  {
    this->eigen /= other;
    return *this;
  }
  //２項==
  inline bool operator == (const TVec2<T>& other) const
  {
    return this->eigen == other.eigen;
  }

  // =================================================================
  // Methods
  // =================================================================
public:
  inline T Length() const
  {
    return this->eigen.norm();
  }
  inline T LengthSquare() const
  {
    return this->eigen.squaredNorm();
  }
  inline TVec2<T> Normalized() const
  {
    return TVec2<T>(this->eigen.normalized());
  }
  inline bool IsZero() const
  {
    return this->eigen.isZero();
  }
  //inline TVec4f ToVector4() const
  //{
  //  Eigen::Matrix<T, 4, 1> ret;
  //  ret[0] = this->eigen[0];
  //  ret[1] = this->eigen[1];
  //  ret[2] = 0.0f;
  //  ret[3] = 1.0f;
  //  return TVec4<T>(this->eigen);
  //}
};

// =================================================================
// Constants
// =================================================================
template<typename T>
const TVec2<T> TVec2<T>::zero = TVec2<T>(0, 0);
template<typename T>
const TVec2<T> TVec2<T>::one = TVec2<T>(1, 1);
template<typename T>
const TVec2<T> TVec2<T>::right = TVec2<T>(1, 0);
template<typename T>
const TVec2<T> TVec2<T>::left = TVec2<T>(-1, 0);
template<typename T>
const TVec2<T> TVec2<T>::up = TVec2<T>(0, 1);
template<typename T>
const TVec2<T> TVec2<T>::down = TVec2<T>(0, -1);

typedef TVec2<T_INT32> TVec2i;
typedef TVec2<T_FLOAT> TVec2f;

