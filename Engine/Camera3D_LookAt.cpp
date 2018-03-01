#include "Camera3D_LookAt.h"
#include "NativeMethod.h"
#include "MathConstants.h"
#include "Director.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Camera3D_LookAt::Camera3D_LookAt(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max)
  : Camera3D(x, y, width, height, z_min, z_max)
  , view_matrix_(INativeMatrix::Create())
  , look_at_pos_(0.0f, 0.0f, 1.0f)
  , current_look_at_pos_(0.0f, 0.0f, 1.0f)
  , target_(nullptr)
  , target_lerp_t_(0.5f)
  , target_direction_(0.0f, 0.0f, 1.0f)
  , view_dirty_(true)
{
}

Camera3D_LookAt::Camera3D_LookAt()
  : Camera3D()
  , view_matrix_(INativeMatrix::Create())
  , look_at_pos_(0.0f, 0.0f, 1.0f)
  , current_look_at_pos_(0.0f, 0.0f, 1.0f)
  , target_(nullptr)
  , target_lerp_t_(0.5f)
  , target_direction_(0.0f, 0.0f, 1.0f)
  , view_dirty_(true)
{
}

Camera3D_LookAt::~Camera3D_LookAt()
{
  delete this->view_matrix_;
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
INativeMatrix* Camera3D_LookAt::GetViewMatrix() const
{
  const_cast<Camera3D_LookAt*>(this)->CheckViewDirty();
  return this->view_matrix_;
}

void Camera3D_LookAt::SetupCamera()
{
  this->OnViewChanged();
  Camera3D::SetupCamera();
}

// =================================================================
// Methods
// =================================================================
void Camera3D_LookAt::CheckViewDirty()
{
  if (!this->view_dirty_)
  {
    return;
  }

  this->view_matrix_->Init();
  if (this->target_)
  {
    GameObject3D* player = ((GameObject3D*)this->entity_)->GetParent();
    if (player)
    {
      TVec3f camera_pos = player->GetTransform()->GetWorldPosition();
      this->direction_ = (this->current_look_at_pos_ - player->GetTransform()->GetWorldPosition()).Normalized();
      camera_pos -= this->direction_ * this->GetTransform()->GetPosition().Length();
      camera_pos.y = std::max(camera_pos.y, player->GetTransform()->GetY());
      this->view_matrix_->LookAtLH(
        camera_pos,
        this->current_look_at_pos_,
        this->GetEntity()->GetWorldMatrix().GetCameraYVec()
      );
    }
    else
    {
      TVec3f camera_pos = this->GetTransform()->GetWorldPosition();
      this->direction_ = (this->current_look_at_pos_ - camera_pos).Normalized();
      this->view_matrix_->LookAtLH(
        camera_pos,
        this->current_look_at_pos_,
        this->GetEntity()->GetWorldMatrix().GetCameraYVec()
      );
    }
  }
  //ターゲットが存在しない時の処理
  else
  {
    GameObject3D* player = ((GameObject3D*)this->entity_)->GetParent();
    if (player)
    {
      this->current_look_at_pos_ = this->look_at_pos_;

      const TVec3f camera_pos = this->GetEntity()->GetWorldMatrix().GetPosition3d();
      TVec3f look_at_pos = this->look_at_pos_;
      this->GetEntity()->GetWorldMatrix().Apply(&look_at_pos);
      this->direction_ = (look_at_pos - camera_pos).Normalized();
      this->view_matrix_->LookAtLH(
        camera_pos,
        look_at_pos,
        this->GetEntity()->GetWorldMatrix().GetCameraYVec()
      );
    }
    //プレイヤーが存在しない時の処理
    else
    {
      this->view_matrix_->Assign(this->GetEntity()->GetWorldMatrix());
      this->direction_ = this->view_matrix_->GetDirection3d();
    }
  }

  this->view_dirty_ = false;
}

void Camera3D_LookAt::SetPlayer(GameObject3D* player)
{
  if (((GameObject3D*)this->entity_)->HasParent())
  {
    ((GameObject3D*)this->entity_)->RemoveSelf();
  }
  player->AddChild(((GameObject3D*)this->entity_));
}

void Camera3D_LookAt::Update()
{
  if (this->target_)
  {
    this->current_look_at_pos_ = TVec3f::Lerp(this->current_look_at_pos_, this->target_->GetTransform()->GetWorldPosition(), this->target_lerp_t_);
  }
}

// =================================================================
// setter/getter
// =================================================================
void Camera3D_LookAt::SetLookAtPos(const TVec3f& look_at_pos)
{
  if (this->look_at_pos_ == look_at_pos)
  {
    return;
  }
  this->look_at_pos_ = look_at_pos;
  this->OnViewChanged();
}

void Camera3D_LookAt::SetLookAtPos(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  if (
    this->look_at_pos_.x == x &&
    this->look_at_pos_.y == y &&
    this->look_at_pos_.z == z
    )
  {
    return;
  }
  this->look_at_pos_.x = x;
  this->look_at_pos_.y = y;
  this->look_at_pos_.z = z;
  this->OnViewChanged();
}

void Camera3D_LookAt::SetLookAtPosX(T_FLOAT x)
{
  if (this->look_at_pos_.x == x)
  {
    return;
  }
  this->look_at_pos_.x = x;
  this->OnViewChanged();
}

void Camera3D_LookAt::SetLookAtPosY(T_FLOAT y)
{
  if (this->look_at_pos_.y == y)
  {
    return;
  }
  this->look_at_pos_.y = y;
  this->OnViewChanged();
}

void Camera3D_LookAt::SetLookAtPosZ(T_FLOAT z)
{
  if (this->look_at_pos_.z == z)
  {
    return;
  }
  this->look_at_pos_.z = z;
  this->OnViewChanged();
}