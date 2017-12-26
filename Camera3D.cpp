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
  , direction_(0.0f, 0.0f, 1.0f)
{
  this->projection_matrix_ = INativeMatrix::Create();
  this->render_state_ = new GameObject3DRenderState(this);
}

Camera3D::Camera3D()
  : Camera()
  , fov_(3.0f)
  , z_near_(0.01f)
  , z_far_(1000.0f)
  , projection_dirty_(true)
  , direction_(0.0f, 0.0f, 1.0f)
{
  this->projection_matrix_ = INativeMatrix::Create();
  this->render_state_ = new GameObject3DRenderState(this);
}

Camera3D::~Camera3D()
{
  delete this->projection_matrix_;
  delete this->render_state_;
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void Camera3D::DrawScene(Scene* scene)
{
  this->SetupCamera();
  this->render_state_->Init();
  scene->Draw3DLayers(this->render_state_);
  this->render_state_->DrawZOrderedGameObject();
}

const INativeMatrix* Camera3D::GetViewMatrix()
{
  return &INativeMatrix::Identity();
}

const INativeMatrix* Camera3D::GetProjectionMatrix()
{
  this->CheckProjectionDirty();
  return this->projection_matrix_;
}

void Camera3D::OnViewportDirty()
{
  this->projection_dirty_ = true;
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
  this->OnProjectionChanged();
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
