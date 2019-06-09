#include "Camera2D.h"

#include <Engine/GameObject/GameObjectRenderState.h>
#include <Engine/Component/Collider/Collision2D.h>
#include <Engine/Scene/Scene.h>

// =================================================================
// GGG Statement
// =================================================================
GG_CREATE_FUNC_IMPL_1(Camera2D, GameObject*, obj)
{
  return Camera::Init(obj);
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
bool Camera2D::FrustumCulling(const TVec3f& positive, const TVec3f& negative, T_INT8* first_index) const
{
  //return Collision2D::Rect(
  //  positive.x, positive.y, negative.x - positive.x, negative.y - positive.y,
  //  this->GetViewportX(), this->GetViewportY(), this->GetViewportWidth(), this->GetViewportHeight()
  //);
  return false;
}

void Camera2D::UpdateViewMatrix()
{
  this->view_matrix_ = this->GetTransform()->GetWorldMatrix().Inverse();
}

void Camera2D::UpdateProjectionMatrix()
{
  this->projection_matrix_ = Matrix4x4::Ortho(
    this->GetViewportWidth(),
    this->GetViewportHeight(),
    0.0f,
    1000.0f
  );
}
