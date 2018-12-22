#include "Matrix4x4.h"

// =================================================================
// Constants
// =================================================================
const Matrix4x4 Matrix4x4::identity = Matrix4x4();
const Matrix4x4 Matrix4x4::zero = Matrix4x4(
  0.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 0.0f
);

// =================================================================
// Static Methods
// =================================================================
Matrix4x4 Matrix4x4::Frustum(T_FLOAT left, T_FLOAT right, T_FLOAT bottom, T_FLOAT top, T_FLOAT z_near, T_FLOAT z_far)
{
  Matrix4x4 ret = Matrix4x4::zero;
  ret(0, 0) = (2.0f * z_near) / (right - left);
  ret(1, 1) = (2.0f * z_near) / (top - bottom);
  ret(0, 2) = (right + left) / (right - left);
  ret(1, 2) = (top + bottom) / (top - bottom);
  ret(2, 2) = -(z_far + z_near) / (z_far - z_near);
  ret(3, 2) = -1.0f;
  ret(2, 3) = -(2.0f * z_far * z_near) / (z_far - z_near);
  return ret;
}

Matrix4x4 Matrix4x4::Ortho(T_FLOAT width, T_FLOAT height, T_FLOAT z_near, T_FLOAT z_far)
{
  Matrix4x4 ret = Matrix4x4::zero;
  ret(0, 0) = 2.0f / width;
  ret(1, 1) = 2.0f / height;
  ret(2, 2) = -2.0f / (z_far - z_near);
  ret(2, 3) = -(z_far + z_near) / (z_far - z_near);
  ret(3, 3) = 1.0f;
  return Matrix4x4(ret);
}

Matrix4x4 Matrix4x4::Ortho(T_FLOAT left, T_FLOAT right, T_FLOAT bottom, T_FLOAT top, T_FLOAT z_near, T_FLOAT z_far)
{
  Matrix4x4 ret = Matrix4x4::zero;
  ret(0, 0) = 2.0f / (right - left);
  ret(1, 1) = 2.0f / (top - bottom);
  ret(2, 2) = -2.0f / (z_far - z_near);
  ret(0, 3) = -(right + left) / (right - left);
  ret(1, 3) = -(top + bottom) / (top - bottom);
  ret(2, 3) = -(z_far + z_near) / (z_far - z_near);
  ret(3, 3) = 1.0f;
  return Matrix4x4(ret);
}

Matrix4x4 Matrix4x4::Perspective(T_FLOAT fov, T_FLOAT aspect, T_FLOAT z_near, T_FLOAT z_far)
{
  Matrix4x4 ret = Matrix4x4::zero;
  const T_FLOAT y_scale = 1.0f / tanf(fov * 0.5f);
  const T_FLOAT x_scale = y_scale / aspect;
  ret(0, 0) = x_scale;
  ret(1, 1) = y_scale;
  ret(2, 2) = z_far / (z_far - z_near);
  ret(2, 3) = 1.0f;
  ret(3, 2) = -z_near * z_far / (z_far - z_near);
  return ret;
}

Matrix4x4 Matrix4x4::LookAt(const TVec3f & eye, const TVec3f & at, const TVec3f & up)
{
  const TVec3f z_axis = (at - eye).Normalized();
  const TVec3f x_axis = (TVec3f::Cross(up, z_axis)).Normalized();
  const TVec3f y_axis = TVec3f::Cross(z_axis, x_axis);
  Matrix4x4 ret = Matrix4x4::zero;

  ret(0, 0) = x_axis.x;
  ret(0, 1) = y_axis.x;
  ret(0, 2) = z_axis.x;

  ret(1, 0) = x_axis.y;
  ret(1, 1) = y_axis.y;
  ret(1, 2) = z_axis.y;

  ret(2, 0) = x_axis.z;
  ret(2, 1) = y_axis.z;
  ret(2, 2) = z_axis.z;

  ret(3, 0) = -TVec3f::Dot(x_axis, eye);
  ret(3, 1) = -TVec3f::Dot(y_axis, eye);
  ret(3, 2) = -TVec3f::Dot(z_axis, eye);
  ret(3, 3) = 1.0f;

  return ret;
}

// =================================================================
// Methods
// =================================================================
Matrix4x4 Matrix4x4::Inverse() const
{
  Matrix4x4 a = *this;
  Matrix4x4 ret = Matrix4x4::identity;
  T_DOUBLE buf;

  for (T_UINT8 i = 0; i < 4; i++)
  {
    buf = 1.0 / ret.m[i][i];
    for (T_UINT8 j = 0; j < 4; j++)
    {
      a.m[i][j] = (T_FLOAT)(a.m[i][j] * buf);
      ret.m[i][j] = (T_FLOAT)(a.m[i][j] * buf);
    }
    for (T_UINT8 j = 0; j < 4; j++)
    {
      if (i != j)
      {
        buf = a.m[j][i];
        for (T_UINT8 k = 0; k < 4; k++)
        {
          a.m[j][k] -= (T_FLOAT)(a.m[i][k] * buf);
          ret.m[j][k] -= (T_FLOAT)(ret.m[i][k] * buf);
        }
      }
    }
  }
  return ret;
}

Matrix4x4 Matrix4x4::Transpose() const
{
  return Matrix4x4(
    this->_11, this->_21, this->_31, this->_41,
    this->_12, this->_22, this->_32, this->_42,
    this->_13, this->_23, this->_33, this->_43,
    this->_14, this->_24, this->_34, this->_44
  );
}

void Matrix4x4::Translation(T_FLOAT x, T_FLOAT y)
{
  *this = Matrix4x4::identity;
  this->_41 = x;
  this->_42 = y;
}

void Matrix4x4::Translation(const TVec2f & value)
{
  *this = Matrix4x4::identity;
  this->_41 = value.x;
  this->_42 = value.y;
}

void Matrix4x4::Translation(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  *this = Matrix4x4::identity;
  this->_41 = x;
  this->_42 = y;
  this->_43 = z;
}

void Matrix4x4::Translation(const TVec3f & value)
{
  *this = Matrix4x4::identity;
  this->_41 = value.x;
  this->_42 = value.y;
  this->_43 = value.z;
}

void Matrix4x4::TranslationX(T_FLOAT x)
{
  *this = Matrix4x4::identity;
  this->_41 = x;
}

void Matrix4x4::TranslationY(T_FLOAT y)
{
  *this = Matrix4x4::identity;
  this->_42 = y;
}

void Matrix4x4::TranslationZ(T_FLOAT z)
{
  *this = Matrix4x4::identity;
  this->_43 = z;
}

void Matrix4x4::Scaling(T_FLOAT value)
{
  *this = Matrix4x4::identity;
  this->_11 = value;
  this->_22 = value;
  this->_33 = value;
}

void Matrix4x4::Scaling(T_FLOAT x, T_FLOAT y)
{
  *this = Matrix4x4::identity;
  this->_11 = x;
  this->_22 = y;
}

void Matrix4x4::Scaling(const TVec2f & value)
{
  *this = Matrix4x4::identity;
  this->_11 = value.x;
  this->_22 = value.y;
}

void Matrix4x4::Scaling(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  *this = Matrix4x4::identity;
  this->_11 = x;
  this->_22 = y;
  this->_33 = z;
}

void Matrix4x4::Scaling(const TVec3f & value)
{
  *this = Matrix4x4::identity;
  this->_11 = value.x;
  this->_22 = value.y;
  this->_33 = value.z;
}

void Matrix4x4::ScalingX(T_FLOAT x)
{
  *this = Matrix4x4::identity;
  this->_11 = x;
}

void Matrix4x4::ScalingY(T_FLOAT y)
{
  *this = Matrix4x4::identity;
  this->_22 = y;
}

void Matrix4x4::ScalingZ(T_FLOAT z)
{
  *this = Matrix4x4::identity;
  this->_33 = z;
}

void Matrix4x4::Rotation(T_FLOAT x, T_FLOAT y)
{
  this->RotationY(y);
  Matrix4x4 y_mat = *this;
  this->RotationX(x);
  *this *= y_mat;
}

void Matrix4x4::Rotation(const TVec2f& value)
{
  this->RotationY(value.y);
  Matrix4x4 y_mat = *this;
  this->RotationX(value.x);
  *this *= y_mat;
}

void Matrix4x4::Rotation(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  this->RotationY(y);
  Matrix4x4 y_mat = *this;
  this->RotationX(x);
  Matrix4x4 x_mat = *this;
  this->RotationZ(z);
  *this *= x_mat;
  *this *= y_mat;
}

void Matrix4x4::Rotation(const TVec3f & value)
{
  this->RotationY(value.y);
  Matrix4x4 y_mat = *this;
  this->RotationX(value.x);
  Matrix4x4 x_mat = *this;
  this->RotationZ(value.z);
  *this *= x_mat;
  *this *= y_mat;
}

void Matrix4x4::RotationX(T_FLOAT x)
{
  const T_FLOAT sin_x = sinf(x);
  const T_FLOAT cos_x = cosf(x);
  *this = Matrix4x4::identity;
  this->_22 = cos_x;
  this->_23 = sin_x;
  this->_32 = -sin_x;
  this->_33 = cos_x;
}

void Matrix4x4::RotationY(T_FLOAT y)
{
  const T_FLOAT sin_y = sinf(y);
  const T_FLOAT cos_y = cosf(y);
  *this = Matrix4x4::identity;
  this->_11 = cos_y;
  this->_13 = -sin_y;
  this->_31 = sin_y;
  this->_33 = cos_y;
}

void Matrix4x4::RotationZ(T_FLOAT z)
{
  const T_FLOAT sin_z = sinf(z);
  const T_FLOAT cos_z = cosf(z);
  *this = Matrix4x4::identity;
  this->_11 = cos_z;
  this->_12 = sin_z;
  this->_21 = -sin_z;
  this->_22 = cos_z;
}
