#pragma once

#include "Eigen\Core"
#include "Eigen\Geometry"

#include "NativeType.h"

#include "EasingFunction.h"

template<typename T>
union TVec4
{
  // =================================================================
  // Constants
  // =================================================================
public:
  static const TVec4<T> zero;
  static const TVec4<T> one;
  static const TVec4<T> forward;
  static const TVec4<T> back;
  static const TVec4<T> right;
  static const TVec4<T> left;
  static const TVec4<T> up;
  static const TVec4<T> down;

  // =================================================================
  // Data Members
  // =================================================================
public:
  struct
  {
    T x, y, z, w;
  };
  T vec[4];
  Eigen::Matrix<T, 4, 1> eigen;

  // =================================================================
  // Constructor
  // =================================================================
public:
  TVec4()
    : eigen(0, 0, 0, 0)
  {}

  TVec4(T x, T y, T z, T w)
    : eigen(x, y, z, w)
  {}

  TVec4(const Eigen::Matrix<T, 4, 1>& eigen)
    : eigen(eigen)
  {}

  // =================================================================
  // Copy Constructor / Assign operator
  // =================================================================
public:
  TVec4(const TVec4<T>& other)
    : eigen(other.eigen)
  {}

  TVec4<T>& operator=(const TVec4<T>& other)
  {
    this->eigen = other.eigen;
    return *this;
  }

  // =================================================================
  // Cast Operator
  // =================================================================
public:
  inline operator Eigen::Matrix<T, 4, 1>() const
  {
    return this->eigen;
  }

  // =================================================================
  // Static Methods
  // =================================================================
public:
  static TVec4<T> EaseIn(EasingFunction::EasingFunction& easing_function, const TVec4<T>& a, const TVec4<T>& b, T_FLOAT t)
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
    return TVec4<T>(a.eigen + (b.eigen - a.eigen) * t);
  }

  static TVec4<T> EaseOut(EasingFunction::EasingFunction& easing_function, const TVec4<T>& a, const TVec4<T>& b, T_FLOAT t)
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
    return TVec4<T>(a.eigen + (b.eigen - a.eigen) * t);
  }

  static TVec4<T> EaseInOut(EasingFunction::EasingFunction& easing_function, const TVec4<T>& a, const TVec4<T>& b, T_FLOAT t)
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
    return TVec4<T>(a.eigen + (b.eigen - a.eigen) * t);
  }

  static TVec4<T> Lerp(const TVec4<T>& a, const TVec4<T>& b, T_FLOAT t)
  {
    if (t <= 0.0f)
    {
      return a;
    }
    if (t >= 1.0f)
    {
      return b;
    }
    return TVec4<T>(a.eigen + (b.eigen - a.eigen) * t);
  }

  static inline T_FLOAT InnerProduct(const TVec4<T>& a, const TVec4<T>& b)
  {
    return a.eigen.dot(b.eigen);
  }

  static inline TVec4<T> OuterProduct(const TVec4<T>& a, const TVec4<T>& b)
  {
    return TVec4<T>(a.eigen.cross(b.eigen));
  }

  // =================================================================
  // Operator
  // =================================================================
public:
  //+
  inline const TVec4<T> operator + () const
  {
    return *this;
  }
  //-
  inline const TVec4<T> operator - () const
  {
    return TVec4<T>(-this->eigen);
  }
  //ÇQçÄ+
  inline const TVec4<T> operator + (const TVec4<T>& other) const
  {
    return TVec4<T>(this->eigen + other.eigen);
  }
  inline TVec4<T>& operator += (const TVec4<T>& other)
  {
    this->eigen += other.eigen;
    return *this;
  }
  //ÇQçÄ-
  inline const TVec4<T> operator - (const TVec4<T>& other) const
  {
    return TVec4<T>(this->eigen - other.eigen);
  }
  inline TVec4<T>& operator -= (const TVec4<T>& other)
  {
    this->eigen -= other.eigen;
    return *this;
  }
  //ÇQçÄ*
  inline const TVec4<T> operator * (T s) const
  {
    return TVec4<T>(this->eigen * s);
  }
  inline TVec4<T>& operator *= (const TVec4<T>& other)
  {
    this->eigen *= other.eigen;
    return *this;
  }
  inline TVec4<T>& operator *= (const T& other)
  {
    this->eigen *= other;
    return *this;
  }
  //ÇQçÄ/
  inline const TVec4<T> operator / (T s) const
  {
    return TVec4<T>(this->eigen / s);
  }
  inline TVec4<T>& operator /= (const TVec4<T>& other)
  {
    this->eigen /= other.eigen;
    return *this;
  }
  inline TVec4<T>& operator /= (const T& other)
  {
    this->eigen /= other;
    return *this;
  }
  //ÇQçÄ==
  inline bool operator == (const TVec4<T>& other) const
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
  inline TVec4<T> Normalized() const
  {
    return TVec4<T>(this->eigen.normalized());
  }
  inline bool IsZero() const
  {
    return this->eigen.isZero();
  }
};

// =================================================================
// Constants
// =================================================================
template<typename T>
const TVec4<T> TVec4<T>::zero = TVec4<T>(0, 0, 0, 0);
template<typename T>
const TVec4<T> TVec4<T>::one = TVec4<T>(1, 1, 1, 1);
template<typename T>
const TVec4<T> TVec4<T>::forward = TVec4<T>(0, 0, 1, 0);
template<typename T>
const TVec4<T> TVec4<T>::back = TVec4<T>(0, 0, -1, 0);
template<typename T>
const TVec4<T> TVec4<T>::right = TVec4<T>(1, 0, 0, 0);
template<typename T>
const TVec4<T> TVec4<T>::left = TVec4<T>(-1, 0, 0, 0);
template<typename T>
const TVec4<T> TVec4<T>::up = TVec4<T>(0, 1, 0, 0);
template<typename T>
const TVec4<T> TVec4<T>::down = TVec4<T>(0, -1, 0, 0);

typedef TVec4<T_INT32> TVec4i;
typedef TVec4<T_FLOAT> TVec4f;