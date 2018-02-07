#ifndef HAL_ENGINE_STRUCTURE_VERTEX_H_
#define HAL_ENGINE_STRUCTURE_VERTEX_H_

#include <algorithm>

#include "NativeType.h"
#include "EasingFunctionManager.h"

// =================================================================
// Vec2
// =================================================================
template <typename T>
struct BaseTVec2
{
  T x, y;

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
  //単項+
  const BaseTVec2 operator + () const
  {
    return *this;
  }
  //単項-
  const BaseTVec2 operator - () const
  {
    return BaseTVec2(-this->x, -this->y);
  }
  //2項+
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
  //2項-
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
  //2項*
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
  //2項/
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
  //2項==
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
struct BaseTSize
{
  T width, height;

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
  //単項+
  const BaseTSize operator + () const
  {
    return *this;
  }
  //単項-
  const BaseTSize operator - () const
  {
    return BaseTSize(-this->width, -this->height);
  }
  //2項+
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
  //2項-
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
  //2項*
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
  //2項/
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
  //2項==
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
struct BaseTVec3
{
  T x, y, z;
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
    return a * (1.0f - t) + b * t;
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
    return a * (1.0f - t) + b * t;
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
    return a * (1.0f - t) + b * t;
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
    return a * (1.0f - t) + b * t;
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

  //単項+
  const BaseTVec3 operator + () const
  {
    return *this;
  }
  //単項-
  const BaseTVec3 operator - () const
  {
    return BaseTVec3(-this->x, -this->y, -this->z);
  }
  //2項+
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
  //2項-
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
  //2項*
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
  //2項/
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
  //2項==
  bool operator == (const BaseTVec3& other) const
  {
    return this->x == other.x && this->y == other.y && this->z == other.z;
  }
};

typedef BaseTVec3<T_INT32> TVec3;
typedef BaseTVec3<T_FLOAT> TVec3f;

// =================================================================
// Vec4
// =================================================================
template<typename T>
struct BaseTVec4
{
  T x, y, z, w;
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
  //単項+
  const BaseTVec4 operator + () const
  {
    return *this;
  }
  //単項-
  const BaseTVec4 operator - () const
  {
    return BaseTVec4(-this->x, -this->y, -this->z, -this->w);
  }
  //2項+
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
  //2項-
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
  //2項*
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
  //2項/
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
  //2項==
  bool operator == (const BaseTVec4& other) const
  {
    return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w;
  }
};

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