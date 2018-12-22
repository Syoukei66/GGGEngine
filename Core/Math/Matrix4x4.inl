#pragma once

#include "Matrix4x4.h"

const Matrix4x4 Matrix4x4::identity = Matrix4x4();
const Matrix4x4 Matrix4x4::zero = Matrix4x4(
  0.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 0.0f
  );

// =================================================================
// Constructor
// =================================================================
GG_INLINE Matrix4x4::Matrix4x4()
  : _11(1.0f), _12(0.0f), _13(0.0f), _14(0.0f)
  , _21(0.0f), _22(1.0f), _23(0.0f), _24(0.0f)
  , _31(0.0f), _32(0.0f), _33(1.0f), _34(0.0f)
  , _41(0.0f), _42(0.0f), _43(0.0f), _44(1.0f)
{
}

GG_INLINE Matrix4x4::Matrix4x4(const T_FLOAT m[4][4])
  : _11(m[0][0]), _12(m[0][1]), _13(m[0][2]), _14(m[0][3])
  , _21(m[1][0]), _22(m[1][1]), _23(m[1][2]), _24(m[1][3])
  , _31(m[2][0]), _32(m[2][1]), _33(m[2][2]), _34(m[2][3])
  , _41(m[3][0]), _42(m[3][1]), _43(m[3][2]), _44(m[3][3])
{}

GG_INLINE Matrix4x4::Matrix4x4(const T_FLOAT * f)
  : _11(f[0]), _12(f[1]), _13(f[2]), _14(f[3])
  , _21(f[4]), _22(f[5]), _23(f[6]), _24(f[7])
  , _31(f[8]), _32(f[9]), _33(f[10]), _34(f[11])
  , _41(f[12]), _42(f[13]), _43(f[14]), _44(f[15])
{}

GG_INLINE Matrix4x4::Matrix4x4(
  T_FLOAT _11, T_FLOAT _12, T_FLOAT _13, T_FLOAT _14,
  T_FLOAT _21, T_FLOAT _22, T_FLOAT _23, T_FLOAT _24,
  T_FLOAT _31, T_FLOAT _32, T_FLOAT _33, T_FLOAT _34,
  T_FLOAT _41, T_FLOAT _42, T_FLOAT _43, T_FLOAT _44
)
  : _11(_11), _12(_12), _13(_13), _14(_14)
  , _21(_21), _22(_22), _23(_23), _24(_24)
  , _31(_31), _32(_32), _33(_33), _34(_34)
  , _41(_41), _42(_42), _43(_43), _44(_44)
{}

GG_INLINE Matrix4x4::Matrix4x4(const Matrix4x4 & other)
  : _11(other._11), _12(other._12), _13(other._13), _14(other._14)
  , _21(other._21), _22(other._22), _23(other._23), _24(other._24)
  , _31(other._31), _32(other._32), _33(other._33), _34(other._34)
  , _41(other._41), _42(other._42), _43(other._43), _44(other._44)
{}

// =================================================================
// Operator
// =================================================================
GG_INLINE T_FLOAT& Matrix4x4::operator() (T_UINT8 Row, T_UINT8 Col)
{
  return this->m[Row][Col];
}
GG_INLINE T_FLOAT Matrix4x4::operator() (T_UINT8 Row, T_UINT8 Col) const
{
  return this->m[Row][Col];
}

GG_INLINE Matrix4x4::operator T_FLOAT* ()
{
  return this->data;
}
GG_INLINE Matrix4x4::operator const T_FLOAT* () const
{
  return this->data;
}

GG_INLINE Matrix4x4& Matrix4x4::operator= (const Matrix4x4& other)
{
  for (T_UINT32 i = 0; i < 16; ++i)
  {
    this->data[i] = other.data[i];
  }
  return *this;
}

GG_INLINE TVec2f Matrix4x4::operator* (const TVec2f& f) const
{
  return TVec2f(
    (f.x * this->_11) + (f.y * this->_21) + this->_41,
    (f.x * this->_12) + (f.y * this->_22) + this->_42
  );
}
GG_INLINE TVec3f Matrix4x4::operator* (const TVec3f& f) const
{
  return TVec3f(
    (f.x * this->_11) + (f.y * this->_21) + (f.z * this->_31) + this->_41,
    (f.x * this->_12) + (f.y * this->_22) + (f.z * this->_32) + this->_42,
    (f.x * this->_13) + (f.y * this->_23) + (f.z * this->_33) + this->_43
  );
}
GG_INLINE TVec4f Matrix4x4::operator* (const TVec4f& f) const
{
  return TVec4f(
    (f.x * this->_11) + (f.y * this->_21) + (f.z * this->_31) + (f.z * this->_41),
    (f.x * this->_12) + (f.y * this->_22) + (f.z * this->_32) + (f.z * this->_42),
    (f.x * this->_13) + (f.y * this->_23) + (f.z * this->_33) + (f.z * this->_43),
    (f.x * this->_14) + (f.y * this->_24) + (f.z * this->_34) + (f.z * this->_44)
  );
}
GG_INLINE Matrix4x4 Matrix4x4::operator* (const Matrix4x4& other) const
{
  T_FLOAT m[4][4] = {};
  for (T_UINT8 i = 0; i < 4; ++i)
  {
    for (T_UINT8 j = 0; j < 4; ++j)
    {
      m[i][j] = 
        this->m[i][0] * other.m[0][j] + 
        this->m[i][1] * other.m[1][j] + 
        this->m[i][2] * other.m[2][j] + 
        this->m[i][3] * other.m[3][j]
        ;
    }
  }
  return Matrix4x4(m);
}
GG_INLINE Matrix4x4& Matrix4x4::operator*= (const Matrix4x4& other)
{
  return *this = *this * other;
}

GG_INLINE bool Matrix4x4::operator== (const Matrix4x4& other) const
{
  return 
    this->_11 == other._11 && this->_12 == other._12 && this->_13 == other._13 && this->_14 == other._14 &&
    this->_21 == other._21 && this->_22 == other._22 && this->_23 == other._23 && this->_24 == other._24 &&
    this->_31 == other._31 && this->_32 == other._32 && this->_33 == other._33 && this->_34 == other._34 &&
    this->_41 == other._41 && this->_42 == other._42 && this->_43 == other._43 && this->_44 == other._44
    ;                                                                            
}                                                                                
GG_INLINE bool Matrix4x4::operator!= (const Matrix4x4& other) const              
{                                                                                
  return                                                                         
    this->_11 != other._11 || this->_12 != other._12 || this->_13 != other._13 || this->_14 != other._14 ||
    this->_21 != other._21 || this->_22 != other._22 || this->_23 != other._23 || this->_24 != other._24 ||
    this->_31 != other._31 || this->_32 != other._32 || this->_33 != other._33 || this->_34 != other._34 ||
    this->_41 != other._41 || this->_42 != other._42 || this->_43 != other._43 || this->_44 != other._44
    ;
}

// =================================================================
// Getter
// =================================================================
GG_INLINE TVec2f Matrix4x4::GetDirection2d() const
{
  return TVec2f(this->_31, this->_32);
}

GG_INLINE TVec3f Matrix4x4::GetDirection3d() const
{
  return TVec3f(this->_31, this->_32, this->_33);
}

GG_INLINE TVec2f Matrix4x4::GetPosition2d() const
{
  return TVec2f(this->_41, this->_42);
}

GG_INLINE TVec3f Matrix4x4::GetPosition3d() const
{
  return TVec3f(this->_41, this->_42, this->_43);
}

GG_INLINE TVec4f Matrix4x4::GetPosition4d() const
{
  return TVec4f(this->_41, this->_42, this->_43, this->_44);
}

GG_INLINE TVec3f Matrix4x4::GetCameraXVec() const
{
  return TVec3f(this->_11, this->_12, this->_13);
}

GG_INLINE TVec3f Matrix4x4::GetCameraYVec() const
{
  return TVec3f(this->_21, this->_22, this->_23);
}

GG_INLINE TVec3f Matrix4x4::GetCameraZVec() const
{
  return TVec3f(this->_31, this->_32, this->_33);
}

GG_INLINE TVec3f Matrix4x4::GetWorldScale() const
{
  return TVec3f(
    TVec3f(this->_11, this->_12, this->_13).Length(),
    TVec3f(this->_21, this->_22, this->_23).Length(),
    TVec3f(this->_31, this->_32, this->_33).Length()
  );
}
