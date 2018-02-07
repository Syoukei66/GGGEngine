#include "Camera3D.h"
#include "MathConstants.h"
#include "NativeMethod.h"
#include "Scene.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Camera3D::Camera3D(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max)
  : Camera(x, y, width, height, z_min, z_max)
  , fov_(3.0f)
  , z_near_(0.01f)
  , z_far_(1000.0f)
  , projection_dirty_(true)
{
  this->entity_ = new GameObject3D();
  this->projection_matrix_ = INativeMatrix::Create();
  this->billboarding_matrix_ = INativeMatrix::Create();
  this->render_state_ = new GameObjectRenderState(this);
}

Camera3D::Camera3D()
  : Camera()
  , fov_(3.0f)
  , z_near_(0.01f)
  , z_far_(1000.0f)
  , projection_dirty_(true)
{
  this->entity_ = new GameObject3D();
  this->projection_matrix_ = INativeMatrix::Create();
  this->billboarding_matrix_ = INativeMatrix::Create();
  this->render_state_ = new GameObjectRenderState(this);
}

Camera3D::~Camera3D()
{
  delete this->billboarding_matrix_;
  delete this->projection_matrix_;
  delete this->render_state_;
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
const INativeMatrix* Camera3D::GetViewMatrix() const 
{
  return &INativeMatrix::Identity();
}

const INativeMatrix* Camera3D::GetProjectionMatrix() const
{
  const_cast<Camera3D*>(this)->CheckProjectionDirty();
  return this->projection_matrix_;
}

void Camera3D::SetupCamera()
{
  Camera::SetupCamera();
  this->GetViewMatrix()->Inverse(this->billboarding_matrix_);

  (*this->billboarding_matrix_)[3][0] = 0.0f;
  (*this->billboarding_matrix_)[3][1] = 0.0f;
  (*this->billboarding_matrix_)[3][2] = 0.0f;
}

void Camera3D::OnViewportChanged()
{
  this->OnProjectionChanged();
}

void Camera3D::OnDrawScene(Scene* scene)
{
  this->render_state_->Init();
  scene->Draw3DLayers(this->render_state_);
  this->render_state_->DrawZOrderedGameObject();
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
  this->projection_matrix_->PerspectiveFovLH(
    MathConstants::PI / this->fov_,
    this->GetViewportWidth() / this->GetViewportHeight(),
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
