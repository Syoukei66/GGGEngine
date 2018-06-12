#include <Matrix.h>

Matrix4x4 Matrix4x4::Frustum(T_FLOAT left, T_FLOAT right, T_FLOAT bottom, T_FLOAT top, T_FLOAT z_near, T_FLOAT z_far)
{
  NATIVE_ASSERT(false, "Ç‹ÇæÇ≈Ç´ÇƒÇ‹ÇπÇÒÅI");
  return D3DXMATRIX();
}

Matrix4x4 Matrix4x4::LookAt(const TVec3f& from, const TVec3f& to, const TVec3f& up)
{
  Matrix4x4 ret;
  D3DXMatrixLookAtLH(
    reinterpret_cast<D3DXMATRIX*>(&ret),
    reinterpret_cast<const D3DXVECTOR3*>(from.vec),
    reinterpret_cast<const D3DXVECTOR3*>(to.vec),
    reinterpret_cast<const D3DXVECTOR3*>(up.vec)
  );
  return Matrix4x4(ret.m);
}

Matrix4x4 Matrix4x4::Ortho(T_FLOAT left, T_FLOAT right, T_FLOAT bottom, T_FLOAT top, T_FLOAT z_near, T_FLOAT z_far)
{
  D3DXMATRIX ret;
  D3DXMatrixOrthoLH(
    reinterpret_cast<D3DXMATRIX*>(&ret),
    right - left,
    top - bottom,
    z_near,
    z_far
  );
  return Matrix4x4(ret.m);
}

Matrix4x4 Matrix4x4::Perspective(T_FLOAT fov, T_FLOAT aspect, T_FLOAT z_near, T_FLOAT z_far)
{
  Matrix4x4 ret;
  D3DXMatrixPerspectiveFovLH(
    reinterpret_cast<D3DXMATRIX*>(&ret),
    fov,
    aspect,
    z_near,
    z_far
  );
  return ret;
}

Matrix4x4 Matrix4x4::Rotate(T_FLOAT x, T_FLOAT y)
{
  Matrix4x4 ret;
  D3DXMatrixRotationX(reinterpret_cast<D3DXMATRIX*>(&ret), x);
  Matrix4x4 mat;
  D3DXMatrixRotationY(reinterpret_cast<D3DXMATRIX*>(&mat), y);
  D3DXMatrixMultiply(reinterpret_cast<D3DXMATRIX*>(&ret), reinterpret_cast<D3DXMATRIX*>(&mat), reinterpret_cast<D3DXMATRIX*>(&ret));
  return ret;
}

Matrix4x4 Matrix4x4::Rotate(const TVec2f& value)
{
  Matrix4x4 ret;
  D3DXMatrixRotationX(reinterpret_cast<D3DXMATRIX*>(&ret), value.x);
  Matrix4x4 mat;
  D3DXMatrixRotationY(reinterpret_cast<D3DXMATRIX*>(&mat), value.y);
  D3DXMatrixMultiply(reinterpret_cast<D3DXMATRIX*>(&ret), reinterpret_cast<D3DXMATRIX*>(&mat), reinterpret_cast<D3DXMATRIX*>(&ret));
  return ret;
}

Matrix4x4 Matrix4x4::Rotate(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  Matrix4x4 ret;
  D3DXMatrixRotationZ(reinterpret_cast<D3DXMATRIX*>(&ret), z);
  Matrix4x4 mat;
  D3DXMatrixRotationX(reinterpret_cast<D3DXMATRIX*>(&mat), x);
  D3DXMatrixMultiply(reinterpret_cast<D3DXMATRIX*>(&ret), reinterpret_cast<D3DXMATRIX*>(&mat), reinterpret_cast<D3DXMATRIX*>(&ret));
  D3DXMatrixRotationY(reinterpret_cast<D3DXMATRIX*>(&mat), y);
  D3DXMatrixMultiply(reinterpret_cast<D3DXMATRIX*>(&ret), reinterpret_cast<D3DXMATRIX*>(&mat), reinterpret_cast<D3DXMATRIX*>(&ret));
  return ret;
}

Matrix4x4 Matrix4x4::Rotate(const TVec3f& value)
{
  Matrix4x4 ret;
  D3DXMatrixRotationZ(reinterpret_cast<D3DXMATRIX*>(&ret), value.z);
  Matrix4x4 mat;
  D3DXMatrixRotationX(reinterpret_cast<D3DXMATRIX*>(&mat), value.x);
  D3DXMatrixMultiply(reinterpret_cast<D3DXMATRIX*>(&ret), reinterpret_cast<D3DXMATRIX*>(&mat), reinterpret_cast<D3DXMATRIX*>(&ret));
  D3DXMatrixRotationY(reinterpret_cast<D3DXMATRIX*>(&mat), value.y);
  D3DXMatrixMultiply(reinterpret_cast<D3DXMATRIX*>(&ret), reinterpret_cast<D3DXMATRIX*>(&mat), reinterpret_cast<D3DXMATRIX*>(&ret));
  return ret;
}

Matrix4x4 Matrix4x4::Rotate(const Quaternion& q)
{
  Matrix4x4 ret;
  D3DXMatrixRotationQuaternion(
    reinterpret_cast<D3DXMATRIX*>(&ret), reinterpret_cast<const D3DXQUATERNION*>(&q)
  );
  return ret;
}

Matrix4x4 Matrix4x4::RotateX(T_FLOAT x)
{
  Matrix4x4 ret;
  D3DXMatrixRotationX(reinterpret_cast<D3DXMATRIX*>(&ret), x);
  return ret;
}

Matrix4x4 Matrix4x4::RotateY(T_FLOAT y)
{
  Matrix4x4 ret;
  D3DXMatrixRotationY(reinterpret_cast<D3DXMATRIX*>(&ret), y);
  return ret;
}

Matrix4x4 Matrix4x4::RotateZ(T_FLOAT z)
{
  Matrix4x4 ret;
  D3DXMatrixRotationZ(reinterpret_cast<D3DXMATRIX*>(&ret), z);
  return ret;
}

Matrix4x4 Matrix4x4::Scale(T_FLOAT value)
{
  Matrix4x4 ret;
  D3DXMatrixScaling(reinterpret_cast<D3DXMATRIX*>(&ret), value, value, value);
  return ret;
}

Matrix4x4 Matrix4x4::Scale(T_FLOAT x, T_FLOAT y)
{
  Matrix4x4 ret;
  D3DXMatrixScaling(reinterpret_cast<D3DXMATRIX*>(&ret), x, y, 1.0f);
  return ret;
}

Matrix4x4 Matrix4x4::Scale(const TVec2f& value)
{
  Matrix4x4 ret;
  D3DXMatrixScaling(reinterpret_cast<D3DXMATRIX*>(&ret), value.x, value.y, 1.0f);
  return ret;
}

Matrix4x4 Matrix4x4::Scale(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  Matrix4x4 ret;
  D3DXMatrixScaling(reinterpret_cast<D3DXMATRIX*>(&ret), x, y, z);
  return ret;
}

Matrix4x4 Matrix4x4::Scale(const TVec3f& value)
{
  Matrix4x4 ret;
  D3DXMatrixScaling(reinterpret_cast<D3DXMATRIX*>(&ret), value.x, value.y, value.z);
  return ret;
}

Matrix4x4 Matrix4x4::ScaleX(T_FLOAT x)
{
  Matrix4x4 ret;
  D3DXMatrixScaling(reinterpret_cast<D3DXMATRIX*>(&ret), x, 1.0f, 1.0f);
  return ret;
}

Matrix4x4 Matrix4x4::ScaleY(T_FLOAT y)
{
  Matrix4x4 ret;
  D3DXMatrixScaling(reinterpret_cast<D3DXMATRIX*>(&ret), 1.0f, y, 1.0f);
  return ret;
}

Matrix4x4 Matrix4x4::ScaleZ(T_FLOAT z)
{
  Matrix4x4 ret;
  D3DXMatrixScaling(reinterpret_cast<D3DXMATRIX*>(&ret), 1.0f, 1.0f, z);
  return ret;
}

Matrix4x4 Matrix4x4::Translate(T_FLOAT x, T_FLOAT y)
{
  Matrix4x4 ret;
  D3DXMatrixTranslation(reinterpret_cast<D3DXMATRIX*>(&ret), x, y, 0.0f);
  return ret;
}

Matrix4x4 Matrix4x4::Translate(const TVec2f& value)
{
  Matrix4x4 ret;
  D3DXMatrixTranslation(reinterpret_cast<D3DXMATRIX*>(&ret), value.x, value.y, 0.0f);
  return ret;
}

Matrix4x4 Matrix4x4::Translate(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  Matrix4x4 ret;
  D3DXMatrixTranslation(reinterpret_cast<D3DXMATRIX*>(&ret), x, y, z);
  return ret;
}

Matrix4x4 Matrix4x4::Translate(const TVec3f& value)
{
  Matrix4x4 ret;
  D3DXMatrixTranslation(reinterpret_cast<D3DXMATRIX*>(&ret), value.x, value.y, value.z);
  return ret;
}

Matrix4x4 Matrix4x4::TranslateX(T_FLOAT x)
{
  Matrix4x4 ret;
  D3DXMatrixTranslation(reinterpret_cast<D3DXMATRIX*>(&ret), x, 0.0f, 0.0f);
  return ret;
}

Matrix4x4 Matrix4x4::TranslateY(T_FLOAT y)
{
  Matrix4x4 ret;
  D3DXMatrixTranslation(reinterpret_cast<D3DXMATRIX*>(&ret), 0.0f, y, 0.0f);
  return ret;
}

Matrix4x4 Matrix4x4::TranslateZ(T_FLOAT z)
{
  Matrix4x4 ret;
  D3DXMatrixTranslation(reinterpret_cast<D3DXMATRIX*>(&ret), 0.0f, 0.0f, z);
  return ret;
}

Matrix4x4 Matrix4x4::TRS(const TVec3f& pos, const Quaternion& q, const TVec3f& s)
{
  Matrix4x4 ret;
  NATIVE_ASSERT(false, "Ç‹ÇæÇ≈Ç´ÇƒÇ‹ÇπÇÒÅI");
  return ret;
}

Matrix4x4::Matrix4x4()
  : _11(1.0f), _12(0.0f), _13(0.0f), _14(0.0f)
  , _21(0.0f), _22(1.0f), _23(0.0f), _24(0.0f)
  , _31(0.0f), _32(0.0f), _33(1.0f), _34(0.0f)
  , _41(0.0f), _42(0.0f), _43(0.0f), _44(1.0f)
{
}

Matrix4x4::Matrix4x4(const T_FLOAT m[4][4])
  : _11(m[0][0]), _12(m[0][1]), _13(m[0][2]), _14(m[0][3])
  , _21(m[1][0]), _22(m[1][1]), _23(m[1][2]), _24(m[1][3])
  , _31(m[2][0]), _32(m[2][1]), _33(m[2][2]), _34(m[2][3])
  , _41(m[3][0]), _42(m[3][1]), _43(m[3][2]), _44(m[3][3])
{
}

Matrix4x4::Matrix4x4(const T_FLOAT* f)
  : _11(f[0]), _12(f[1]), _13(f[2]), _14(f[3])
  , _21(f[4]), _22(f[5]), _23(f[6]), _24(f[7])
  , _31(f[8]), _32(f[9]), _33(f[10]), _34(f[11])
  , _41(f[12]), _42(f[13]), _43(f[14]), _44(f[15])
{
}

Matrix4x4::Matrix4x4(const Matrix4x4& other)
  : _11(other._11), _12(other._12), _13(other._13), _14(other._14)
  , _21(other._21), _22(other._22), _23(other._23), _24(other._24)
  , _31(other._31), _32(other._32), _33(other._33), _34(other._34)
  , _41(other._41), _42(other._42), _43(other._43), _44(other._44)
{
}

Matrix4x4::Matrix4x4(T_FLOAT _11, T_FLOAT _12, T_FLOAT _13, T_FLOAT _14, T_FLOAT _21, T_FLOAT _22, T_FLOAT _23, T_FLOAT _24, T_FLOAT _31, T_FLOAT _32, T_FLOAT _33, T_FLOAT _34, T_FLOAT _41, T_FLOAT _42, T_FLOAT _43, T_FLOAT _44)
  : _11(_11), _12(_12), _13(_13), _14(_14)
  , _21(_21), _22(_22), _23(_23), _24(_24)
  , _31(_31), _32(_32), _33(_33), _34(_34)
  , _41(_41), _42(_42), _43(_43), _44(_44)
{
}

T_FLOAT& Matrix4x4::operator()(T_UINT8 Row, T_UINT8 Col)
{
  return this->m[Row][Col];
}

T_FLOAT Matrix4x4::operator()(T_UINT8 Row, T_UINT8 Col) const
{
  return this->m[Row][Col];
}

Matrix4x4::operator T_FLOAT*()
{
  return this->v;
}

Matrix4x4::operator const T_FLOAT*() const
{
  return this->v;
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other)
{
  return *this = *this * other;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const
{
  D3DXMATRIX mat = D3DXMATRIX(this->v);
  mat = mat * D3DXMATRIX(other.v);
  return static_cast<Matrix4x4>(mat);
}

TVec2f Matrix4x4::operator*(const TVec2f& f) const
{
  TVec2f ret = f;
  const T_FLOAT x = ret.x;
  const T_FLOAT y = ret.y;
  ret.x = (x * this->_11) + (y * this->_21) + this->_41;
  ret.y = (x * this->_12) + (y * this->_22) + this->_42;
  return ret;
}

TVec3f Matrix4x4::operator*(const TVec3f& f) const
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

TVec4f Matrix4x4::operator*(const TVec4f& f) const
{
  TVec4f ret = f;
  const T_FLOAT x = ret.x;
  const T_FLOAT y = ret.y;
  const T_FLOAT z = ret.z;
  const T_FLOAT w = ret.w;
  ret.x = (x * this->_11) + (y * this->_21) + (z * this->_31) + (w * this->_41);
  ret.y = (x * this->_12) + (y * this->_22) + (z * this->_32) + (w * this->_42);
  ret.z = (x * this->_13) + (y * this->_23) + (z * this->_33) + (w * this->_43);
  ret.w = (x * this->_14) + (y * this->_24) + (z * this->_34) + (w * this->_44);
  return ret;
}

bool Matrix4x4::operator==(const Matrix4x4& other) const
{
  for (T_UINT8 i = 0; i < 16; ++i)
  {
    if (this->v[i] != other.v[i])
    {
      return false;
    }
  }
  return true;
}

bool Matrix4x4::operator!=(const Matrix4x4& other) const
{
  for (T_UINT8 i = 0; i < 16; ++i)
  {
    if (this->v[i] != other.v[i])
    {
      return true;
    }
  }
  return false;
}

Matrix4x4 Matrix4x4::Inverse() const
{
  return Matrix4x4();
}

Matrix4x4 Matrix4x4::Transpose() const
{
  return Matrix4x4();
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
