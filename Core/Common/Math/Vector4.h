#pragma once

#include <Eigen/Core.h>
#include <Eigen/Geometry.h>

#include <Core/Common/Types.h>
#include <Core/Macro/ObjectMacro.h>

template<typename T>
struct TVec4
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(TVec4<T>)
  {
    archive(x);
    archive(y);
    archive(z);
    archive(w);
  }

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
  union
  {
    struct
    {
      T x, y, z, w;
    };
    T data[4];
    Eigen::Matrix<T, 4, 1> eigen;
  };

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

  TVec4(const TVec3<T>& vec3, T_FLOAT w)
    : eigen(vec3.x, vec3.y, vec3.z, w)
  {}

  // =================================================================
  // Copy Constructor / Assign operator
  // =================================================================
public:
  TVec4(const TVec4<T>& other)
    : eigen(other.eigen)
  {}

  GG_INLINE TVec4<T>& operator=(const TVec4<T>& other)
  {
    this->eigen = other.eigen;
    return *this;
  }

  // =================================================================
  // Cast Operator
  // =================================================================
public:
  GG_INLINE operator Eigen::Matrix<T, 4, 1>() const
  {
    return this->eigen;
  }

  // =================================================================
  // Static Methods
  // =================================================================
public:
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

  static GG_INLINE T_FLOAT Dot(const TVec4<T>& a, const TVec4<T>& b)
  {
    return a.eigen.dot(b.eigen);
  }

  static GG_INLINE TVec4<T> Cross(const TVec4<T>& a, const TVec4<T>& b)
  {
    return TVec4<T>(a.eigen.cross(b.eigen));
  }

  // =================================================================
  // Operator
  // =================================================================
public:
  //+
  GG_INLINE const TVec4<T> operator + () const
  {
    return *this;
  }
  //-
  GG_INLINE const TVec4<T> operator - () const
  {
    return TVec4<T>(-this->eigen);
  }
  //ÇQçÄ+
  GG_INLINE const TVec4<T> operator + (const TVec4<T>& other) const
  {
    return TVec4<T>(this->eigen + other.eigen);
  }
  GG_INLINE TVec4<T>& operator += (const TVec4<T>& other)
  {
    this->eigen += other.eigen;
    return *this;
  }
  //ÇQçÄ-
  GG_INLINE const TVec4<T> operator - (const TVec4<T>& other) const
  {
    return TVec4<T>(this->eigen - other.eigen);
  }
  GG_INLINE TVec4<T>& operator -= (const TVec4<T>& other)
  {
    this->eigen -= other.eigen;
    return *this;
  }
  //ÇQçÄ*
  GG_INLINE const TVec4<T> operator * (T s) const
  {
    return TVec4<T>(this->eigen * s);
  }
  GG_INLINE TVec4<T>& operator *= (const TVec4<T>& other)
  {
    this->eigen *= other.eigen;
    return *this;
  }
  GG_INLINE TVec4<T>& operator *= (const T& other)
  {
    this->eigen *= other;
    return *this;
  }
  //ÇQçÄ/
  GG_INLINE const TVec4<T> operator / (T s) const
  {
    return TVec4<T>(this->eigen / s);
  }
  GG_INLINE TVec4<T>& operator /= (const TVec4<T>& other)
  {
    this->eigen /= other.eigen;
    return *this;
  }
  GG_INLINE TVec4<T>& operator /= (const T& other)
  {
    this->eigen /= other;
    return *this;
  }
  //ÇQçÄ==
  GG_INLINE bool operator == (const TVec4<T>& other) const
  {
    return this->eigen == other.eigen;
  }

  // =================================================================
  // Methods
  // =================================================================
public:
  GG_INLINE T Length() const
  {
    return this->eigen.norm();
  }
  GG_INLINE T LengthSquare() const
  {
    return this->eigen.squaredNorm();
  }
  GG_INLINE TVec4<T> Normalized() const
  {
    return TVec4<T>(this->eigen.normalized());
  }
  GG_INLINE bool IsZero() const
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