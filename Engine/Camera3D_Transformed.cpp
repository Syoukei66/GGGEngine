#include "Camera3D_Transformed.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Camera3D_Transformed::Camera3D_Transformed(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max)
  : Camera3D(x, y, width, height, z_min, z_max)
{
  this->entity_ = new GameObject3D();
  this->inv_ = NativeMethod::Matrix().Matrix4x4_Create();
}

Camera3D_Transformed::Camera3D_Transformed()
  : Camera3D()
{
  this->entity_ = new GameObject3D();
  this->inv_ = NativeMethod::Matrix().Matrix4x4_Create();
}

Camera3D_Transformed::~Camera3D_Transformed()
{
  delete this->entity_;
  NativeMethod::Matrix().Matrix4x4_Delete(this->inv_);
}

// =================================================================
// Methods
// =================================================================
void Camera3D_Transformed::Move(TVec3f value)
{
  NativeMethod::Matrix().Matrix4x4_Inverse(this->inv_, this->GetTransform()->GetRotationMatrix());
  NativeMethod::Matrix().Matrix4x4_Apply(this->inv_, &value.x, &value.y, &value.z);
  const TVec3f& pos = this->GetTransform()->GetPosition();
  this->GetTransform()->SetPosition(pos.x + value.x, pos.y + value.y, pos.z + value.z);
}

void Camera3D_Transformed::Move(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  NativeMethod::Matrix().Matrix4x4_Inverse(this->inv_, this->GetTransform()->GetRotationMatrix());
  NativeMethod::Matrix().Matrix4x4_Apply(this->inv_, &x, &y, &z);
  const TVec3f& pos = this->GetTransform()->GetPosition();
  this->GetTransform()->SetPosition(pos.x + x, pos.y + y, pos.z + z);
}

void Camera3D_Transformed::MoveX(T_FLOAT x)
{
  NativeMethod::Matrix().Matrix4x4_Inverse(this->inv_, this->GetTransform()->GetRotationMatrix());
  NativeMethod::Matrix().Matrix4x4_Apply(this->inv_, &x, nullptr, nullptr);
  this->GetTransform()->SetX(this->GetTransform()->GetX() + x);
}

void Camera3D_Transformed::MoveY(T_FLOAT y)
{
  NativeMethod::Matrix().Matrix4x4_Inverse(this->inv_, this->GetTransform()->GetRotationMatrix());
  NativeMethod::Matrix().Matrix4x4_Apply(this->inv_, &y, nullptr, nullptr);
  this->GetTransform()->SetY(this->GetTransform()->GetY() + y);
}

void Camera3D_Transformed::MoveZ(T_FLOAT z)
{
  NativeMethod::Matrix().Matrix4x4_Inverse(this->inv_, this->GetTransform()->GetRotationMatrix());
  NativeMethod::Matrix().Matrix4x4_Apply(this->inv_, &z, nullptr, nullptr);
  this->GetTransform()->SetZ(this->GetTransform()->GetZ() + z);
}

void Camera3D_Transformed::RotateXAxis(T_FLOAT x_axis)
{
  this->GetTransform()->GetRotator()->RotateXAxis(x_axis);
}

void Camera3D_Transformed::RotateYAxis(T_FLOAT y_axis)
{
  this->GetTransform()->GetRotator()->RotateYAxis(y_axis);
}

void Camera3D_Transformed::RotateZAxis(T_FLOAT z_axis)
{
  this->GetTransform()->GetRotator()->RotateYAxis(z_axis);
}
