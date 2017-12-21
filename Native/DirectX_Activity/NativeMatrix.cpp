#include "NativeMatrix.h"

NativeMatrix::NativeMatrix()
{
  this->Init();
}

NativeMatrix::NativeMatrix(NativeMatrixInstance* instance)
{
  this->SetNativeMatrixInstance(instance);
  this->mat_ =  
}

void NativeMatrix::Init()
{
  D3DXMatrixIdentity(&this->mat_);
}

void NativeMatrix::Assign(const INativeMatrix& mat)
{
  D3DXMatrixIdentity(&this->mat_);
  D3DXMatrixMultiply(&this->mat_, &this->mat_, &((const NativeMatrix&)mat).mat_);
}

void NativeMatrix::Multiple(const INativeMatrix& mat)
{
  D3DXMatrixMultiply(&this->mat_, &this->mat_, &((const NativeMatrix&)mat).mat_);
}

void NativeMatrix::Inverse()
{
  D3DXMatrixInverse(&this->mat_, nullptr, &this->mat_);
}

void NativeMatrix::Inverse(INativeMatrix* dest) const
{
  D3DXMatrixInverse(&((NativeMatrix&)dest).mat_, nullptr, &this->mat_);
}

void NativeMatrix::Translation(T_FLOAT x, T_FLOAT y)
{
  D3DXMatrixTranslation(&this->mat_, x, y, 0.0f);
}

void NativeMatrix::Translation(const TVec2f& value)
{
  D3DXMatrixTranslation(&this->mat_, value.x, value.y, 0.0f);
}

void NativeMatrix::Translation(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  D3DXMatrixTranslation(&this->mat_, x, y, z);
}

void NativeMatrix::Translation(const TVec3f& value)
{
  D3DXMatrixTranslation(&this->mat_, value.x, value.y, value.z);
}

void NativeMatrix::TranslationX(T_FLOAT x)
{
  D3DXMatrixTranslation(&this->mat_, x, 0.0f, 0.0f);
}

void NativeMatrix::TranslationY(T_FLOAT y)
{
  D3DXMatrixTranslation(&this->mat_, 0.0f, y, 0.0f);
}

void NativeMatrix::TranslationZ(T_FLOAT z)
{
  D3DXMatrixTranslation(&this->mat_, 0.0f, 0.0f, z);
}

void NativeMatrix::Scaling(T_FLOAT value)
{
  D3DXMatrixScaling(&this->mat_, value, value, value);
}

void NativeMatrix::Scaling(T_FLOAT x, T_FLOAT y)
{
  D3DXMatrixScaling(&this->mat_, x, y, 1.0f);
}

void NativeMatrix::Scaling(const TVec2f& value)
{
  D3DXMatrixScaling(&this->mat_, value.x, value.y, 1.0f);
}

void NativeMatrix::Scaling(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  D3DXMatrixScaling(&this->mat_, x, y, z);
}

void NativeMatrix::Scaling(const TVec3f& value)
{
  D3DXMatrixScaling(&this->mat_, value.x, value.y, value.z);
}

void NativeMatrix::ScalingX(T_FLOAT x)
{
  D3DXMatrixScaling(&this->mat_, x, 1.0f, 1.0f);
}

void NativeMatrix::ScalingY(T_FLOAT y)
{
  D3DXMatrixScaling(&this->mat_, 1.0f, y, 1.0f);
}

void NativeMatrix::ScalingZ(T_FLOAT z)
{
  D3DXMatrixScaling(&this->mat_, 1.0f, 1.0f, z);
}

void NativeMatrix::Rotation(T_FLOAT x, T_FLOAT y)
{
  D3DXMatrixRotationX(&this->mat_, x);

  D3DXMATRIX mat;
  D3DXMatrixRotationY(&mat, y);
  D3DXMatrixMultiply(&this->mat_, &mat, &this->mat_);
}

void NativeMatrix::Rotation(const TVec2f& value)
{
  D3DXMatrixRotationX(&this->mat_, value.x);

  D3DXMATRIX mat;
  D3DXMatrixRotationY(&mat, value.y);
  D3DXMatrixMultiply(&this->mat_, &mat, &this->mat_);
}

void NativeMatrix::Rotation(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  D3DXMatrixRotationZ(&this->mat_, z);

  D3DXMATRIX mat;
  D3DXMatrixRotationX(&mat, x);
  D3DXMatrixMultiply(&this->mat_, &mat, &this->mat_);
  D3DXMatrixRotationY(&mat, y);
  D3DXMatrixMultiply(&this->mat_, &mat, &this->mat_);
}

void NativeMatrix::Rotation(const TVec3f& value)
{
  D3DXMatrixRotationZ(&this->mat_, value.z);

  D3DXMATRIX mat;
  D3DXMatrixRotationX(&mat, value.x);
  D3DXMatrixMultiply(&this->mat_, &mat, &this->mat_);
  D3DXMatrixRotationY(&mat, value.y);
  D3DXMatrixMultiply(&this->mat_, &mat, &this->mat_);
}

void NativeMatrix::RotationX(T_FLOAT x)
{
  D3DXMatrixRotationX(&this->mat_, x);
}

void NativeMatrix::RotationY(T_FLOAT y)
{
  D3DXMatrixRotationY(&this->mat_, y);
}

void NativeMatrix::RotationZ(T_FLOAT z)
{
  D3DXMatrixRotationZ(&this->mat_, z);
}

void NativeMatrix::Apply(TVec2f* dest) const
{
  dest->x = (dest->x * this->mat_._11) + (dest->y * this->mat_._21) + this->mat_._41;
  dest->y = (dest->x * this->mat_._12) + (dest->y * this->mat_._22) + this->mat_._42;
}

void NativeMatrix::Apply(TVec3f* dest) const
{
  dest->x = (dest->x * this->mat_._11) + (dest->y * this->mat_._21) + (dest->z * this->mat_._31) + this->mat_._41;
  dest->y = (dest->x * this->mat_._12) + (dest->y * this->mat_._22) + (dest->z * this->mat_._32) + this->mat_._42;
  dest->z = (dest->x * this->mat_._13) + (dest->y * this->mat_._23) + (dest->z * this->mat_._33) + this->mat_._43;
}

void NativeMatrix::Apply(TVec4f* dest) const
{
  dest->x = (dest->x * this->mat_._11) + (dest->y * this->mat_._21) + (dest->z * this->mat_._31) + (dest->w * this->mat_._41);
  dest->y = (dest->x * this->mat_._12) + (dest->y * this->mat_._22) + (dest->z * this->mat_._32) + (dest->w * this->mat_._42);
  dest->z = (dest->x * this->mat_._13) + (dest->y * this->mat_._23) + (dest->z * this->mat_._33) + (dest->w * this->mat_._43);
  dest->w = (dest->x * this->mat_._14) + (dest->y * this->mat_._24) + (dest->z * this->mat_._34) + (dest->w * this->mat_._44);
}

void NativeMatrix::Apply(T_FLOAT* dest_x, T_FLOAT* dest_y) const
{
  const T_FLOAT x = dest_x ? (*dest_x) : 0.0f;
  const T_FLOAT y = dest_y ? (*dest_y) : 0.0f;
  if (dest_x)
  {
    (*dest_x) = (x * this->mat_._11) + (y * this->mat_._21) + this->mat_._41;
  }
  if (dest_y)
  {
    (*dest_y) = (x * this->mat_._12) + (y * this->mat_._22) + this->mat_._42;
  }
}

void NativeMatrix::Apply(T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z) const
{
  const T_FLOAT x = dest_x ? (*dest_x) : 0.0f;
  const T_FLOAT y = dest_y ? (*dest_y) : 0.0f;
  const T_FLOAT z = dest_z ? (*dest_z) : 0.0f;
  if (dest_x)
  {
    (*dest_x) = (x * this->mat_._11) + (y * this->mat_._21) + (z * this->mat_._31) + this->mat_._41;
  }
  if (dest_y)
  {
    (*dest_y) = (x * this->mat_._12) + (y * this->mat_._22) + (z * this->mat_._32) + this->mat_._42;
  }
  if (dest_z)
  {
    (*dest_z) = (x * this->mat_._13) + (y * this->mat_._23) + (z * this->mat_._33) + this->mat_._43;
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
    (*dest_x) = (x * this->mat_._11) + (y * this->mat_._21) + (z * this->mat_._31) + (w * this->mat_._41);
  }
  if (dest_y)
  {
    (*dest_y) = (x * this->mat_._12) + (y * this->mat_._22) + (z * this->mat_._32) + (w * this->mat_._42);
  }
  if (dest_z)
  {
    (*dest_z) = (x * this->mat_._13) + (y * this->mat_._23) + (z * this->mat_._33) + (w * this->mat_._43);
  }
  if (dest_w)
  {
    (*dest_w) = (x * this->mat_._14) + (y * this->mat_._24) + (z * this->mat_._34) + (w * this->mat_._44);
  }
}

void NativeMatrix::Direction(TVec2f* dest) const
{
  dest->x = this->mat_._31;
  dest->y = this->mat_._32;
}

void NativeMatrix::Direction(TVec3f* dest) const
{
  dest->x = this->mat_._31;
  dest->y = this->mat_._32;
  dest->z = this->mat_._33;
}

void NativeMatrix::LookAtLH(const TVec3f& camera_pos, const TVec3f& camera_at, const TVec3f& camera_up)
{
  D3DXMatrixLookAtLH(
    &this->mat_,
    &D3DXVECTOR3(camera_pos.x, camera_pos.y, camera_pos.z),
    &D3DXVECTOR3(camera_at.x, camera_at.y, camera_at.z),
    &D3DXVECTOR3(camera_up.x, camera_up.y, camera_up.z)
  );
}

void NativeMatrix::PerspectiveFovLH(T_FLOAT field_of_view_y, T_FLOAT aspect_ratio, T_FLOAT z_near, T_FLOAT z_far)
{
  D3DXMatrixPerspectiveFovLH(
    &this->mat_,
    field_of_view_y,
    aspect_ratio,
    z_near,
    z_far
  );
}

void NativeMatrix::OrthoLH(T_FLOAT width, T_FLOAT height, T_FLOAT z_near, T_FLOAT z_far)
{
  D3DXMatrixOrthoLH(
    &this->mat_,
    width,
    height,
    z_near,
    z_far
  );
}

const T_FLOAT* NativeMatrix::Get(T_UINT8 x) const
{
  return this->mat_.m[x];
}

T_FLOAT* NativeMatrix::Get(T_UINT8 x)
{
  return this->mat_.m[x];
}
