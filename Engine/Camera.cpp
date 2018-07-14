#include "Camera.h"
#include "GameObject.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Camera::Camera(GameObject* entity)
  : GameComponent(entity)
  , target_texture_(nullptr)
{
  this->render_state_ = new RenderState();
}

Camera::~Camera()
{
  delete this->render_state_;
}

// =================================================================
// Method
// =================================================================
void Camera::SetupCamera()
{
  if (!this->IsEnabled())
  {
    this->render_state_->SetEnabled(false);
    return;
  }
  this->render_state_->SetEnabled(true);

  if (this->target_texture_)
  {
    this->render_state_->SetColorBuffer(this->target_texture_->GetColorBuffer());
    this->render_state_->SetDepthStencilBuffer(this->target_texture_->GetDepthBuffer());
  }
  else
  {
    this->render_state_->SetColorBuffer(nullptr);
    this->render_state_->SetDepthStencilBuffer(nullptr);
  }

  this->render_state_->SetViewMatrix(this->GetViewMatrix());
  this->render_state_->SetProjectionMatrix(this->GetProjectionMatrix());
}

// =================================================================
// setter/getter
// =================================================================
const TVec3f Camera::Get2dPositionScale(const GameObject * obj) const
{
  Matrix4x4 ret;
  ret = obj->GetWorldMatrix();
  ret *= this->GetViewMatrix();
  ret *= this->GetProjectionMatrix();
  const TVec4f pos = ret.GetPosition4d();
  return TVec3f(pos.x / pos.w, pos.y / pos.w, pos.z / fabs(pos.w));
}

const TVec3f Camera::Get2dPosition(const GameObject * obj) const
{
  TVec3f ret = this->Get2dPositionScale(obj);
  const Viewport& viewport = this->GetRenderState()->GetViewport();
  ret.x *= viewport.size.width * 0.5f;
  ret.y *= viewport.size.height * 0.5f;
  return ret;
}

const TVec3f Camera::GetRayVector(const TVec2f & screen_position)
{
  Matrix4x4 ret;
  ret.Translation(screen_position);
  ret = this->GetProjectionMatrix() * ret;
  ret = this->GetViewMatrix() * ret;
  return ret.GetPosition3d();
}
