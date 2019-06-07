#pragma once

#include <Core/Macro/ProgramMacro.h>
#include <Core/Macro/ObjectMacro.h>

template <typename T>
struct TVec3;
template <typename T>
struct TVec4;

/*!
 * @brief ２次元ベクトル
 */
template <typename T>
struct TVec2
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(TVec2<T>)
  {
    archive(x);
    archive(y);
  }

  // =================================================================
  // Constants
  // =================================================================
public:
  static const TVec2<T> zero;
  static const TVec2<T> one;
  static const TVec2<T> right;
  static const TVec2<T> left;
  static const TVec2<T> up;
  static const TVec2<T> down;

  // =================================================================
  // Data Members
  // =================================================================
public:
  union
  {
    struct
    {
      T x, y;
    };
    struct
    {
      T width, height;
    };
    T data[2];
  };

  // =================================================================
  // Constructor
  // =================================================================
public:
  GG_INLINE TVec2();
  GG_INLINE TVec2(T x, T y);
  GG_INLINE TVec2(const TVec2<T>& other);
  GG_INLINE TVec2(const TVec3<T>& other);
  GG_INLINE TVec2(const TVec4<T>& other);

  // =================================================================
  // Operator
  // =================================================================
public:
  // 代入
  GG_INLINE TVec2<T>& operator=(const TVec2<T>& other);
  GG_INLINE TVec2<T>& operator=(const TVec3<T>& other);
  GG_INLINE TVec2<T>& operator=(const TVec4<T>& other);
  // 加算
  GG_INLINE const TVec2<T> operator+ () const;
  GG_INLINE const TVec2<T> operator+ (const TVec2<T>& other) const;
  GG_INLINE TVec2<T>& operator+= (const TVec2<T>& other);
  // 減算
  GG_INLINE const TVec2<T> operator- () const;
  GG_INLINE const TVec2<T> operator- (const TVec2<T>& other) const;
  GG_INLINE TVec2<T>& operator-= (const TVec2<T>& other);
  // 乗算
  GG_INLINE const TVec2<T> operator* (T s) const;
  GG_INLINE const TVec2<T> operator* (const TVec2<T>& other) const;
  GG_INLINE TVec2<T>& operator*= (T s);
  GG_INLINE TVec2<T>& operator*= (const TVec2<T>& other);
  // 除算
  GG_INLINE const TVec2<T> operator/ (T s) const;
  GG_INLINE const TVec2<T> operator/ (const TVec2<T>& other) const;
  GG_INLINE TVec2<T>& operator/= (T s);
  GG_INLINE TVec2<T>& operator/= (const TVec2<T>& other);
  // 比較
  GG_INLINE bool operator== (const TVec2<T>& other) const;
  GG_INLINE bool operator!= (const TVec2<T>& other) const;

  // =================================================================
  // Methods
  // =================================================================
public:
  GG_INLINE T Length() const;
  GG_INLINE T LengthSquare() const;
  GG_INLINE TVec2<T> Normalized() const;
  GG_INLINE bool IsZero() const;
};

typedef TVec2<T_INT32> TVec2i;
typedef TVec2<T_FLOAT> TVec2f;

#include "Vector2.inl"