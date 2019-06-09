#include "Camera3D_LookAt.h"

// =================================================================
// GGG Statement
// =================================================================
GG_CREATE_FUNC_IMPL_1(Camera3D_LookAt, GameObject*, obj)
{
  this->look_at_pos_ = TVec3f::forward;
  this->current_look_at_pos_ = TVec3f::forward;
  this->target_lerp_t_ = 0.5f;
  this->target_direction_ = TVec3f::forward;
  return Camera3D::Init(obj);
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void Camera3D_LookAt::UpdateViewMatrix()
{
  this->view_matrix_ = Matrix4x4::identity;
  if (this->target_)
  {
    const SharedRef<GameObject>& player = this->GetObject()->GetParent();
    if (player)
    {
      TVec3f camera_pos = player->GetTransform()->GetWorldPosition();
      this->direction_ = (this->current_look_at_pos_ - player->GetTransform()->GetWorldPosition()).Normalized();
      //camera_pos -= this->direction_ * this->GetTransform()->GetPosition().Length();
      //camera_pos.y = std::max(camera_pos.y, player->GetTransform()->GetY());
      this->view_matrix_ = Matrix4x4::LookAt(
        camera_pos,
        this->current_look_at_pos_,
        this->GetObject()->GetTransform()->GetWorldMatrix().GetCameraYVec()
      );
    }
    else
    {
      TVec3f camera_pos = this->GetTransform()->GetWorldPosition();
      this->direction_ = (this->current_look_at_pos_ - camera_pos).Normalized();
      this->view_matrix_ = Matrix4x4::LookAt(
        camera_pos,
        this->current_look_at_pos_,
        this->GetObject()->GetTransform()->GetWorldMatrix().GetCameraYVec()
      );
    }
  }
  //ターゲットが存在しない時の処理
  else
  {
    this->current_look_at_pos_ = this->look_at_pos_;

    const Matrix4x4& world = this->GetTransform()->GetWorldMatrix();
    const TVec3f camera_pos = world.GetPosition3d();
    const TVec3f look_at_pos = world * this->look_at_pos_;
    this->direction_ = (look_at_pos - camera_pos).Normalized();
    this->view_matrix_ = Matrix4x4::LookAt(
      camera_pos,
      look_at_pos,
      world.GetCameraYVec()
    );
  }
  this->UpdateBillboardMatrix();
}

// =================================================================
// Methods
// =================================================================
void Camera3D_LookAt::Update()
{
  if (this->target_)
  {
    this->current_look_at_pos_ = Mathf::Lerp(this->current_look_at_pos_, this->target_->GetTransform()->GetWorldPosition(), this->target_lerp_t_);
  }
}

// =================================================================
// Setter / Getter
// =================================================================
void Camera3D_LookAt::SetLookAtPos(const TVec3f& look_at_pos)
{
  if (this->look_at_pos_ == look_at_pos)
  {
    return;
  }
  this->look_at_pos_ = look_at_pos;
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
}

void Camera3D_LookAt::SetLookAtPosX(T_FLOAT x)
{
  if (this->look_at_pos_.x == x)
  {
    return;
  }
  this->look_at_pos_.x = x;
}

void Camera3D_LookAt::SetLookAtPosY(T_FLOAT y)
{
  if (this->look_at_pos_.y == y)
  {
    return;
  }
  this->look_at_pos_.y = y;
}

void Camera3D_LookAt::SetLookAtPosZ(T_FLOAT z)
{
  if (this->look_at_pos_.z == z)
  {
    return;
  }
  this->look_at_pos_.z = z;
}