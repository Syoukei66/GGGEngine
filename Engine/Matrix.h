#pragma once

#include "NativeType.h"
#include "Geometry.h"
#include "Quaternion.h"

union Matrix4x4
{
public:
  struct
  {
    T_FLOAT _11, _12, _13, _14;
    T_FLOAT _21, _22, _23, _24;
    T_FLOAT _31, _32, _33, _34;
    T_FLOAT _41, _42, _43, _44;
  };

  T_FLOAT m[4][4];

  T_FLOAT v[16];
public:
  static const Matrix4x4 identity;
  static const Matrix4x4 zero;

public:
  static Matrix4x4 Frustum(
    T_FLOAT left, T_FLOAT right,
    T_FLOAT bottom, T_FLOAT top,
    T_FLOAT z_near, T_FLOAT z_far
  );
  static Matrix4x4 LookAt(const TVec3f& from, const TVec3f& to, const TVec3f& up);
  static Matrix4x4 Ortho(T_FLOAT left, T_FLOAT right, T_FLOAT bottom, T_FLOAT top, T_FLOAT z_near, T_FLOAT z_far);
  static Matrix4x4 Perspective(T_FLOAT fov, T_FLOAT aspect, T_FLOAT z_near, T_FLOAT z_far);

  static Matrix4x4 Rotate(T_FLOAT x, T_FLOAT y);
  static Matrix4x4 Rotate(const TVec2f& value);
  static Matrix4x4 Rotate(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  static Matrix4x4 Rotate(const TVec3f& value);
  static Matrix4x4 Rotate(const Quaternion& q);
  static Matrix4x4 RotateX(T_FLOAT x);
  static Matrix4x4 RotateY(T_FLOAT y);
  static Matrix4x4 RotateZ(T_FLOAT z);

  static Matrix4x4 Scale(T_FLOAT value);
  static Matrix4x4 Scale(T_FLOAT x, T_FLOAT y);
  static Matrix4x4 Scale(const TVec2f& value);
  static Matrix4x4 Scale(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  static Matrix4x4 Scale(const TVec3f& value);
  static Matrix4x4 ScaleX(T_FLOAT x);
  static Matrix4x4 ScaleY(T_FLOAT y);
  static Matrix4x4 ScaleZ(T_FLOAT z);

  static Matrix4x4 Translate(T_FLOAT x, T_FLOAT y);
  static Matrix4x4 Translate(const TVec2f& value);
  static Matrix4x4 Translate(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  static Matrix4x4 Translate(const TVec3f& value);
  static Matrix4x4 TranslateX(T_FLOAT x);
  static Matrix4x4 TranslateY(T_FLOAT y);
  static Matrix4x4 TranslateZ(T_FLOAT z);

  static Matrix4x4 TRS(const TVec3f& pos, const Quaternion& q, const TVec3f& s);

public:
  Matrix4x4();
  Matrix4x4(const T_FLOAT m[4][4]);
  Matrix4x4(const T_FLOAT* f);
  Matrix4x4(const Matrix4x4& other);
  Matrix4x4(
    T_FLOAT _11, T_FLOAT _12, T_FLOAT _13, T_FLOAT _14,
    T_FLOAT _21, T_FLOAT _22, T_FLOAT _23, T_FLOAT _24,
    T_FLOAT _31, T_FLOAT _32, T_FLOAT _33, T_FLOAT _34,
    T_FLOAT _41, T_FLOAT _42, T_FLOAT _43, T_FLOAT _44
  );

  T_FLOAT& operator () (T_UINT8 Row, T_UINT8 Col);
  T_FLOAT  operator () (T_UINT8 Row, T_UINT8 Col) const;

  operator T_FLOAT* ();
  operator const T_FLOAT* () const;

  Matrix4x4& operator *= (const Matrix4x4& other);
  Matrix4x4 operator * (const Matrix4x4& other) const;
  TVec2f operator * (const TVec2f& f) const;
  TVec3f operator * (const TVec3f& f) const;
  TVec4f operator * (const TVec4f& f) const;

  bool operator == (const Matrix4x4& other) const;
  bool operator != (const Matrix4x4& other) const;

public:
  Matrix4x4 Inverse() const;
  Matrix4x4 Transpose() const;

  TVec2f GetDirection2d() const;
  TVec3f GetDirection3d() const;

  TVec2f GetPosition2d() const;
  TVec3f GetPosition3d() const;
  TVec4f GetPosition4d() const;

  TVec3f GetCameraXVec() const;
  TVec3f GetCameraYVec() const;
  TVec3f GetCameraZVec() const;

  TVec3f GetWorldScale() const;

};