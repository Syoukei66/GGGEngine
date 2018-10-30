#pragma once

#include <Eigen/Core.h>
#include <Eigen/Geometry.h>

struct TranslationMatrix;
struct Quaternion;
struct ScalingMatrix;

struct Matrix4x4
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(Matrix4x4)
  {
    archive(_11); archive(_12); archive(_13); archive(_14);
    archive(_21); archive(_22); archive(_23); archive(_24);
    archive(_31); archive(_32); archive(_33); archive(_34);
    archive(_41); archive(_42); archive(_43); archive(_44);
  }

  // =================================================================
  // Constants
  // =================================================================
public:
  static const Matrix4x4 identity;
  static const Matrix4x4 zero;

  // =================================================================
  // Data Members
  // =================================================================
public:
  union
  {
    struct
    {
      T_FLOAT _11, _12, _13, _14;
      T_FLOAT _21, _22, _23, _24;
      T_FLOAT _31, _32, _33, _34;
      T_FLOAT _41, _42, _43, _44;
    };
    T_FLOAT m[4][4];
    T_FLOAT data[16];
    Eigen::Matrix<T_FLOAT, 4, 4, Eigen::RowMajor> eigen;
  };

  // =================================================================
  // Constructor
  // =================================================================
public:
  Matrix4x4();  
  Matrix4x4(const Eigen::Matrix<T_FLOAT, 4, 4, Eigen::RowMajor>& mat);
  Matrix4x4(const T_FLOAT m[4][4]);
  Matrix4x4(const T_FLOAT* f);
  Matrix4x4(
    T_FLOAT _11, T_FLOAT _12, T_FLOAT _13, T_FLOAT _14,
    T_FLOAT _21, T_FLOAT _22, T_FLOAT _23, T_FLOAT _24,
    T_FLOAT _31, T_FLOAT _32, T_FLOAT _33, T_FLOAT _34,
    T_FLOAT _41, T_FLOAT _42, T_FLOAT _43, T_FLOAT _44
  );

  // =================================================================
  // Copy Constructor / Assign operator
  // =================================================================
public:
  Matrix4x4(const Matrix4x4& other);

  Matrix4x4& operator = (const Matrix4x4& other)
  {
    this->eigen = other.eigen;
    return *this;
  }

  operator Eigen::Matrix4f() const;

  // =================================================================
  // Static Methods
  // =================================================================
public:
  static Matrix4x4 Frustum(T_FLOAT left, T_FLOAT right, T_FLOAT bottom, T_FLOAT top, T_FLOAT z_near, T_FLOAT z_far);
  static Matrix4x4 Ortho(T_FLOAT width, T_FLOAT height, T_FLOAT z_near, T_FLOAT z_far);
  static Matrix4x4 Ortho(T_FLOAT left, T_FLOAT right, T_FLOAT bottom, T_FLOAT top, T_FLOAT z_near, T_FLOAT z_far);
  static Matrix4x4 Perspective(T_FLOAT fov, T_FLOAT aspect, T_FLOAT z_near, T_FLOAT z_far);
  static Matrix4x4 LookAt(const TVec3f& eye, const TVec3f& at, const TVec3f& up);
  static Matrix4x4 TRS(const TranslationMatrix& t, const Quaternion& r, const ScalingMatrix& s);

  // =================================================================
  // Operator
  // =================================================================
public:
  GG_INLINE T_FLOAT & operator () (T_UINT8 Row, T_UINT8 Col)
  {
    return this->m[Row][Col];
  }
  GG_INLINE T_FLOAT operator () (T_UINT8 Row, T_UINT8 Col) const
  {
    return this->m[Row][Col];
  }

  GG_INLINE operator T_FLOAT* ();
  GG_INLINE operator const T_FLOAT* () const;

  GG_INLINE Matrix4x4& operator *= (const Matrix4x4& other)
  {
    this->eigen *= other.eigen;
    return *this;
  }
  GG_INLINE Matrix4x4 operator * (const Matrix4x4& other) const
  {
    return Matrix4x4(this->eigen * other.eigen);
  }
  GG_INLINE TVec2f operator * (const TVec2f& f) const
  {
    TVec2f ret = f;
    const T_FLOAT x = ret.x;
    const T_FLOAT y = ret.y;
    ret.x = (x * this->_11) + (y * this->_21) + this->_41;
    ret.y = (x * this->_12) + (y * this->_22) + this->_42;
    return ret;
  }
  GG_INLINE TVec3f operator * (const TVec3f& f) const
  {
    TVec3f ret = f;
    const T_FLOAT x = ret.x;
    const T_FLOAT y = ret.y;
    const T_FLOAT z = ret.z;
    ret.x = (x * this->_11) + (y * this->_21) + (z * this->_31) + this->_41;
    ret.y = (x * this->_12) + (y * this->_22) + (z * this->_32) + this->_42;
    ret.z = (x * this->_13) + (y * this->_23) + (z * this->_33) + this->_43;
    return ret;
  }
  GG_INLINE TVec4f operator * (const TVec4f& f) const
  {
    return TVec4f(this->eigen * f.eigen);
  }

  GG_INLINE bool operator == (const Matrix4x4& other) const
  {
    return this->eigen == other.eigen;
  }
  GG_INLINE bool operator != (const Matrix4x4& other) const
  {
    return this->eigen != other.eigen;
  }

  // =================================================================
  // Methods
  // =================================================================
public:
  Matrix4x4 Inverse() const;
  Matrix4x4 Transpose() const;

  void Translation(T_FLOAT x, T_FLOAT y);
  void Translation(const TVec2f& value);
  void Translation(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  void Translation(const TVec3f& value);
  void TranslationX(T_FLOAT x);
  void TranslationY(T_FLOAT y);
  void TranslationZ(T_FLOAT z);

  void Scaling(T_FLOAT value);
  void Scaling(T_FLOAT x, T_FLOAT y);
  void Scaling(const TVec2f& value);
  void Scaling(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  void Scaling(const TVec3f& value);
  void ScalingX(T_FLOAT x);
  void ScalingY(T_FLOAT y);
  void ScalingZ(T_FLOAT z);

  void Rotation(T_FLOAT x, T_FLOAT y);
  void Rotation(const TVec2f& value);
  void Rotation(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  void Rotation(const TVec3f& value);
  void RotationX(T_FLOAT x);
  void RotationY(T_FLOAT y);
  void RotationZ(T_FLOAT z);

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
