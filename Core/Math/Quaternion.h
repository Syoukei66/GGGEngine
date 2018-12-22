#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"

struct Quaternion
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(Quaternion)
  {
    archive(v);
    archive(w);
  }

  // =================================================================
  // Constants
  // =================================================================
public:
  static const Quaternion Identity;

  // =================================================================
  // Data Members
  // =================================================================
public:
  union
  {
    struct
    {
      TVec3f v;
      T_FLOAT w;
    };
    T_FLOAT val[4];
  };

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GG_INLINE Quaternion();
  GG_INLINE Quaternion(const TVec3f& v, T_FLOAT rad);
  GG_INLINE Quaternion(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT w);
  GG_INLINE Quaternion(const Quaternion& q);

  // =================================================================
  // Static Methods
  // =================================================================
public:
  static const Quaternion Eular(const TVec3f& eular_angles);
  static const Quaternion Lerp(const Quaternion& a, const Quaternion& b, T_FLOAT t);
  static const Quaternion Slerp(const Quaternion& a, const Quaternion& b, T_FLOAT t);
  static const Quaternion LookRotation(const TVec3f& forward, const TVec3f& upwards = TVec3f(0.0f, 1.0f, 0.0f));
  static T_FLOAT Dot(const Quaternion& a, const Quaternion& b);

  // =================================================================
  // Operator
  // =================================================================
public:
  // ë„ì¸
  GG_INLINE Quaternion& operator=(const Quaternion& other);
  // â¡éZ
  GG_INLINE const Quaternion operator+ () const;
  GG_INLINE const Quaternion operator+ (const Quaternion& other) const;
  GG_INLINE Quaternion& operator+= (const Quaternion& other);
  // å∏éZ
  GG_INLINE const Quaternion operator- () const;
  GG_INLINE const Quaternion operator- (const Quaternion& other) const;
  GG_INLINE Quaternion& operator-= (const Quaternion& other);
  // èÊéZ
  GG_INLINE const Quaternion operator* (T_FLOAT v) const;
  GG_INLINE const Quaternion operator* (const Quaternion& other) const;
  GG_INLINE Quaternion& operator*= (T_FLOAT v);
  GG_INLINE Quaternion& operator*= (const Quaternion& other);
  // èúéZ
  GG_INLINE const Quaternion operator/ (T_FLOAT s) const;
  //GG_INLINE const Quaternion operator/ (const Quaternion& other) const;
  //GG_INLINE Quaternion& operator/= (T_FLOAT s);
  //GG_INLINE Quaternion& operator/= (const Quaternion& other);
  // î‰är
  GG_INLINE bool operator== (const Quaternion& other) const;
  GG_INLINE bool operator!= (const Quaternion& other) const;

  // =================================================================
  // Methods
  // =================================================================

  //TODO: Matrixë§Ç…à⁄ìÆÇ∑ÇÈÇ◊Ç´Ç©
  void FromRotationMatrix(const Matrix4x4& mat);
  void ToRotationMatrix(Matrix4x4* dest);

  GG_INLINE T_FLOAT ScalarSquare() const;
  GG_INLINE T_FLOAT Scalar() const;
  GG_INLINE const Quaternion Conjugated() const;
  GG_INLINE const Quaternion Inversed() const;
  GG_INLINE const Quaternion Normalized() const;
  GG_INLINE bool IsNormal(T_FLOAT eps = 0.1f) const;

};

#include "Quaternion.inl"