#include "Camera.h"

#include <Engine/GameObject/GameObjectRenderState.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(Camera, GameObject* obj)
{
  this->direction_ = TVec3f::forward;
  this->viewport_clear_ = true;
  this->size_ = Application::GetMainActivity()->GetContext()->GetScreenSize();
  this->z_min_ = 0.0f;
  this->z_max_ = 1.0f;
  this->render_state_ = new GameObjectRenderState(this);
  this->bg_color_ = TColor::BLACK;
  return GameComponent::Init(obj);
}

GG_DESTRUCT_FUNC_IMPL(Camera)
{
  delete this->render_state_;
  return true;
}

// =================================================================
// Methods
// =================================================================
void Camera::DrawScene(Scene* scene)
{
  if (!this->IsEnabled())
  {
    return;
  }
  //if (this->target_texture_)
  //{
  //  this->target_texture_->RenderBegin();
  //}
  this->SetupCamera();
  if (this->viewport_clear_)
  {
    //Application::GetPlatform()->GetGraphicsAPI()->ViewportClear(this->bg_color_);
  }
  this->OnDrawScene(scene);
  //if (this->target_texture_)
  //{
  //  this->target_texture_->RenderEnd();
  //}
}

void Camera::SetupCamera()
{
  Application::GetPlatform()->Platform::GetGraphicsAPI()->SetViewport(
    this->position_.x,
    this->position_.y,
    this->size_.width,
    this->size_.height,
    this->z_min_,
    this->z_max_
  );
}

// =================================================================
// Setter / Getter
// =================================================================
void Camera::SetViewportPosition(const TVec2f& position)
{
  if (this->position_ == position)
  {
    return;
  }
  this->position_ = position;
  this->OnViewportChanged();
}

void Camera::SetViewportPosition(T_FLOAT x, T_FLOAT y)
{
  if (this->position_.x == x && this->position_.y == y)
  {
    return;
  }
  this->position_.x = x;
  this->position_.y = y;
  this->OnViewportChanged();
}

void Camera::SetViewportX(T_FLOAT x)
{
  if (this->position_.x == x)
  {
    return;
  }
  this->position_.x = x;
  this->OnViewportChanged();
}

void Camera::SetViewportY(T_FLOAT y)
{
  if (this->position_.y == y)
  {
    return;
  }
  this->position_.y = y;
  this->OnViewportChanged();
}

void Camera::SetViewportSize(const TVec2f& size)
{
  if (this->size_ == size)
  {
    return;
  }
  this->size_ = size;
  this->OnViewportChanged();
}

void Camera::SetViewportSize(T_FLOAT width, T_FLOAT height)
{
  if (this->size_.width == width && this->size_.height == height)
  {
    return;
  }
  this->size_.width = width;
  this->size_.height = height;
  this->OnViewportChanged();
}

void Camera::SetViewportWidth(T_FLOAT width)
{
  if (this->size_.width == width)
  {
    return;
  }
  this->size_.width = width;
  this->OnViewportChanged();
}

void Camera::SetViewportHeight(T_FLOAT height)
{
  if (this->size_.height == height)
  {
    return;
  }
  this->size_.height = height;
  this->OnViewportChanged();
}

void Camera::SetViewportZRange(T_FLOAT z_min, T_FLOAT z_max)
{
  if (this->z_min_ == z_min && this->z_max_ == z_max)
  {
    return;
  }
  this->z_min_ = z_min;
  this->z_max_ = z_max;
  this->OnViewportChanged();
}

void Camera::SetViewportZMin(T_FLOAT z_min)
{
  if (this->z_min_ == z_min)
  {
    return;
  }
  this->z_min_ = z_min;
  this->OnViewportChanged();
}

void Camera::SetViewportZMax(T_FLOAT z_max)
{
  if (this->z_max_ == z_max)
  {
    return;
  }
  this->z_max_ = z_max;
  this->OnViewportChanged();
}
