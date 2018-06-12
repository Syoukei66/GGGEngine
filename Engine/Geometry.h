#ifndef HAL_ENGINE_STRUCTURE_VERTEX_H_
#define HAL_ENGINE_STRUCTURE_VERTEX_H_

#include <algorithm>

#include "NativeType.h"
#include "EasingFunctionManager.h"
#include "Eigen\Core"
#include "Eigen\Geometry"

// =================================================================
// Vec2
// =================================================================
template <typename T>
union BaseTVec2
{
  struct
  {
    T x, y;
  };
  T vec[2];

  BaseTVec2()
    : x(0)
    , y(0)
  {}

  BaseTVec2(T x, T y)
    : x(x)
    , y(y)
  {}

  static BaseTVec2<T> EaseIn(EasingFunction::EasingFunction& easing_function, const BaseTVec2<T>& a, const BaseTVec2<T>& b, T_FLOAT t)
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
    return a * (1.0f - t) + b * t;
  }

  static BaseTVec2<T> EaseOut(EasingFunction::EasingFunction& easing_function, const BaseTVec2<T>& a, const BaseTVec2<T>& b, T_FLOAT t)
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
    return a * (1.0f - t) + b * t;
  }

  static BaseTVec2<T> EaseInOut(EasingFunction::EasingFunction& easing_function, const BaseTVec2<T>& a, const BaseTVec2<T>& b, T_FLOAT t)
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
    return a * (1.0f - t) + b * t;
  }

  static BaseTVec2<T> Lerp(const BaseTVec2<T>& a, const BaseTVec2<T>& b, T_FLOAT t)
  {
    if (t <= 0.0f)
    {
      return a;
    }
    if (t >= 1.0f)
    {
      return b;
    }
    return a * (1.0f - t) + b * t;
  }

  T Length() const
  {
    return sqrt(LengthSquare());
  }
  T LengthSquare() const
  {
    return this->x * this->x + this->y * this->y;
  }
  BaseTVec2 Normalized() const
  {
    T length = Length();
    if (length == 0.0)
    {
      return BaseTVec2((T)0.0, (T)0.0);
    }
    return *this / length;
  }
  bool IsZero() const
  {
    return this->x == 0.0 && this->y == 0.0;
  }
  //’P€+
  const BaseTVec2 operator + () const
  {
    return *this;
  }
  //’P€-
  const BaseTVec2 operator - () const
  {
    return BaseTVec2(-this->x, -this->y);
  }
  //2€+
  const BaseTVec2 operator + (const BaseTVec2& other) const
  {
    return BaseTVec2(this->x + other.x, this->y + other.y);
  }
  BaseTVec2& operator += (const BaseTVec2& other)
  {
    this->x += other.x;
    this->y += other.y;
    return *this;
  }
  //2€-
  const BaseTVec2 operator - (const BaseTVec2& other) const
  {
    return BaseTVec2(this->x - other.x, this->y - other.y);
  }
  BaseTVec2& operator -= (const BaseTVec2& other)
  {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
  }
  //2€*
  const BaseTVec2 operator * (T s) const
  {
    return BaseTVec2(this->x * s, this->y * s);
  }
  BaseTVec2& operator *= (const BaseTVec2& other)
  {
    this->x *= other.x;
    this->y *= other.y;
    return *this;
  }
  BaseTVec2& operator *= (const T& other)
  {
    this->x *= other;
    this->y *= other;
    return *this;
  }
  //2€/
  const BaseTVec2 operator / (T s) const
  {
    return BaseTVec2(this->x / s, this->y / s);
  }
  BaseTVec2& operator /= (const BaseTVec2& other)
  {
    this->x /= other.x;
    this->y /= other.y;
    return *this;
  }
  BaseTVec2& operator /= (const T& other)
  {
    this->x /= other;
    this->y /= other;
    return *this;
  }
  //2€==
  bool operator == (const BaseTVec2& other) const
  {
    return this->x == other.x && this->y == other.y;
  }
};

typedef BaseTVec2<T_INT32> TVec2;
typedef BaseTVec2<T_FLOAT> TVec2f;


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
  const BaseTSize operator * (const BaseTVec2<T>& vec) const
  {
    return BaseTSize(this->width * vec.x, this->height * vec.y);
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
  Eigen::Matrix<T, 3, 1> eigen;

  BaseTVec3()
    : eigen(0, 0, 0)
  {}

  BaseTVec3(T x, T y, T z)
    : eigen(x, y, z)
  {}

  BaseTVec3(const Eigen::Matrix<T, 3, 1>& eigen)
    : eigen(eigen)
  {}

  BaseTVec3(const BaseTVec3<T>& other)
    : eigen(other.eigen)
  {}

  BaseTVec3<T>& operator = (const BaseTVec3<T>& other)
  {
    this->eigen = other.eigen;
    return *this;
  }

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
    return BaseTVec3<T>(a.eigen + (b.eigen - a.eigen) * t);
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
    return BaseTVec3<T>(a.eigen + (b.eigen - a.eigen) * t);
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
    return BaseTVec3<T>(a.eigen + (b.eigen - a.eigen) * t);
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
    return BaseTVec3<T>(a.eigen + (b.eigen - a.eigen) * t);
  }

  bool IsZero() const
  {
    return this->x == 0.0 && this->y == 0.0 && this->z == 0.0;
  }
  T Length() const
  {
    return this->eigen.norm();
  }
  T LengthSquare() const
  {
    return this->eigen.squaredNorm();
  }
  BaseTVec3<T> Normalized() const
  {
    return BaseTVec3<T>(this->eigen.normalized());
  }

  static T_FLOAT InnerProduct(const BaseTVec3<T>& a, const BaseTVec3<T>& b)
  {
    return a.eigen.dot(b.eigen);
  }

  static BaseTVec3<T> OuterProduct(const BaseTVec3<T>& a, const BaseTVec3<T>& b)
  {
    return BaseTVec3<T>(a.eigen.cross(b.eigen));
  }

  //’P€+
  const BaseTVec3<T> operator + () const
  {
    return *this;
  }
  //’P€-
  const BaseTVec3<T> operator - () const
  {
    return BaseTVec3<T>(-this->eigen);
  }
  //2€+
  const BaseTVec3<T> operator + (const BaseTVec3<T>& other) const
  {
    return BaseTVec3<T>(this->eigen + other.eigen);
  }
  BaseTVec3<T>& operator += (const BaseTVec3<T>& other)
  {
    this->eigen += other.eigen;
    return *this;
  }
  //2€-
  const BaseTVec3<T> operator - (const BaseTVec3<T>& other) const
  {
    return BaseTVec3<T>(this->eigen - other.eigen);
  }
  BaseTVec3<T>& operator -= (const BaseTVec3<T>& other)
  {
    this->eigen -= other.eigen;
    return *this;
  }
  //2€*
  const BaseTVec3<T> operator * (T s) const
  {
    return BaseTVec3<T>(this->eigen * s);
  }
  const BaseTVec3<T> operator * (const BaseTVec3<T>& vec) const
  {
    return BaseTVec3<T>(this->eigen * vec.eigen);
  }
  BaseTVec3<T>& operator *= (const BaseTVec3<T>& other)
  {
    this->eigen *= other.eigen;
    return *this;
  }
  BaseTVec3<T>& operator *= (const T& other)
  {
    this->eigen *= other;
    return *this;
  }
  //2€/
  const BaseTVec3<T> operator / (T s) const
  {
    return BaseTVec3<T>(this->eigen / s);
  }
  BaseTVec3<T>& operator /= (const BaseTVec3<T>& other)
  {
    this->eigen /= other.eigen;
    return *this;
  }
  BaseTVec3<T>& operator /= (const T& other)
  {
    this->eigen /= other.eigen;
    return *this;
  }
  //2€==
  bool operator == (const BaseTVec3<T>& other) const
  {
    return this->eigen == other.eigen;
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
template<typename T>
union BaseTVec4
{
  static const BaseTVec4<T> zero;
  static const BaseTVec4<T> one;
  static const BaseTVec4<T> forward;
  static const BaseTVec4<T> back;
  static const BaseTVec4<T> right;
  static const BaseTVec4<T> left;
  static const BaseTVec4<T> up;
  static const BaseTVec4<T> down;

  struct
  {
    T x, y, z, w;
  };
  T vec[4];

  BaseTVec4()
    : x(0)
    , y(0)
    , z(0)
    , w(0)
  {}

  BaseTVec4(T x, T y, T z, T w)
    : x(x)
    , y(y)
    , z(z)
    , w(w)
  {}

  bool IsZero() const
  {
    return this->x == 0.0 && this->y == 0.0 && this->z == 0.0 && this->w == 0.0;
  }
  //’P€+
  const BaseTVec4 operator + () const
  {
    return *this;
  }
  //’P€-
  const BaseTVec4 operator - () const
  {
    return BaseTVec4(-this->x, -this->y, -this->z, -this->w);
  }
  //2€+
  const BaseTVec4 operator + (const BaseTVec4& other) const
  {
    return BaseTVec4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
  }
  BaseTVec4& operator += (const BaseTVec4& other)
  {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;
    return *this;
  }
  //2€-
  const BaseTVec4 operator - (const BaseTVec4& other) const
  {
    return BaseTVec4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
  }
  BaseTVec4& operator -= (const BaseTVec4& other)
  {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    this->w -= other.w;
    return *this;
  }
  //2€*
  const BaseTVec4 operator * (T s) const
  {
    return BaseTVec4(this->x * s, this->y * s, this->z * s, this->w * s);
  }
  BaseTVec4& operator *= (const BaseTVec4& other)
  {
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    this->w *= other.w;
    return *this;
  }
  BaseTVec4& operator *= (const T& other)
  {
    this->x *= other;
    this->y *= other;
    this->z *= other;
    this->w *= other;
    return *this;
  }
  //2€/
  const BaseTVec4 operator / (T s) const
  {
    return BaseTVec4(this->x / s, this->y / s, this->z / s, this->w / s);
  }
  BaseTVec4& operator /= (const BaseTVec4& other)
  {
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    this->w /= other.w;
    return *this;
  }
  BaseTVec4& operator /= (const T& other)
  {
    this->x /= other;
    this->y /= other;
    this->z /= other;
    this->w /= other;
    return *this;
  }
  //2€==
  bool operator == (const BaseTVec4& other) const
  {
    return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w;
  }
};

template<typename T>
const BaseTVec4<T> BaseTVec4<T>::zero =    BaseTVec4<T>(0, 0, 0, 0);
template<typename T>
const BaseTVec4<T> BaseTVec4<T>::one =     BaseTVec4<T>(1, 1, 1, 1);
template<typename T>
const BaseTVec4<T> BaseTVec4<T>::forward = BaseTVec4<T>(0, 0, 1, 0);
template<typename T>
const BaseTVec4<T> BaseTVec4<T>::back =    BaseTVec4<T>(0, 0, -1, 0);
template<typename T>
const BaseTVec4<T> BaseTVec4<T>::right =   BaseTVec4<T>(1, 0, 0, 0);
template<typename T>
const BaseTVec4<T> BaseTVec4<T>::left =    BaseTVec4<T>(-1, 0, 0, 0);
template<typename T>
const BaseTVec4<T> BaseTVec4<T>::up =      BaseTVec4<T>(0, 1, 0, 0);
template<typename T>
const BaseTVec4<T> BaseTVec4<T>::down =    BaseTVec4<T>(0, -1, 0, 0);

typedef BaseTVec4<T_INT32> TVec4;
typedef BaseTVec4<T_FLOAT> TVec4f;

// =================================================================
// Area
// =================================================================
template <typename T>
struct BaseTArea
{
  BaseTArea(T x, T y, T w, T h)
    : pos(x, y)
    , size(w, h)
  {}
  BaseTArea()
    : pos()
    , size()
  {}
  BaseTVec2<T> pos;
  BaseTSize<T> size;
};

typedef BaseTArea<T_INT32> TArea;
typedef BaseTArea<T_FLOAT> TAreaf;

#endif//HAL_ENGINE_STRUCTURE_VERTEX_H_