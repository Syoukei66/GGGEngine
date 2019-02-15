#pragma once

#include <Core/Macro/ProgramMacro.h>
#include <Core/Macro/ObjectMacro.h>

template <typename T>
struct TVec2;
template <typename T>
struct TVec4;

/*!
* @brief ÇRéüå≥ÉxÉNÉgÉã
*/
template<typename T>
struct TVec3
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(TVec3<T>)
  {
    archive(x);
    archive(y);
    archive(z);
  }

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
  // Static Methods
  // =================================================================
public:
  static GG_INLINE T Dot(const TVec3<T>& a, const TVec3<T>& b);
  static GG_INLINE TVec3<T> Cross(const TVec3<T>& a, const TVec3<T>& b);

  // =================================================================
  // Data Members
  // =================================================================
public:
  union
  {
    struct
    {
      T x, y, z;
    };
    T data[3];
  };

  // =================================================================
  // Constructor
  // =================================================================
public:
  GG_INLINE TVec3();
  GG_INLINE TVec3(T x, T y, T z);
  GG_INLINE TVec3(const TVec2<T>& other, T_FLOAT z = 0);
  GG_INLINE TVec3(const TVec3<T>& other);
  GG_INLINE TVec3(const TVec4<T>& other);

  // =================================================================
  // Operator
  // =================================================================
public:
  // ë„ì¸
  GG_INLINE TVec3<T>& operator= (const TVec3<T>& other);
  GG_INLINE TVec3<T>& operator= (const TVec4<T>& other);
  // â¡éZ
  GG_INLINE const TVec3<T> operator+ () const;
  GG_INLINE const TVec3<T> operator+ (const TVec3<T>& other) const;
  GG_INLINE TVec3<T>& operator+= (const TVec3<T>& other);
  // å∏éZ
  GG_INLINE const TVec3<T> operator- () const;
  GG_INLINE const TVec3<T> operator- (const TVec3<T>& other) const;
  GG_INLINE TVec3<T>& operator-= (const TVec3<T>& other);
  // èÊéZ
  GG_INLINE const TVec3<T> operator* (T s) const;
  GG_INLINE const TVec3<T> operator* (const TVec3<T>& other) const;
  GG_INLINE TVec3<T>& operator*= (T s);
  GG_INLINE TVec3<T>& operator*= (const TVec3<T>& other);
  // èúéZ
  GG_INLINE const TVec3<T> operator/ (T s) const;
  GG_INLINE const TVec3<T> operator/ (const TVec3<T>& other) const;
  GG_INLINE TVec3<T>& operator/= (T s);
  GG_INLINE TVec3<T>& operator/= (const TVec3<T>& other);
  // î‰är
  GG_INLINE bool operator== (const TVec3<T>& other) const;
  GG_INLINE bool operator!= (const TVec3<T>& other) const;

  // =================================================================
  // Methods
  // =================================================================
 public:
   GG_INLINE T Length() const;
   GG_INLINE T LengthSquare() const;
   GG_INLINE TVec3<T> Normalized() const;
   GG_INLINE bool IsZero() const;
};

typedef TVec3<T_INT32> TVec3i;
typedef TVec3<T_FLOAT> TVec3f;

#include "Vector3.inl"