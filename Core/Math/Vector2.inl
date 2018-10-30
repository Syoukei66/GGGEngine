#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

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

// =================================================================
// Constructor
// =================================================================
template<typename T>
GG_INLINE TVec2<T>::TVec2()
  : x(0), y(0)
{}

template<typename T>
GG_INLINE TVec2<T>::TVec2(T x, T y)
  : x(x), y(y)
{}

template<typename T>
GG_INLINE TVec2<T>::TVec2(const TVec2<T>& other)
  : x(other.x), y(other.y)
{}

template<typename T>
GG_INLINE TVec2<T>::TVec2(const TVec3<T>& other)
  : x(other.x), y(other.y)
{}

template<typename T>
GG_INLINE TVec2<T>::TVec2(const TVec4<T>& other)
  : x(other.x), y(other.y)
{}

// =================================================================
// Operator
// =================================================================
// ë„ì¸
template<typename T>
GG_INLINE TVec2<T>& TVec2<T>::operator=(const TVec2<T>& other)
{
  this->x = other.x;
  this->y = other.y;
  return *this;
}

template<typename T>
GG_INLINE TVec2<T>& TVec2<T>::operator=(const TVec3<T>& other)
{
  this->x = other.x;
  this->y = other.y;
  return *this;
}

template<typename T>
GG_INLINE TVec2<T>& TVec2<T>::operator=(const TVec4<T>& other)
{
  this->x = other.x;
  this->y = other.y;
  return *this;
}

// â¡éZ
template<typename T>
GG_INLINE const TVec2<T> TVec2<T>::operator+ () const
{
  return *this;
}

template<typename T>
GG_INLINE const TVec2<T> TVec2<T>::operator+ (const TVec2<T>& other) const
{
  return TVec2<T>(this->x + other.x, this->y + other.y);
}

template<typename T>
GG_INLINE TVec2<T>& TVec2<T>::operator+= (const TVec2<T>& other)
{
  this->x += other.x;
  this->y += other.y;
  return *this;
}

// å∏éZ
template<typename T>
GG_INLINE const TVec2<T> TVec2<T>::operator- () const
{
  return TVec2<T>(-this->x, -this->y);
}

template<typename T>
GG_INLINE const TVec2<T> TVec2<T>::operator- (const TVec2<T>& other) const
{
  return TVec2<T>(this->x - other.x, this->y - other.y);
}

template<typename T>
GG_INLINE TVec2<T>& TVec2<T>::operator-= (const TVec2<T>& other)
{
  this->x -= other.x;
  this->y -= other.y;
  return *this;
}

// èÊéZ
template<typename T>
GG_INLINE const TVec2<T> TVec2<T>::operator* (T s) const
{
  return TVec2<T>(this->x * s, this->y * s);
}

template<typename T>
GG_INLINE const TVec2<T> TVec2<T>::operator* (const TVec2<T>& other) const
{
  return TVec2<T>(this->x * other.x, this->y * other.y);
}

template<typename T>
GG_INLINE TVec2<T>& TVec2<T>::operator*= (T s)
{
  this->x *= s;
  this->y *= s;
  return *this;
}

template<typename T>
GG_INLINE TVec2<T>& TVec2<T>::operator*= (const TVec2<T>& other)
{
  this->x *= other.x;
  this->y *= other.y;
  return *this;
}

// èúéZ
template<typename T>
GG_INLINE const TVec2<T> TVec2<T>::operator/ (T s) const
{
  return TVec2<T>(this->x / s, this->y / s);
}

template<typename T>
GG_INLINE const TVec2<T> TVec2<T>::operator/ (const TVec2<T>& other) const
{
  return TVec2<T>(this->x / other.x, this->y / other.y);
}

template<typename T>
GG_INLINE TVec2<T>& TVec2<T>::operator/= (T s)
{
  this->x /= s;
  this->y /= s;
  return *this;
}

template<typename T>
GG_INLINE TVec2<T>& TVec2<T>::operator/= (const TVec2<T>& other)
{
  this->x /= other.x;
  this->y /= other.y;
  return *this;
}

// î‰är
template<typename T>
GG_INLINE bool TVec2<T>::operator== (const TVec2<T>& other) const
{
  return this->x == other.x && this->y == other.y;
}

template<typename T>
GG_INLINE bool TVec2<T>::operator!= (const TVec2<T>& other) const
{
  return this->x != other.x || this->y != other.y;
}

// =================================================================
// Methods
// =================================================================
template<typename T>
GG_INLINE T TVec2<T>::Length() const
{
  return sqrtf(this->LengthSquare());
}

template<typename T>
GG_INLINE T TVec2<T>::LengthSquare() const
{
  return this->x * this->x + this->y * this->y;
}

template<typename T>
GG_INLINE TVec2<T> TVec2<T>::Normalized() const
{
  const T length = this->Length();
  return TVec2<T>(this->x / length, this->y / length);
}

template<typename T>
GG_INLINE bool TVec2<T>::IsZero() const
{
  return this->x == 0 && this->y == 0;
}
