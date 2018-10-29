#include "Matrix4x4.h"

inline Matrix4x4::Matrix4x4()
{
  this->eigen = Eigen::Matrix<T_FLOAT, 4, 4, Eigen::RowMajor>::Identity();
}

inline Matrix4x4::Matrix4x4(const Eigen::Matrix<T_FLOAT, 4, 4, Eigen::RowMajor>& mat)
{
  this->eigen = mat;
}

inline Matrix4x4::Matrix4x4(const T_FLOAT m[4][4])
  : _11(m[0][0]), _12(m[0][1]), _13(m[0][2]), _14(m[0][3])
  , _21(m[1][0]), _22(m[1][1]), _23(m[1][2]), _24(m[1][3])
  , _31(m[2][0]), _32(m[2][1]), _33(m[2][2]), _34(m[2][3])
  , _41(m[3][0]), _42(m[3][1]), _43(m[3][2]), _44(m[3][3])
{}

inline Matrix4x4::Matrix4x4(const T_FLOAT * f)
  : _11(f[0]), _12(f[1]), _13(f[2]), _14(f[3])
  , _21(f[4]), _22(f[5]), _23(f[6]), _24(f[7])
  , _31(f[8]), _32(f[9]), _33(f[10]), _34(f[11])
  , _41(f[12]), _42(f[13]), _43(f[14]), _44(f[15])
{}

inline Matrix4x4::Matrix4x4(T_FLOAT _11, T_FLOAT _12, T_FLOAT _13, T_FLOAT _14, T_FLOAT _21, T_FLOAT _22, T_FLOAT _23, T_FLOAT _24, T_FLOAT _31, T_FLOAT _32, T_FLOAT _33, T_FLOAT _34, T_FLOAT _41, T_FLOAT _42, T_FLOAT _43, T_FLOAT _44)
  : _11(_11), _12(_12), _13(_13), _14(_14)
  , _21(_21), _22(_22), _23(_23), _24(_24)
  , _31(_31), _32(_32), _33(_33), _34(_34)
  , _41(_41), _42(_42), _43(_43), _44(_44)
{}

inline Matrix4x4::Matrix4x4(const Matrix4x4 & other)
  : eigen(other.eigen)
{}

inline Matrix4x4::operator Eigen::Matrix4f() const
{
  return this->eigen;
}

Matrix4x4 Matrix4x4::Frustum(T_FLOAT left, T_FLOAT right, T_FLOAT bottom, T_FLOAT top, T_FLOAT z_near, T_FLOAT z_far)
{
  Eigen::Matrix<T_FLOAT, 4, 4, Eigen::RowMajor> ret = Eigen::Matrix<T_FLOAT, 4, 4, Eigen::RowMajor>::Zero();
  ret(0, 0) = (2.0f * z_near) / (right - left);
  ret(1, 1) = (2.0f * z_near) / (top - bottom);
  ret(0, 2) = (right + left) / (right - left);
  ret(1, 2) = (top + bottom) / (top - bottom);
  ret(2, 2) = -(z_far + z_near) / (z_far - z_near);
  ret(3, 2) = -1.0f;
  ret(2, 3) = -(2.0f * z_far * z_near) / (z_far - z_near);
  return ret;
}

inline Matrix4x4 Matrix4x4::Ortho(T_FLOAT width, T_FLOAT height, T_FLOAT z_near, T_FLOAT z_far)
{
  Eigen::Matrix<T_FLOAT, 4, 4, Eigen::RowMajor> ret = Eigen::Matrix<T_FLOAT, 4, 4, Eigen::RowMajor>::Zero();
  ret(0, 0) = 2.0f / width;
  ret(1, 1) = 2.0f / height;
  ret(2, 2) = -2.0f / (z_far - z_near);
  ret(2, 3) = -(z_far + z_near) / (z_far - z_near);
  ret(3, 3) = 1.0f;
  return Matrix4x4(ret);
}

inline Matrix4x4 Matrix4x4::Ortho(T_FLOAT left, T_FLOAT right, T_FLOAT bottom, T_FLOAT top, T_FLOAT z_near, T_FLOAT z_far)
{
  Eigen::Matrix<T_FLOAT, 4, 4, Eigen::RowMajor> ret = Eigen::Matrix<T_FLOAT, 4, 4, Eigen::RowMajor>::Zero();
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
  Eigen::Matrix<T_FLOAT, 4, 4, Eigen::RowMajor> ret = Eigen::Matrix<T_FLOAT, 4, 4, Eigen::RowMajor>::Zero();
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
  Eigen::Matrix<T_FLOAT, 4, 4, Eigen::RowMajor> ret = Eigen::Matrix<T_FLOAT, 4, 4, Eigen::RowMajor>::Zero();

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

inline Matrix4x4::operator T_FLOAT*()
{
  return this->data;
}

Matrix4x4::operator const T_FLOAT*() const
{
  return this->data;
}

Matrix4x4 Matrix4x4::Inverse() const
{
  return Matrix4x4(this->eigen.inverse());
}

Matrix4x4 Matrix4x4::Transpose() const
{
  return Matrix4x4(this->eigen.transpose());
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
  this->eigen = this->eigen * y_mat.eigen;
}

void Matrix4x4::Rotation(const TVec2f & value)
{
  this->RotationY(value.y);
  Matrix4x4 y_mat = *this;
  this->RotationX(value.x);
  this->eigen = this->eigen * y_mat.eigen;
}

void Matrix4x4::Rotation(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  this->RotationY(y);
  Matrix4x4 y_mat = *this;
  this->RotationX(x);
  Matrix4x4 x_mat = *this;
  this->RotationZ(z);
  this->eigen = this->eigen * x_mat.eigen * y_mat.eigen;
}

void Matrix4x4::Rotation(const TVec3f & value)
{
  this->RotationY(value.y);
  Matrix4x4 y_mat = *this;
  this->RotationX(value.x);
  Matrix4x4 x_mat = *this;
  this->RotationZ(value.z);
  this->eigen = this->eigen * x_mat.eigen * y_mat.eigen;
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

TVec2f Matrix4x4::GetDirection2d() const
{
  return TVec2f(this->_31, this->_32);
}

TVec3f Matrix4x4::GetDirection3d() const
{
  return TVec3f(this->_31, this->_32, this->_33);
}

TVec2f Matrix4x4::GetPosition2d() const
{
  return TVec2f(this->_41, this->_42);
}

TVec3f Matrix4x4::GetPosition3d() const
{
  return TVec3f(this->_41, this->_42, this->_43);
}

TVec4f Matrix4x4::GetPosition4d() const
{
  return TVec4f(this->_41, this->_42, this->_43, this->_44);
}

TVec3f Matrix4x4::GetCameraXVec() const
{
  return TVec3f(this->_11, this->_12, this->_13);
}

TVec3f Matrix4x4::GetCameraYVec() const
{
  return TVec3f(this->_21, this->_22, this->_23);
}

TVec3f Matrix4x4::GetCameraZVec() const
{
  return TVec3f(this->_31, this->_32, this->_33);
}

TVec3f Matrix4x4::GetWorldScale() const
{
  TVec3f ret;
  ret.x = TVec3f(this->_11, this->_12, this->_13).Length();
  ret.y = TVec3f(this->_21, this->_22, this->_23).Length();
  ret.z = TVec3f(this->_31, this->_32, this->_33).Length();
  return ret;
}
