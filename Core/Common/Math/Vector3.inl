#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

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

// =================================================================
// Constructor
// =================================================================
template<typename T>
GG_INLINE TVec3<T>::TVec3()
  : x(0), y(0), z(0)
{}

template<typename T>
GG_INLINE TVec3<T>::TVec3(T x, T y, T z)
  : x(x), y(y), z(z)
{}

template<typename T>
GG_INLINE TVec3<T>::TVec3(const TVec2<T>& other, T_FLOAT z)
  : x(other.x), y(other.y), z(z)
{}

template<typename T>
GG_INLINE TVec3<T>::TVec3(const TVec3<T>& other)
  : x(other.x), y(other.y), z(other.z)
{}

template<typename T>
GG_INLINE TVec3<T>::TVec3(const TVec4<T>& other)
  : x(other.x), y(other.y), z(other.z)
{}

// =================================================================
// Static Methods
// =================================================================
template<typename T>
GG_INLINE T TVec3<T>::Dot(const TVec3<T>& a, const TVec3<T>& b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<typename T>
GG_INLINE TVec3<T> TVec3<T>::Cross(const TVec3<T>& a, const TVec3<T>& b)
{
  return TVec3<T>(
    a.y * b.z - b.y * a.z,
    -a.x * b.z + b.x * a.z,
    a.x * b.y - b.x * a.y
    );
}

// =================================================================
// Operator
// =================================================================
// ë„ì¸
template<typename T>
GG_INLINE TVec3<T>& TVec3<T>::operator= (const TVec3<T>& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  return *this;
}

template<typename T>
GG_INLINE TVec3<T>& TVec3<T>::operator= (const TVec4<T>& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  return *this;
}

// â¡éZ
template<typename T>
GG_INLINE const TVec3<T> TVec3<T>::operator+ () const
{
  return *this;
}

template<typename T>
GG_INLINE const TVec3<T> TVec3<T>::operator+ (const TVec3<T>& other) const
{
  return TVec3<T>(this->x + other.x, this->y + other.y, this->z + other.z);
}

template<typename T>
GG_INLINE TVec3<T>& TVec3<T>::operator+= (const TVec3<T>& other)
{
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  return *this;
}

// å∏éZ
template<typename T>
GG_INLINE const TVec3<T> TVec3<T>::operator- () const
{
  return TVec3<T>(-this->x, -this->y, -this->z);
}

template<typename T>
GG_INLINE const TVec3<T> TVec3<T>::operator- (const TVec3<T>& other) const
{
  return TVec3<T>(this->x - other.x, this->y - other.y, this->z - other.z);
}

template<typename T>
GG_INLINE TVec3<T>& TVec3<T>::operator-= (const TVec3<T>& other)
{
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;
  return *this;
}

// èÊéZ
template<typename T>
GG_INLINE const TVec3<T> TVec3<T>::operator* (T s) const
{
  return TVec3<T>(this->x * s, this->y * s, this->z * s);
}

template<typename T>
GG_INLINE const TVec3<T> TVec3<T>::operator* (const TVec3<T>& other) const
{
  return TVec3<T>(this->x * other.x, this->y * other.y, this->z * other.z);
}

template<typename T>
GG_INLINE TVec3<T>& TVec3<T>::operator*= (T s)
{
  this->x *= s;
  this->y *= s;
  this->z *= s;
  return *this;
}

template<typename T>
GG_INLINE TVec3<T>& TVec3<T>::operator*= (const TVec3<T>& other)
{
  this->x *= other.x;
  this->y *= other.y;
  this->z *= other.z;
  return *this;
}

// èúéZ
template<typename T>
GG_INLINE const TVec3<T> TVec3<T>::operator/ (T s) const
{
  return TVec3<T>(this->x / s, this->y / s, this->z / s);
}

template<typename T>
GG_INLINE const TVec3<T> TVec3<T>::operator/ (const TVec3<T>& other) const
{
  return TVec3<T>(this->x / other.x, this->y / other.y, this->z / other.z);
}

template<typename T>
GG_INLINE TVec3<T>& TVec3<T>::operator/= (T s)
{
  this->x /= s;
  this->y /= s;
  this->z /= s;
  return *this;
}

template<typename T>
GG_INLINE TVec3<T>& TVec3<T>::operator/= (const TVec3<T>& other)
{
  this->x /= other.x;
  this->y /= other.y;
  this->z /= other.z;
  return *this;
}

// î‰är
template<typename T>
GG_INLINE bool TVec3<T>::operator== (const TVec3<T>& other) const
{
  return this->x == other.x && this->y == other.y && this->z == other.z;
}

template<typename T>
GG_INLINE bool TVec3<T>::operator!= (const TVec3<T>& other) const
{
  return this->x != other.x || this->y != other.y || this->z != other.z;
}

// =================================================================
// Methods
// =================================================================
template<typename T>
GG_INLINE T TVec3<T>::Length() const
{
  return sqrtf(this->LengthSquare());
}

template<typename T>
GG_INLINE T TVec3<T>::LengthSquare() const
{
  return this->x * this->x + this->y * this->y + this->z * this->z;
}

template<typename T>
GG_INLINE TVec3<T> TVec3<T>::Normalized() const
{
  const T length = this->Length();
  return TVec3<T>(this->x / length, this->y / length, this->z / length);
}

template<typename T>
GG_INLINE bool TVec3<T>::IsZero() const
{
  return this->x == 0 && this->y == 0 && this->z == 0;
}
