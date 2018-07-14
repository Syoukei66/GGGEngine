#include "Camera3D.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Camera3D::Camera3D(GameObject* entity)
  : Camera(entity)
  , billboarding_matrix_()
  , projection_matrix_()
  , fov_(3.0f)
  , z_near_(0.3f)
  , z_far_(1000.0f)
  , projection_dirty_(true)
{
}

Camera3D::~Camera3D()
{
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
const Matrix4x4& Camera3D::GetViewMatrix() const
{
  return Matrix4x4::identity;
}

const Matrix4x4& Camera3D::GetProjectionMatrix() const
{
  const_cast<Camera3D*>(this)->CheckProjectionDirty();
  return this->projection_matrix_;
}

void Camera3D::SetupCamera()
{
  this->billboarding_matrix_ = this->GetViewMatrix().Inverse();

  this->billboarding_matrix_._41 = 0.0f;
  this->billboarding_matrix_._42 = 0.0f;
  this->billboarding_matrix_._43 = 0.0f;
  Camera::SetupCamera();
}

// =================================================================
// Method
// =================================================================
void Camera3D::CheckProjectionDirty()
{
  if (!this->projection_dirty_)
  {
    return;
  }
  const Viewport& viewport = this->GetRenderState()->GetViewport();
  this->projection_matrix_ = Matrix4x4::Perspective(
    MathConstants::PI / this->fov_,
    (T_FLOAT)viewport.size.width / viewport.size.height,
    this->z_near_,
    this->z_far_
  );
  this->projection_dirty_ = false;
}

// =================================================================
// setter/getter
// =================================================================
void Camera3D::SetFov(T_FLOAT fov)
{
  if (this->fov_ == fov)
  {
    return;
  }
  this->fov_ = fov;
  this->OnProjectionChanged();
}

void Camera3D::SetZNear(T_FLOAT z_near)
{
  if (this->z_near_ == z_near)
  {
    return;
  }
  this->z_near_ = z_near;
  this->OnProjectionChanged();
}

void Camera3D::SetZFar(T_FLOAT z_far)
{
  if (this->z_far_ == z_far)
  {
    return;
  }
  this->z_far_ = z_far;
  this->OnProjectionChanged();
}
