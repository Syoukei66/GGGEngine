#include "Camera2D.h"
#include "NativeMethod.h"
#include "Scene.h"

static LP_MATRIX_4x4 VIEW_MATRIX = nullptr;

static void CreateViewMatrix()
{
  if (VIEW_MATRIX)
  {
    return;
  }
  VIEW_MATRIX = NativeMethod::Matrix().Matrix4x4_Create();
}

static void DeleteViewMatrix()
{
  if (!VIEW_MATRIX)
  {
    return;
  }
  NativeMethod::Matrix().Matrix4x4_Delete(VIEW_MATRIX);
}

// =================================================================
// Constructor / Destructor
// =================================================================
Camera2D::Camera2D(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max)
  : Camera(x, y, width, height, z_min, z_max)
{
  this->render_state_ = new GameObject2DRenderState(this);
  this->projection_matrix_ = NativeMethod::Matrix().Matrix4x4_Create();
}

Camera2D::Camera2D()
  : Camera()
{
  this->render_state_ = new GameObject2DRenderState(this);
  this->projection_matrix_ = NativeMethod::Matrix().Matrix4x4_Create();
}

Camera2D::~Camera2D()
{
  delete this->render_state_;
  NativeMethod::Matrix().Matrix4x4_Delete(this->projection_matrix_);
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void Camera2D::DrawScene(Scene* scene)
{
  this->SetupCamera();
  this->render_state_->Init();
  scene->Draw2DLayers(this->render_state_);
}

void Camera2D::OnViewportDirty()
{
  NativeMethod::Matrix().Matrix4x4_OrthoLH(
    this->projection_matrix_,
    this->GetViewportWidth(),
    this->GetViewportHeight(),
    this->GetViewportZMin(),
    this->GetViewportZMax()
  );
}

LP_MATRIX_4x4 Camera2D::GetViewMatrix()
{
  return NativeMethod::Matrix().Matrix4x4_GetIdentity();
}

LP_MATRIX_4x4 Camera2D::GetProjectionMatrix()
{
  this->CheckViewportDirty();
  return this->projection_matrix_;
}
