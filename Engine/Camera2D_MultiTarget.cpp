#include "Camera2D_MultiTarget.h"
#include <algorithm>

#include "Director.h"
#include "NativeMethod.h"
#include "GameObject2D.h"

static const T_FLOAT ZOOM_RATE = 0.8f;

// =================================================================
// Constructor / Destructor
// =================================================================
Camera2D_MultiTarget::Camera2D_MultiTarget(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max)
  : Camera2D(x, y, width, height, z_min, z_max)
  , view_(nullptr)
  , target_entities_()
  , zoom_(1.0f)
  , next_zoom_(1.0f)
  , padding_(0.0f)
{
  this->translate_ = INativeMatrix::Create();
  this->scale_ = INativeMatrix::Create();
  this->view_matrix_ = INativeMatrix::Create();
}

Camera2D_MultiTarget::Camera2D_MultiTarget()
  : Camera2D()
  , view_(nullptr)
  , target_entities_()
  , zoom_(1.0f)
  , next_zoom_(1.0f)
  , padding_(0.0f)
{
  this->translate_ = INativeMatrix::Create();
  this->scale_ = INativeMatrix::Create();
  this->view_matrix_ = INativeMatrix::Create();
}

Camera2D_MultiTarget::~Camera2D_MultiTarget()
{
  delete this->translate_;
  delete this->scale_;
  delete this->view_matrix_;
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void Camera2D_MultiTarget::Update()
{
  if (this->zoom_ != this->next_zoom_)
  {
    this->zoom_ += (this->next_zoom_ - this->zoom_) * ZOOM_RATE;
    this->OnUpdateZoom();
  }
  if (!this->view_ || this->target_entities_.size() == 0)
  {
    return;
  }
  TVec2f min(100000.0f, 100000.0f);
  TVec2f max(-100000.0f, -100000.0f);
  for (GameObject2D* target : this->target_entities_)
  {
    TVec2f target_world = target->GetTransform()->GetWorldPosition() - this->view_->GetTransform()->GetWorldPosition();
    min.x = std::min(min.x, target_world.x);
    min.y = std::min(min.y, target_world.y);
    max.x = std::max(max.x, target_world.x);
    max.y = std::max(max.y, target_world.y);
  }
  T_FLOAT width = max.x - min.x;
  T_FLOAT height = max.y - min.y;
  const T_FLOAT center_x = width * 0.5f;
  const T_FLOAT center_y = height * 0.5f;
  width += this->padding_ * 2;
  height += this->padding_ * 2;
  const TSize& screen_size = Director::GetInstance()->GetScreenSize();
  if (width > screen_size.width || height > screen_size.height)
  {
    this->SetZoom(std::min(screen_size.width / width, screen_size.height / height));
  }
  else
  {
    this->SetZoom(1.0f);
  }
  this->position_.x = -(min.x + center_x) * this->zoom_;
  this->position_.y = -(min.y + center_y) * this->zoom_;
  return;
}

INativeMatrix* Camera2D_MultiTarget::GetViewMatrix() const
{
  return this->view_matrix_;
}

// =================================================================
// Method
// =================================================================
void Camera2D_MultiTarget::SetViewEntity(GameObject2D* view_)
{
  this->view_ = view_;
}

void Camera2D_MultiTarget::OnUpdateZoom()
{
  this->scale_->Scaling(this->zoom_, this->zoom_, 1.0f);
  this->translate_->Translation(this->position_);

  this->view_matrix_->Init();
  this->view_matrix_->Multiple(*this->scale_);
  this->view_matrix_->Multiple(*this->translate_);
}
