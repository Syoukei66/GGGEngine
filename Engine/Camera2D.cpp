#include "Camera2D.h"
#include "NativeMethod.h"
#include "Scene.h"
#include "GameObjectRenderState.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Camera2D::Camera2D(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max)
  : Camera(x, y, width, height, z_min, z_max)
  , projection_dirty_(true)
{
  this->entity_ = new GameObject2D();
  this->render_state_ = new GameObjectRenderState(this);
  this->projection_matrix_ = INativeMatrix::Create();
}

Camera2D::Camera2D()
  : Camera()
  , projection_dirty_(true)
{
  this->entity_ = new GameObject2D();
  this->render_state_ = new GameObjectRenderState(this);
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
const INativeMatrix* Camera2D::GetViewMatrix() const 
{
  return &INativeMatrix::Identity();
}

const INativeMatrix* Camera2D::GetProjectionMatrix() const
{
  if (this->projection_dirty_)
  {
    Camera2D* const this_ = const_cast<Camera2D*>(this);
    this_->projection_matrix_->OrthoLH(
      this->GetViewportWidth(),
      this->GetViewportHeight(),
      0.0f,
      1000.0f
    );
    this_->projection_dirty_ = false;
  }
  return this->projection_matrix_;
}

void Camera2D::OnViewportChanged()
{
  this->projection_dirty_ = true;
}

void Camera2D::OnDrawScene(Scene* scene)
{
  this->render_state_->Init();
  scene->Draw2DLayers(this->render_state_);
}

