#include "Camera2D.h"
#include "NativeMethod.h"
#include "Scene.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Camera2D::Camera2D(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max)
  : Camera(x, y, width, height, z_min, z_max)
{
  this->render_state_ = new GameObject2DRenderState(this);
  this->projection_matrix_ = INativeMatrix::Create();
}

Camera2D::Camera2D()
  : Camera()
{
  this->render_state_ = new GameObject2DRenderState(this);
  this->projection_matrix_ = INativeMatrix::Create();
}

Camera2D::~Camera2D()
{
  delete this->render_state_;
  delete this->projection_matrix_;
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
const INativeMatrix* Camera2D::GetViewMatrix()
{
  return &INativeMatrix::Identity();
}

const INativeMatrix* Camera2D::GetProjectionMatrix()
{
  this->CheckViewportDirty();
  return this->projection_matrix_;
}

void Camera2D::OnDrawScene(Scene* scene)
{
  this->render_state_->Init();
  scene->Draw2DLayers(this->render_state_);
}

void Camera2D::OnViewportDirty()
{
  this->projection_matrix_->OrthoLH(
    this->GetViewportWidth(),
    this->GetViewportHeight(),
    0.0f,
    2.15f
  );
}

