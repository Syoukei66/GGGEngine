#include "NativeMatrix.h"
#include "NativeMethod.h"

// =================================================================
// Static Method
// =================================================================
const NativeMatrix& NativeMatrix::Identity()
{
  return NativeMethod::Matrix().Matrix4x4_GetIdentity();
}

// =================================================================
// Constructor / Destructor
// =================================================================
NativeMatrix::NativeMatrix()
{
}

NativeMatrix::NativeMatrix(const NativeMatrix& mat)
{
}

NativeMatrix::~NativeMatrix()
{
}

// =================================================================
// Operator
// =================================================================
NativeMatrix& NativeMatrix::operator=(const NativeMatrix& mat)
{
  // TODO: return ステートメントをここに挿入します
}

NativeMatrix& NativeMatrix::operator*=(const NativeMatrix& mat)
{
  // TODO: return ステートメントをここに挿入します
}

const T_FLOAT* NativeMatrix::operator[](T_UINT8 x) const
{
  return nullptr;
}

T_FLOAT* NativeMatrix::operator[](T_UINT8 x)
{
  return nullptr;
}

// =================================================================
// Method
// =================================================================
void NativeMatrix::Init()
{
}

void NativeMatrix::Assign(const NativeMatrix& mat)
{
}

void NativeMatrix::Multiple(const NativeMatrix& mat)
{
}

void NativeMatrix::Translation(T_FLOAT x, T_FLOAT y)
{
}

void NativeMatrix::Translation(const TVec2f& value)
{
}

void NativeMatrix::Translation(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
}

void NativeMatrix::Translation(const TVec3f& value)
{
}

void NativeMatrix::TranslationX(T_FLOAT x)
{
}

void NativeMatrix::TranslationY(T_FLOAT y)
{
}

void NativeMatrix::TranslationZ(T_FLOAT z)
{
}

void NativeMatrix::Scaling(T_FLOAT value)
{
}

void NativeMatrix::Scaling(T_FLOAT x, T_FLOAT y)
{
}

void NativeMatrix::Scaling(const TVec2f& value)
{
}

void NativeMatrix::Scaling(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
}

void NativeMatrix::Scaling(const TVec3f& value)
{
}

void NativeMatrix::ScalingX(T_FLOAT x)
{
}

void NativeMatrix::ScalingY(T_FLOAT y)
{
}

void NativeMatrix::ScalingZ(T_FLOAT z)
{
}

void NativeMatrix::Rotation(T_FLOAT x, T_FLOAT y)
{
}

void NativeMatrix::Rotation(const TVec2f& value)
{
}

void NativeMatrix::Rotation(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
}

void NativeMatrix::Rotation(const TVec3f& value)
{
}

void NativeMatrix::RotationX(T_FLOAT x)
{
}

void NativeMatrix::RotationY(T_FLOAT y)
{
}

void NativeMatrix::RotationZ(T_FLOAT z)
{
}

void NativeMatrix::Apply(TVec2f* dest) const
{
}

void NativeMatrix::Apply(TVec3f* dest) const
{
}

void NativeMatrix::Apply(TVec4f* dest) const
{
}

void NativeMatrix::Apply(T_FLOAT* dest_x, T_FLOAT* dest_y) const
{
}

void NativeMatrix::Apply(T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z) const
{
}

void NativeMatrix::Apply(T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z, T_FLOAT* dest_w) const
{
}

void NativeMatrix::Direction(TVec2f* dest) const
{
}

void NativeMatrix::Direction(TVec3f* dest) const
{
}

void NativeMatrix::LookAtLH(const TVec3f& camera_pos, const TVec3f& camera_at, const TVec3f& camera_up)
{
}

void NativeMatrix::PerspectiveFovLH(T_FLOAT field_of_view_y, T_FLOAT aspect_ratio, T_FLOAT z_near, T_FLOAT z_far)
{
}

void NativeMatrix::OrthoLH(T_FLOAT width, T_FLOAT height, T_FLOAT z_near, T_FLOAT z_far)
{
}
