#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

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

// =================================================================
// Constructor
// =================================================================
template<typename T>
GG_INLINE TVec4<T>::TVec4()
  : x(0)
  , y(0)
  , z(0)
  , w(0)
{}

template<typename T>
GG_INLINE TVec4<T>::TVec4(T x, T y, T z, T w)
  : x(x)
  , y(y)
  , z(z)
  , w(w)
{}

template<typename T>
GG_INLINE TVec4<T>::TVec4(const TVec2<T>& vec2, T_FLOAT z, T_FLOAT w)
  : x(vec2.x)
  , y(vec2.y)
  , z(z)
  , w(w)
{}

template<typename T>
GG_INLINE TVec4<T>::TVec4(const TVec3<T>& vec3, T_FLOAT w)
  : x(vec3.x)
  , y(vec3.y)
  , z(vec3.z)
  , w(w)
{}

template<typename T>
GG_INLINE TVec4<T>::TVec4(const TVec4<T>& other)
  : x(other.x)
  , y(other.y)
  , z(other.z)
  , w(other.w)
{}

// =================================================================
// Operator
// =================================================================
// ë„ì¸
template<typename T>
GG_INLINE TVec4<T>& TVec4<T>::operator=(const TVec4<T>& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  this->w = other.w;
  return *this;
}

// â¡éZ
template<typename T>
GG_INLINE const TVec4<T> TVec4<T>::operator+ () const
{
  return *this;
}

template<typename T>
GG_INLINE const TVec4<T> TVec4<T>::operator+ (const TVec4<T>& other) const
{
  return TVec4<T>(
    this->x + other.x,
    this->y + other.y,
    this->z + other.z,
    this->w + other.w
    );
}

template<typename T>
GG_INLINE TVec4<T>& TVec4<T>::operator+= (const TVec4<T>& other)
{
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  this->w += other.w;
  return *this;
}

// å∏éZ
template<typename T>
GG_INLINE const TVec4<T> TVec4<T>::operator- () const
{
  return TVec4<T>(
    -this->x,
    -this->y,
    -this->z,
    -this->w
    );
}

template<typename T>
GG_INLINE const TVec4<T> TVec4<T>::operator- (const TVec4<T>& other) const
{
  return TVec4<T>(
    this->x - other.x,
    this->y - other.y,
    this->z - other.z,
    this->w - other.w
    );
}

template<typename T>
GG_INLINE TVec4<T>& TVec4<T>::operator-= (const TVec4<T>& other)
{
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;
  this->w -= other.w;
  return *this;
}

// èÊéZ
template<typename T>
GG_INLINE const TVec4<T> TVec4<T>::operator* (T s) const
{
  return TVec4<T>(
    this->x * s,
    this->y * s,
    this->z * s,
    this->w * s
    );
}

template<typename T>
GG_INLINE TVec4<T>& TVec4<T>::operator*= (const TVec4<T>& other)
{
  this->x *= other.x;
  this->y *= other.y;
  this->z *= other.z;
  this->w *= other.w;
  return *this;
}

template<typename T>
GG_INLINE TVec4<T>& TVec4<T>::operator*= (const T& other)
{
  this->x *= other;
  this->y *= other;
  this->z *= other;
  this->w *= other;
  return *this;
}

// èúéZ
template<typename T>
GG_INLINE const TVec4<T> TVec4<T>::operator/ (T s) const
{
  return TVec4<T>(
    this->x / s,
    this->y / s,
    this->z / s,
    this->w / s
    );
}

template<typename T>
GG_INLINE TVec4<T>& TVec4<T>::operator/= (const TVec4<T>& other)
{
  this->x /= other.x;
  this->y /= other.y;
  this->z /= other.z;
  this->w /= other.w;
  return *this;
}

template<typename T>
GG_INLINE TVec4<T>& TVec4<T>::operator/= (const T& other)
{
  this->x /= other;
  this->y /= other;
  this->z /= other;
  this->w /= other;
  return *this;
}

// î‰är
template<typename T>
GG_INLINE bool TVec4<T>::operator== (const TVec4<T>& other) const
{
  return 
    this->x == other.x &&
    this->y == other.y &&
    this->z == other.z &&
    this->w == other.w
    ;
}

template<typename T>
GG_INLINE bool TVec4<T>::operator!= (const TVec4<T>& other) const
{
  return     
    this->x != other.x ||
    this->y != other.y ||
    this->z != other.z ||
    this->w != other.w
    ;
}

// =================================================================
// Methods
// =================================================================
template<typename T>
GG_INLINE T TVec4<T>::Length() const
{
  return sqrtf(this->LengthSquare());
}

template<typename T>
GG_INLINE T TVec4<T>::LengthSquare() const
{
  return 
    this->x * this->x +
    this->y * this->y +
    this->z * this->z +
    this->w * this->w
    ;
}

template<typename T>
GG_INLINE TVec4<T> TVec4<T>::Normalized() const
{
  const T length = this->Length();
  return TVec4<T>(
    this->x / length,
    this->y / length,
    this->z / length,
    this->w / length
    );
}

template<typename T>
GG_INLINE bool TVec4<T>::IsZero() const
{
  return this->x == 0 && this->y == 0 && this->z == 0 && this->w == 0;
}
