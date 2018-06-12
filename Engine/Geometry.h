#ifndef HAL_ENGINE_STRUCTURE_VERTEX_H_
#define HAL_ENGINE_STRUCTURE_VERTEX_H_

#include <algorithm>

#include "NativeType.h"
#include "Vector2.h"

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
  const BaseTSize operator * (const TVec2<T>& vec) const
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
  TVec2<T> pos;
  BaseTSize<T> size;
};

typedef BaseTArea<T_INT32> TArea;
typedef BaseTArea<T_FLOAT> TAreaf;

#endif//HAL_ENGINE_STRUCTURE_VERTEX_H_