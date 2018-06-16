#include "Camera.h"
#include "Director.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Camera::Camera(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max)
  : entity_(nullptr)
  , direction_(0.0f, 0.0f, 1.0f)
  , target_texture_(nullptr)
  , viewport_clear_(true)
  , position_(x, y)
  , size_(width, height)
  , z_min_(z_min)
  , z_max_(z_max)
{
}

Camera::Camera()
  : entity_(nullptr)
  , direction_(0.0f, 0.0f, 1.0f)
  , target_texture_(nullptr)
  , viewport_clear_(true)
  , position_(0.0f, 0.0f)
  , size_((T_FLOAT)Director::GetInstance()->GetScreenWidth(), (T_FLOAT)Director::GetInstance()->GetScreenHeight())
  , z_min_(0.0f)
  , z_max_(1.0f)
{
}

Camera::~Camera()
{
  delete this->entity_;
}

// =================================================================
// Method
// =================================================================
void Camera::SetupViewProjMatrix()
{
}

void Camera::DrawScene(Scene* scene)
{
  if (!this->IsEnabled())
  {
    return;
  }
  this->SetupCamera();
  if (this->target_texture_)
  {
    this->target_texture_->RenderBegin();
  }
  if (this->viewport_clear_)
  {
    NativeMethod::Graphics().Graphics_Clear();
  }
  this->OnDrawScene(scene);
  if (this->target_texture_)
  {
    this->target_texture_->RenderEnd();
  }
}

void Camera::SetupCamera()
{
  NativeMethod::Graphics().Graphics_SetViewport(
    this->position_.x,
    this->position_.y,
    this->size_.width,
    this->size_.height,
    this->z_min_,
    this->z_max_
  );
  //NativeMethod::Graphics().Graphics_SetTransformProjection(this->GetProjectionMatrix()->GetNativeInstance());
  //NativeMethod::Graphics().Graphics_SetTransformView(this->GetViewMatrix()->GetNativeInstance());
}

// =================================================================
// setter/getter
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

void Camera::SetViewportSize(const TSizef & size)
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
