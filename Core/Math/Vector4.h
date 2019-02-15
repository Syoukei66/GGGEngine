#pragma once

#include <Core/Macro/ProgramMacro.h>
#include <Core/Macro/ObjectMacro.h>

template <typename T>
struct TVec2;
template <typename T>
struct TVec3;

/*!
 * @brief ÇSéüå≥ÉxÉNÉgÉã
 */
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
    struct
    {
      TVec2<T> pos;
      TVec2<T> size;
    };
    T data[4];
  };

  // =================================================================
  // Constructor
  // =================================================================
public:
  GG_INLINE TVec4();
  GG_INLINE TVec4(T x, T y, T z, T w);
  GG_INLINE TVec4(const TVec2<T>& vec2, T_FLOAT z, T_FLOAT w);
  GG_INLINE TVec4(const TVec3<T>& vec3, T_FLOAT w);
  GG_INLINE TVec4(const TVec4<T>& vec4);

  // =================================================================
  // Operator
  // =================================================================
public:
  // ë„ì¸
  GG_INLINE TVec4<T>& operator=(const TVec4<T>& other);
  // â¡éZ
  GG_INLINE const TVec4<T> operator+ () const;
  GG_INLINE const TVec4<T> operator+ (const TVec4<T>& other) const;
  GG_INLINE TVec4<T>& operator+= (const TVec4<T>& other);
  // å∏éZ
  GG_INLINE const TVec4<T> operator- () const;
  GG_INLINE const TVec4<T> operator- (const TVec4<T>& other) const;
  GG_INLINE TVec4<T>& operator-= (const TVec4<T>& other);
  // èÊéZ
  GG_INLINE const TVec4<T> operator * (T s) const;
  GG_INLINE TVec4<T>& operator *= (const TVec4<T>& other);
  GG_INLINE TVec4<T>& operator *= (const T& other);
  // èúéZ
  GG_INLINE const TVec4<T> operator / (T s) const;
  GG_INLINE TVec4<T>& operator /= (const TVec4<T>& other);
  GG_INLINE TVec4<T>& operator /= (const T& other);
  //î‰är
  GG_INLINE bool operator == (const TVec4<T>& other) const;
  GG_INLINE bool operator != (const TVec4<T>& other) const;

  // =================================================================
  // Methods
  // =================================================================
public:
  GG_INLINE T Length() const;
  GG_INLINE T LengthSquare() const;
  GG_INLINE TVec4<T> Normalized() const;
  GG_INLINE bool IsZero() const;
};

// =================================================================
// Constants
// =================================================================
typedef TVec4<T_INT32> TVec4i;
typedef TVec4<T_FLOAT> TVec4f;

#include "Vector4.inl"