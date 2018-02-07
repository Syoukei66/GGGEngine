#include "NativeMatrix.h"

////平行移動      _41 _42 _43
////スケーリング  _11 _22 _33

// =================================================================
// Constructor / Destructor
// =================================================================
NativeMatrix::NativeMatrix()
{
  this->mat_ = new D3DXMATRIX();
  this->SetNativeInstance<D3DXMATRIX>(this->mat_);
  this->Init();
}

NativeMatrix::NativeMatrix(NativeMatrixInstance* instance)
  : INativeMatrix(instance)
{
  this->mat_ = GetNativeInstance<D3DXMATRIX>();
}

NativeMatrix::NativeMatrix(const NativeMatrix& mat)
  : INativeMatrix(mat.GetNativeInstance())
{
  this->mat_ = GetNativeInstance<D3DXMATRIX>();
}

NativeMatrix::~NativeMatrix()
{
  delete this->mat_;
}
// =================================================================
// Method
// =================================================================
void NativeMatrix::Init()
{
  D3DXMatrixIdentity(this->mat_);
}

void NativeMatrix::Assign(NativeMatrixInstance* mat)
{
  D3DXMatrixIdentity(this->mat_);
  D3DXMatrixMultiply(this->mat_, this->mat_, (D3DXMATRIX*)mat);
}

void NativeMatrix::Assign(const INativeMatrix& mat)
{
  D3DXMatrixIdentity(this->mat_);
  D3DXMatrixMultiply(this->mat_, this->mat_, ((const NativeMatrix&)mat).mat_);
}

void NativeMatrix::Multiple(const INativeMatrix& mat)
{
  D3DXMatrixMultiply(this->mat_, this->mat_, ((const NativeMatrix&)mat).mat_);
}

void NativeMatrix::MultipleReverse(const INativeMatrix & mat)
{
  D3DXMatrixMultiply(this->mat_, ((const NativeMatrix&)mat).mat_, this->mat_);
}

void NativeMatrix::Inverse()
{
  D3DXMatrixInverse(this->mat_, nullptr, this->mat_);
}

void NativeMatrix::Inverse(INativeMatrix* dest) const
{
  D3DXMatrixInverse(((NativeMatrix*)dest)->mat_, nullptr, this->mat_);
}

void NativeMatrix::Translation(T_FLOAT x, T_FLOAT y)
{
  D3DXMatrixTranslation(this->mat_, x, y, 0.0f);
}

void NativeMatrix::Translation(const TVec2f& value)
{
  D3DXMatrixTranslation(this->mat_, value.x, value.y, 0.0f);
}

void NativeMatrix::Translation(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  D3DXMatrixTranslation(this->mat_, x, y, z);
}

void NativeMatrix::Translation(const TVec3f& value)
{
  D3DXMatrixTranslation(this->mat_, value.x, value.y, value.z);
}

void NativeMatrix::TranslationX(T_FLOAT x)
{
  D3DXMatrixTranslation(this->mat_, x, 0.0f, 0.0f);
}

void NativeMatrix::TranslationY(T_FLOAT y)
{
  D3DXMatrixTranslation(this->mat_, 0.0f, y, 0.0f);
}

void NativeMatrix::TranslationZ(T_FLOAT z)
{
  D3DXMatrixTranslation(this->mat_, 0.0f, 0.0f, z);
}

void NativeMatrix::Scaling(T_FLOAT value)
{
  D3DXMatrixScaling(this->mat_, value, value, value);
}

void NativeMatrix::Scaling(T_FLOAT x, T_FLOAT y)
{
  D3DXMatrixScaling(this->mat_, x, y, 1.0f);
}

void NativeMatrix::Scaling(const TVec2f& value)
{
  D3DXMatrixScaling(this->mat_, value.x, value.y, 1.0f);
}

void NativeMatrix::Scaling(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  D3DXMatrixScaling(this->mat_, x, y, z);
}

void NativeMatrix::Scaling(const TVec3f& value)
{
  D3DXMatrixScaling(this->mat_, value.x, value.y, value.z);
}

void NativeMatrix::ScalingX(T_FLOAT x)
{
  D3DXMatrixScaling(this->mat_, x, 1.0f, 1.0f);
}

void NativeMatrix::ScalingY(T_FLOAT y)
{
  D3DXMatrixScaling(this->mat_, 1.0f, y, 1.0f);
}

void NativeMatrix::ScalingZ(T_FLOAT z)
{
  D3DXMatrixScaling(this->mat_, 1.0f, 1.0f, z);
}

void NativeMatrix::Rotation(T_FLOAT x, T_FLOAT y)
{
  D3DXMatrixRotationX(this->mat_, x);

  D3DXMATRIX mat;
  D3DXMatrixRotationY(&mat, y);
  D3DXMatrixMultiply(this->mat_, &mat, this->mat_);
}

void NativeMatrix::Rotation(const TVec2f& value)
{
  D3DXMatrixRotationX(this->mat_, value.x);

  D3DXMATRIX mat;
  D3DXMatrixRotationY(&mat, value.y);
  D3DXMatrixMultiply(this->mat_, &mat, this->mat_);
}

void NativeMatrix::Rotation(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  D3DXMatrixRotationZ(this->mat_, z);

  D3DXMATRIX mat;
  D3DXMatrixRotationX(&mat, x);
  D3DXMatrixMultiply(this->mat_, &mat, this->mat_);
  D3DXMatrixRotationY(&mat, y);
  D3DXMatrixMultiply(this->mat_, &mat, this->mat_);
}

void NativeMatrix::Rotation(const TVec3f& value)
{
  D3DXMatrixRotationZ(this->mat_, value.z);

  D3DXMATRIX mat;
  D3DXMatrixRotationX(&mat, value.x);
  D3DXMatrixMultiply(this->mat_, &mat, this->mat_);
  D3DXMatrixRotationY(&mat, value.y);
  D3DXMatrixMultiply(this->mat_, &mat, this->mat_);
}

void NativeMatrix::RotationX(T_FLOAT x)
{
  D3DXMatrixRotationX(this->mat_, x);
}

void NativeMatrix::RotationY(T_FLOAT y)
{
  D3DXMatrixRotationY(this->mat_, y);
}

void NativeMatrix::RotationZ(T_FLOAT z)
{
  D3DXMatrixRotationZ(this->mat_, z);
}


void NativeMatrix::LookAtLH(const TVec3f& camera_pos, const TVec3f& camera_at, const TVec3f& camera_up)
{
  D3DXMatrixLookAtLH(
    this->mat_,
    &D3DXVECTOR3(camera_pos.x, camera_pos.y, camera_pos.z),
    &D3DXVECTOR3(camera_at.x, camera_at.y, camera_at.z),
    &D3DXVECTOR3(camera_up.x, camera_up.y, camera_up.z)
  );
}

void NativeMatrix::PerspectiveFovLH(T_FLOAT field_of_view_y, T_FLOAT aspect_ratio, T_FLOAT z_near, T_FLOAT z_far)
{
  D3DXMatrixPerspectiveFovLH(
    this->mat_,
    field_of_view_y,
    aspect_ratio,
    z_near,
    z_far
  );
}

void NativeMatrix::OrthoLH(T_FLOAT width, T_FLOAT height, T_FLOAT z_near, T_FLOAT z_far)
{
  D3DXMatrixOrthoLH(
    this->mat_,
    width,
    height,
    z_near,
    z_far
  );
}

void NativeMatrix::Apply(TVec2f* dest) const
{
  const T_FLOAT x = dest->x;
  const T_FLOAT y = dest->y;
  dest->x = (x * this->mat_->_11) + (y * this->mat_->_21) + this->mat_->_41;
  dest->y = (x * this->mat_->_12) + (y * this->mat_->_22) + this->mat_->_42;
}

void NativeMatrix::Apply(TVec3f* dest) const
{
  const T_FLOAT x = dest->x;
  const T_FLOAT y = dest->y;
  const T_FLOAT z = dest->z;
  dest->x = (x * this->mat_->_11) + (y * this->mat_->_21) + (z * this->mat_->_31) + this->mat_->_41;
  dest->y = (x * this->mat_->_12) + (y * this->mat_->_22) + (z * this->mat_->_32) + this->mat_->_42;
  dest->z = (x * this->mat_->_13) + (y * this->mat_->_23) + (z * this->mat_->_33) + this->mat_->_43;
}

void NativeMatrix::Apply(TVec4f* dest) const
{
  const T_FLOAT x = dest->x;
  const T_FLOAT y = dest->y;
  const T_FLOAT z = dest->z;
  const T_FLOAT w = dest->w;
  dest->x = (x * this->mat_->_11) + (y * this->mat_->_21) + (z * this->mat_->_31) + (w * this->mat_->_41);
  dest->y = (x * this->mat_->_12) + (y * this->mat_->_22) + (z * this->mat_->_32) + (w * this->mat_->_42);
  dest->z = (x * this->mat_->_13) + (y * this->mat_->_23) + (z * this->mat_->_33) + (w * this->mat_->_43);
  dest->w = (x * this->mat_->_14) + (y * this->mat_->_24) + (z * this->mat_->_34) + (w * this->mat_->_44);
}

void NativeMatrix::Apply(T_FLOAT* dest_x, T_FLOAT* dest_y) const
{
  const T_FLOAT x = dest_x ? (*dest_x) : 0.0f;
  const T_FLOAT y = dest_y ? (*dest_y) : 0.0f;
  if (dest_x)
  {
    (*dest_x) = (x * this->mat_->_11) + (y * this->mat_->_21) + this->mat_->_41;
  }
  if (dest_y)
  {
    (*dest_y) = (x * this->mat_->_12) + (y * this->mat_->_22) + this->mat_->_42;
  }
}

void NativeMatrix::Apply(T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z) const
{
  const T_FLOAT x = dest_x ? (*dest_x) : 0.0f;
  const T_FLOAT y = dest_y ? (*dest_y) : 0.0f;
  const T_FLOAT z = dest_z ? (*dest_z) : 0.0f;
  if (dest_x)
  {
    (*dest_x) = (x * this->mat_->_11) + (y * this->mat_->_21) + (z * this->mat_->_31) + this->mat_->_41;
  }
  if (dest_y)
  {
    (*dest_y) = (x * this->mat_->_12) + (y * this->mat_->_22) + (z * this->mat_->_32) + this->mat_->_42;
  }
  if (dest_z)
  {
    (*dest_z) = (x * this->mat_->_13) + (y * this->mat_->_23) + (z * this->mat_->_33) + this->mat_->_43;
  }
}

void NativeMatrix::Apply(T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z, T_FLOAT* dest_w) const
{
  const T_FLOAT x = dest_x ? (*dest_x) : 0.0f;
  const T_FLOAT y = dest_y ? (*dest_y) : 0.0f;
  const T_FLOAT z = dest_z ? (*dest_z) : 0.0f;
  const T_FLOAT w = dest_w ? (*dest_w) : 1.0f;
  if (dest_x)
  {
    (*dest_x) = (x * this->mat_->_11) + (y * this->mat_->_21) + (z * this->mat_->_31) + (w * this->mat_->_41);
  }
  if (dest_y)
  {
    (*dest_y) = (x * this->mat_->_12) + (y * this->mat_->_22) + (z * this->mat_->_32) + (w * this->mat_->_42);
  }
  if (dest_z)
  {
    (*dest_z) = (x * this->mat_->_13) + (y * this->mat_->_23) + (z * this->mat_->_33) + (w * this->mat_->_43);
  }
  if (dest_w)
  {
    (*dest_w) = (x * this->mat_->_14) + (y * this->mat_->_24) + (z * this->mat_->_34) + (w * this->mat_->_44);
  }
}

const TVec2f NativeMatrix::GetDirection2d() const
{
  return TVec2f(this->mat_->_31, this->mat_->_32);
}

const TVec3f NativeMatrix::GetDirection3d() const
{
  return TVec3f(this->mat_->_31, this->mat_->_32, this->mat_->_33);
}

const TVec2f NativeMatrix::GetPosition2d() const
{
  return TVec2f(this->mat_->_41, this->mat_->_42);
}

const TVec3f NativeMatrix::GetPosition3d() const
{
  return TVec3f(this->mat_->_41, this->mat_->_42, this->mat_->_43);
}

const TVec4f NativeMatrix::GetPosition4d() const
{
  return TVec4f(this->mat_->_41, this->mat_->_42, this->mat_->_43, this->mat_->_44);
}

const TVec3f NativeMatrix::GetCameraXVec() const
{
  return TVec3f(this->mat_->_11, this->mat_->_12, this->mat_->_13);
}

const TVec3f NativeMatrix::GetCameraYVec() const
{
  return TVec3f(this->mat_->_21, this->mat_->_22, this->mat_->_23);
}

const TVec3f NativeMatrix::GetCameraZVec() const
{
  return TVec3f(this->mat_->_31, this->mat_->_32, this->mat_->_33);
}

const TVec3f NativeMatrix::GetWorldScale() const
{
  TVec3f ret;
  ret.x = TVec3f(this->mat_->_11, this->mat_->_12, this->mat_->_13).Length();
  ret.y = TVec3f(this->mat_->_21, this->mat_->_22, this->mat_->_23).Length();
  ret.z = TVec3f(this->mat_->_31, this->mat_->_32, this->mat_->_33).Length();
  return ret;
}

const T_FLOAT* NativeMatrix::Get(T_UINT8 x) const
{
  return this->mat_->m[x];
}

T_FLOAT* NativeMatrix::Get(T_UINT8 x)
{
  return this->mat_->m[x];
}
