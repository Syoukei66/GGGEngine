#ifndef HAL_ENGINE_STRUCTURE_VERTEX_H_
#define HAL_ENGINE_STRUCTURE_VERTEX_H_

#include <algorithm>

#include "NativeType.h"
#include "EasingFunctionManager.h"
#include "Eigen\Core"

// =================================================================
// Vec2
// =================================================================
typedef Eigen::Vector2f TVec2f;
typedef Eigen::Vector2i TVec2i;

// =================================================================
// Size
// =================================================================
template <typename T>
union BaseTSize
{
  struct
  {
    T width, height;
  };
  T vec[2];

  BaseTSize()
    : width(0)
    , height(0)
  {}

  BaseTSize(T w, T h)
    : width(w)
    , height(h)
  {}
  bool IsZero() const
  {
    return this->width == 0 && this->height == 0;
  }
  //’P€+
  const BaseTSize operator + () const
  {
    return *this;
  }
  //’P€-
  const BaseTSize operator - () const
  {
    return BaseTSize(-this->width, -this->height);
  }
  //2€+
  const BaseTSize operator + (const BaseTSize& other) const
  {
    return BaseTSize(this->width + other.width, this->height + other.height);
  }
  BaseTSize& operator += (const BaseTSize& other)
  {
    this->width += other.width;
    this->height += other.height;
    return *this;
  }
  //2€-
  const BaseTSize operator - (const BaseTSize& other) const
  {
    return BaseTSize(this->width - other.width, this->height - other.height);
  }
  BaseTSize& operator -= (const BaseTSize& other)
  {
    this->width -= other.width;
    this->height -= other.height;
    return *this;
  }
  //2€*
  const BaseTSize operator * (const BaseTSize& other) const
  {
    return BaseTSize(this->width * other.width, this->height * other.height);
  }
  const BaseTSize operator * (T s) const
  {
    return BaseTSize(this->width * s, this->height * s);
  }
  BaseTSize& operator *= (const BaseTSize& other)
  {
    this->width *= other.width;
    this->height *= other.height;
    return *this;
  }
  BaseTSize& operator *= (const T& other)
  {
    this->width *= other;
    this->height *= other;
    return *this;
  } 
  BaseTSize& operator *= (T s)
  {
    this->width *= s;
    this->height *= s;
    return *this;
  }
  //2€/
  const BaseTSize operator / (const BaseTSize& other) const
  {
    return BaseTSize(this->width / other.width, this->height / other.height);
  }
  BaseTSize& operator /= (const BaseTSize& other)
  {
    this->width /= other.width;
    this->height /= other.height;
    return *this;
  }
  BaseTSize& operator /= (const T& other)
  {
    this->width /= other;
    this->height /= other;
    return *this;
  }
  //2€==
  bool operator == (const BaseTSize& other) const
  {
    return this->width == other.width && this->height == other.height;
  }
};

typedef BaseTSize<T_INT32> TSize;
typedef BaseTSize<T_FLOAT> TSizef;

// =================================================================
// Vec3
// =================================================================
template<typename T>
union BaseTVec3
{
  static const BaseTVec3<T> zero;
  static const BaseTVec3<T> one;
  static const BaseTVec3<T> forward;
  static const BaseTVec3<T> back;
  static const BaseTVec3<T> right;
  static const BaseTVec3<T> left;
  static const BaseTVec3<T> up;
  static const BaseTVec3<T> down;

  struct
  {
    T x, y, z;
  };
  T vec[3];

  BaseTVec3()
    : x(0)
    , y(0)
    , z(0)
  {}

  BaseTVec3(T x, T y, T z)
    : x(x)
    , y(y)
    , z(z)
  {}

  static BaseTVec3<T> EaseIn(EasingFunction::EasingFunction& easing_function, const BaseTVec3<T>& a, const BaseTVec3<T>& b, T_FLOAT t)
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
    return a + (b - a) * t;
  }

  static BaseTVec3<T> EaseOut(EasingFunction::EasingFunction& easing_function, const BaseTVec3<T>& a, const BaseTVec3<T>& b, T_FLOAT t)
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
    return a + (b - a) * t;
  }

  static BaseTVec3<T> EaseInOut(EasingFunction::EasingFunction& easing_function, const BaseTVec3<T>& a, const BaseTVec3<T>& b, T_FLOAT t)
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
    return a + (b - a) * t;
  }

  static BaseTVec3<T> Lerp(const BaseTVec3<T>& a, const BaseTVec3<T>& b, T_FLOAT t)
  {
    if (t <= 0.0f)
    {
      return a;
    }
    if (t >= 1.0f)
    {
      return b;
    }
    t = std::min(std::max(t, 0.0f), 1.0f);
    return a + (b - a) * t;
  }

  bool IsZero() const
  {
    return this->x == 0.0 && this->y == 0.0 && this->z == 0.0;
  }
  T Length() const
  {
    return (T)sqrt(LengthSquare());
  }
  T LengthSquare() const
  {
    return this->x * this->x + this->y * this->y + this->z * this->z;
  }
  BaseTVec3 Normalized() const
  {
    T length = Length();
    if (length == 0.0)
    {
      return BaseTVec3((T)0.0, (T)0.0, (T)0.0);
    }
    return *this / length;
  }

  static T_FLOAT InnerProduct(const BaseTVec3& a, const BaseTVec3& b)
  {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }

  static BaseTVec3 OuterProduct(const BaseTVec3& a, const BaseTVec3& b)
  {
    return BaseTVec3(
      a.y * b.z - b.y * a.z,
     -a.x * b.z + b.x * a.z,
      a.x * b.y - b.x * a.y
    );
  }

  //’P€+
  const BaseTVec3 operator + () const
  {
    return *this;
  }
  //’P€-
  const BaseTVec3 operator - () const
  {
    return BaseTVec3(-this->x, -this->y, -this->z);
  }
  //2€+
  const BaseTVec3 operator + (const BaseTVec3& other) const
  {
    return BaseTVec3(this->x + other.x, this->y + other.y, this->z + other.z);
  }
  BaseTVec3& operator += (const BaseTVec3& other)
  {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
  }
  //2€-
  const BaseTVec3 operator - (const BaseTVec3& other) const
  {
    return BaseTVec3(this->x - other.x, this->y - other.y, this->z - other.z);
  }
  BaseTVec3& operator -= (const BaseTVec3& other)
  {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
  }
  //2€*
  const BaseTVec3 operator * (T s) const
  {
    return BaseTVec3(this->x * s, this->y * s, this->z * s);
  }
  const BaseTVec3 operator * (const BaseTVec3<T>& vec) const
  {
    return BaseTVec3(this->x * vec.x, this->y * vec.y, this->z * vec.z);
  }
  BaseTVec3& operator *= (const BaseTVec3& other)
  {
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    return *this;
  }
  BaseTVec3& operator *= (const T& other)
  {
    this->x *= other;
    this->y *= other;
    this->z *= other;
    return *this;
  }
  //2€/
  const BaseTVec3 operator / (T s) const
  {
    return BaseTVec3(this->x / s, this->y / s, this->z / s);
  }
  BaseTVec3& operator /= (const BaseTVec3& other)
  {
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    return *this;
  }
  BaseTVec3& operator /= (const T& other)
  {
    this->x /= other;
    this->y /= other;
    this->z /= other;
    return *this;
  }
  //2€==
  bool operator == (const BaseTVec3& other) const
  {
    return this->x == other.x && this->y == other.y && this->z == other.z;
  }
};

template<typename T>
const BaseTVec3<T> BaseTVec3<T>::zero    = BaseTVec3<T>(0, 0, 0);
template<typename T>
const BaseTVec3<T> BaseTVec3<T>::one     = BaseTVec3<T>(1, 1, 1);
template<typename T>
const BaseTVec3<T> BaseTVec3<T>::forward = BaseTVec3<T>(0, 0, 1);
template<typename T>
const BaseTVec3<T> BaseTVec3<T>::back    = BaseTVec3<T>(0, 0, -1);
template<typename T>
const BaseTVec3<T> BaseTVec3<T>::right   = BaseTVec3<T>(1, 0, 0);
template<typename T>
const BaseTVec3<T> BaseTVec3<T>::left    = BaseTVec3<T>(-1, 0, 0);
template<typename T>
const BaseTVec3<T> BaseTVec3<T>::up      = BaseTVec3<T>(0, 1, 0);
template<typename T>
const BaseTVec3<T> BaseTVec3<T>::down    = BaseTVec3<T>(0, -1, 0);

typedef BaseTVec3<T_INT32> TVec3;
typedef BaseTVec3<T_FLOAT> TVec3f;

// =================================================================
// Vec4
// =================================================================
typedef Eigen::Vector4f TVec4f;
typedef Eigen::Vector4i TVec4i;

// =================================================================
// Area
// =================================================================
template <typename T>
struct BaseTArea
{
  BaseTArea(T x, T y, T w, T h)
    : x(x)
    , y(y)
    , size(w, h)
  {}
  BaseTArea()
    : x()
    , y()
    , size()
  {}

  T x, y;
  BaseTSize<T> size;
};

typedef BaseTArea<T_INT32> TArea;
typedef BaseTArea<T_FLOAT> TAreaf;

#endif//HAL_ENGINE_STRUCTURE_VERTEX_H_