#pragma once

#include <Eigen/Core.h>
#include <Eigen/Geometry.h>

#include "NativeType.h"

#include "EasingFunction.h"

#include "Vector2.h"

template<typename T>
union TVec3
{
  // =================================================================
  // Constants
  // =================================================================
public:
  static const TVec3<T> zero;
  static const TVec3<T> one;
  static const TVec3<T> forward;
  static const TVec3<T> back;
  static const TVec3<T> right;
  static const TVec3<T> left;
  static const TVec3<T> up;
  static const TVec3<T> down;

  // =================================================================
  // Data Members
  // =================================================================
public:
  struct
  {
    T x, y, z;
  };
  T data[3];
  Eigen::Matrix<T, 3, 1> eigen;

  // =================================================================
  // Constructor
  // =================================================================
public:
  TVec3()
    : eigen(0, 0, 0)
  {}

  TVec3(T x, T y, T z)
    : eigen(x, y, z)
  {}

  TVec3(const Eigen::Matrix<T, 3, 1>& eigen)
    : eigen(eigen)
  {}

  TVec3(const TVec2<T>& vec2, T_FLOAT z)
    : eigen(vec2.x, vec2.y, z)
  {}

  // =================================================================
  // Copy Constructor / Assign operator
  // =================================================================
public:
  TVec3(const TVec3<T>& other)
    : eigen(other.eigen)
  {}

  inline TVec3<T>& operator = (const TVec3<T>& other)
  {
    this->eigen = other.eigen;
    return *this;
  }

  // =================================================================
  // Cast Operator
  // =================================================================
public:
  operator Eigen::Matrix<T, 3, 1>() const
  {
    return this->eigen;
  }

  // =================================================================
  // Static Methods
  // =================================================================
public:
  static TVec3<T> EaseIn(EasingFunction::EasingFunction& easing_function, const TVec3<T>& a, const TVec3<T>& b, T_FLOAT t)
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
    return TVec3<T>(a.eigen + (b.eigen - a.eigen) * t);
  }

  static TVec3<T> EaseOut(EasingFunction::EasingFunction& easing_function, const TVec3<T>& a, const TVec3<T>& b, T_FLOAT t)
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
    return TVec3<T>(a.eigen + (b.eigen - a.eigen) * t);
  }

  static TVec3<T> EaseInOut(EasingFunction::EasingFunction& easing_function, const TVec3<T>& a, const TVec3<T>& b, T_FLOAT t)
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
    return TVec3<T>(a.eigen + (b.eigen - a.eigen) * t);
  }

  static TVec3<T> Lerp(const TVec3<T>& a, const TVec3<T>& b, T_FLOAT t)
  {
    if (t <= 0.0f)
    {
      return a;
    }
    if (t >= 1.0f)
    {
      return b;
    }
    return TVec3<T>(a.eigen + (b.eigen - a.eigen) * t);
  }

  static inline T_FLOAT InnerProduct(const TVec3<T>& a, const TVec3<T>& b)
  {
    return a.eigen.dot(b.eigen);
  }

  static inline TVec3<T> OuterProduct(const TVec3<T>& a, const TVec3<T>& b)
  {
    return TVec3<T>(a.eigen.cross(b.eigen));
  }

  // =================================================================
  // Operator
  // =================================================================
public:
  //+
  inline const TVec3<T> operator + () const
  {
    return *this;
  }
  //-
  inline const TVec3<T> operator - () const
  {
    return TVec3<T>(-this->eigen);
  }
  //ÇQçÄ+
  inline const TVec3<T> operator + (const TVec3<T>& other) const
  {
    return TVec3<T>(this->eigen + other.eigen);
  }
  inline TVec3<T>& operator += (const TVec3<T>& other)
  {
    this->eigen += other.eigen;
    return *this;
  }
  //ÇQçÄ-
  inline const TVec3<T> operator - (const TVec3<T>& other) const
  {
    return TVec3<T>(this->eigen - other.eigen);
  }
  inline TVec3<T>& operator -= (const TVec3<T>& other)
  {
    this->eigen -= other.eigen;
    return *this;
  }
  //ÇQçÄ*
  inline const TVec3<T> operator * (T s) const
  {
    return TVec3<T>(this->eigen * s);
  }
  inline const TVec3<T> operator * (const TVec3<T>& data) const
  {
    return TVec3<T>(this->eigen * data.eigen);
  }
  inline TVec3<T>& operator *= (const TVec3<T>& other)
  {
    this->eigen *= other.eigen;
    return *this;
  }
  inline TVec3<T>& operator *= (const T& other)
  {
    this->eigen *= other;
    return *this;
  }
  //ÇQçÄ/
  inline const TVec3<T> operator / (T s) const
  {
    return TVec3<T>(this->eigen / s);
  }
  inline TVec3<T>& operator /= (const TVec3<T>& other)
  {
    this->eigen /= other.eigen;
    return *this;
  }
  inline TVec3<T>& operator /= (const T& other)
  {
    this->eigen /= other;
    return *this;
  }
  //ÇQçÄ==
  inline bool operator == (const TVec3<T>& other) const
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
   inline TVec3<T> Normalized() const
   {
     return TVec3<T>(this->eigen.normalized());
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
   //  ret[2] = this->eigen[2];
   //  ret[3] = 1.0f;
   //  return TVec4<T>(this->eigen);
   //}
};

// =================================================================
// Constants
// =================================================================
template<typename T>
const TVec3<T> TVec3<T>::zero = TVec3<T>(0, 0, 0);
template<typename T>
const TVec3<T> TVec3<T>::one = TVec3<T>(1, 1, 1);
template<typename T>
const TVec3<T> TVec3<T>::forward = TVec3<T>(0, 0, 1);
template<typename T>
const TVec3<T> TVec3<T>::back = TVec3<T>(0, 0, -1);
template<typename T>
const TVec3<T> TVec3<T>::right = TVec3<T>(1, 0, 0);
template<typename T>
const TVec3<T> TVec3<T>::left = TVec3<T>(-1, 0, 0);
template<typename T>
const TVec3<T> TVec3<T>::up = TVec3<T>(0, 1, 0);
template<typename T>
const TVec3<T> TVec3<T>::down = TVec3<T>(0, -1, 0);

typedef TVec3<T_INT32> TVec3i;
typedef TVec3<T_FLOAT> TVec3f;
