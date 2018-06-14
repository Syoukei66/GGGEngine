#include "NativeMatrix.h"

////平行移動      _41 _42 _43
////スケーリング  _11 _22 _33

// =================================================================
// Constructor / Destructor
// =================================================================
NativeMatrix::NativeMatrix()
{
  this->SetNativeInstance<Matrix4x4>(&this->mat_);
  this->Init();
}

NativeMatrix::NativeMatrix(NativeMatrixInstance* instance)
  : INativeMatrix(instance)
{
  this->mat_ = *GetNativeInstance<Matrix4x4>();
}

NativeMatrix::NativeMatrix(const NativeMatrix& mat)
  : INativeMatrix(mat.GetNativeInstance())
{
  this->mat_ = *GetNativeInstance<Matrix4x4>();
}

NativeMatrix::~NativeMatrix()
{
}
// =================================================================
// Method
// =================================================================
void NativeMatrix::Init()
{
  this->mat_ = this->mat_.identity;
}

void NativeMatrix::Assign(NativeMatrixInstance* mat)
{
  this->mat_ = *((Matrix4x4*)mat);
}

void NativeMatrix::Assign(const INativeMatrix& mat)
{
  this->mat_ = *((Matrix4x4*)mat.GetNativeInstance());
}

void NativeMatrix::Multiple(const INativeMatrix& mat)
{
  this->mat_ *= *((Matrix4x4*)mat.GetNativeInstance());
}

void NativeMatrix::MultipleReverse(const INativeMatrix & mat)
{
  this->mat_ = *((Matrix4x4*)mat.GetNativeInstance()) * this->mat_;
}

void NativeMatrix::Inverse()
{
  this->mat_ = this->mat_.Inverse();
}

void NativeMatrix::Inverse(INativeMatrix* dest) const
{
  *((Matrix4x4*)dest->GetNativeInstance()) = this->mat_.Inverse();
}

void NativeMatrix::Translation(T_FLOAT x, T_FLOAT y)
{
  this->mat_.Translation(x, y);
}

void NativeMatrix::Translation(const TVec2f& value)
{
  this->mat_.Translation(value.x, value.y);
}

void NativeMatrix::Translation(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  this->mat_.Translation(x, y, z);
}

void NativeMatrix::Translation(const TVec3f& value)
{
  this->mat_.Translation(value.x, value.y, value.z);
}

void NativeMatrix::TranslationX(T_FLOAT x)
{
  this->mat_.TranslationX(x);
}

void NativeMatrix::TranslationY(T_FLOAT y)
{
  this->mat_.TranslationY(y);
}

void NativeMatrix::TranslationZ(T_FLOAT z)
{
  this->mat_.TranslationZ(z);
}

void NativeMatrix::Scaling(T_FLOAT value)
{
  this->mat_.Scaling(value);
}

void NativeMatrix::Scaling(T_FLOAT x, T_FLOAT y)
{
  this->mat_.Scaling(x, y);
}

void NativeMatrix::Scaling(const TVec2f& value)
{
  this->mat_.Scaling(value);
}

void NativeMatrix::Scaling(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  this->mat_.Scaling(x, y, z);
}

void NativeMatrix::Scaling(const TVec3f& value)
{
  this->mat_.Scaling(value);
}

void NativeMatrix::ScalingX(T_FLOAT x)
{
  this->mat_.ScalingX(x);
}

void NativeMatrix::ScalingY(T_FLOAT y)
{
  this->mat_.ScalingY(y);
}

void NativeMatrix::ScalingZ(T_FLOAT z)
{
  this->mat_.ScalingZ(z);
}

void NativeMatrix::Rotation(T_FLOAT x, T_FLOAT y)
{
  this->mat_.Rotation(x, y);
}

void NativeMatrix::Rotation(const TVec2f& value)
{
  this->mat_.Rotation(value.x, value.y);
}

void NativeMatrix::Rotation(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  this->mat_.Rotation(x, y, z);
}

void NativeMatrix::Rotation(const TVec3f& value)
{
  this->mat_.Rotation(value.x, value.y, value.z);
}

void NativeMatrix::RotationX(T_FLOAT x)
{
  this->mat_.RotationX(x);
}

void NativeMatrix::RotationY(T_FLOAT y)
{
  this->mat_.RotationY(y);
}

void NativeMatrix::RotationZ(T_FLOAT z)
{
  this->mat_.RotationZ(z);
}

void NativeMatrix::LookAtLH(const TVec3f& camera_pos, const TVec3f& camera_at, const TVec3f& camera_up)
{
  this->mat_.LookAt(camera_pos, camera_at, camera_up);
}

void NativeMatrix::PerspectiveFovLH(T_FLOAT field_of_view_y, T_FLOAT aspect_ratio, T_FLOAT z_near, T_FLOAT z_far)
{
  this->mat_.Perspective(field_of_view_y, aspect_ratio, z_far, z_far);
}

void NativeMatrix::OrthoLH(T_FLOAT width, T_FLOAT height, T_FLOAT z_near, T_FLOAT z_far)
{
  const T_FLOAT x = width * 0.5f;
  const T_FLOAT y = height * 0.5f;
  this->mat_.Ortho(-x, x, -y, y, z_near, z_far);
}

void NativeMatrix::Apply(TVec2f* dest) const
{
  const T_FLOAT x = dest->x;
  const T_FLOAT y = dest->y;
  dest->x = (x * this->mat_._11) + (y * this->mat_._21) + this->mat_._41;
  dest->y = (x * this->mat_._12) + (y * this->mat_._22) + this->mat_._42;
}

void NativeMatrix::Apply(TVec3f* dest) const
{
  const T_FLOAT x = dest->x;
  const T_FLOAT y = dest->y;
  const T_FLOAT z = dest->z;
  dest->x = (x * this->mat_._11) + (y * this->mat_._21) + (z * this->mat_._31) + this->mat_._41;
  dest->y = (x * this->mat_._12) + (y * this->mat_._22) + (z * this->mat_._32) + this->mat_._42;
  dest->z = (x * this->mat_._13) + (y * this->mat_._23) + (z * this->mat_._33) + this->mat_._43;
}

void NativeMatrix::Apply(TVec4f* dest) const
{
  const T_FLOAT x = dest->x;
  const T_FLOAT y = dest->y;
  const T_FLOAT z = dest->z;
  const T_FLOAT w = dest->w;
  dest->x = (x * this->mat_._11) + (y * this->mat_._21) + (z * this->mat_._31) + (w * this->mat_._41);
  dest->y = (x * this->mat_._12) + (y * this->mat_._22) + (z * this->mat_._32) + (w * this->mat_._42);
  dest->z = (x * this->mat_._13) + (y * this->mat_._23) + (z * this->mat_._33) + (w * this->mat_._43);
  dest->w = (x * this->mat_._14) + (y * this->mat_._24) + (z * this->mat_._34) + (w * this->mat_._44);
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

const TVec2f NativeMatrix::GetDirection2d() const
{
  return TVec2f(this->mat_._31, this->mat_._32);
}

const TVec3f NativeMatrix::GetDirection3d() const
{
  return TVec3f(this->mat_._31, this->mat_._32, this->mat_._33);
}

const TVec2f NativeMatrix::GetPosition2d() const
{
  return TVec2f(this->mat_._41, this->mat_._42);
}

const TVec3f NativeMatrix::GetPosition3d() const
{
  return TVec3f(this->mat_._41, this->mat_._42, this->mat_._43);
}

const TVec4f NativeMatrix::GetPosition4d() const
{
  return TVec4f(this->mat_._41, this->mat_._42, this->mat_._43, this->mat_._44);
}

const TVec3f NativeMatrix::GetCameraXVec() const
{
  return TVec3f(this->mat_._11, this->mat_._12, this->mat_._13);
}

const TVec3f NativeMatrix::GetCameraYVec() const
{
  return TVec3f(this->mat_._21, this->mat_._22, this->mat_._23);
}

const TVec3f NativeMatrix::GetCameraZVec() const
{
  return TVec3f(this->mat_._31, this->mat_._32, this->mat_._33);
}

const TVec3f NativeMatrix::GetWorldScale() const
{
  TVec3f ret;
  ret.x = TVec3f(this->mat_._11, this->mat_._12, this->mat_._13).Length();
  ret.y = TVec3f(this->mat_._21, this->mat_._22, this->mat_._23).Length();
  ret.z = TVec3f(this->mat_._31, this->mat_._32, this->mat_._33).Length();
  return ret;
}

const T_FLOAT* NativeMatrix::Get(T_UINT8 x) const
{
  return this->mat_.m[x];
}

T_FLOAT* NativeMatrix::Get(T_UINT8 x)
{
  return this->mat_.m[x];
}
