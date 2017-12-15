#include "Camera3D_LookAt.h"
#include "NativeMethod.h"
#include "MathConstants.h"
#include "Director.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Camera3D_LookAt::Camera3D_LookAt(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max)
  : Camera3D(x, y, width, height, z_min, z_max)
  , look_at_pos_(0.0f, 0.0f, 1.0f)
  , direction_(0.0f, 0.0f, 1.0f)
  , target_(nullptr)
  , current_target_look_pos_()
  , target_lerp_(1.0f)
  , camera_up_(0.0f, 1.0f, 0.0f)
  , view_dirty_(true)
{
  this->entity_ = new GameObject3D();
  this->view_matrix_ = NativeMethod::Matrix().Matrix4x4_Create();
  this->inv_ = NativeMethod::Matrix().Matrix4x4_Create();
}

Camera3D_LookAt::Camera3D_LookAt()
  : Camera3D()
  , look_at_pos_(0.0f, 0.0f, 1.0f)
  , direction_(0.0f, 0.0f, 1.0f)
  , target_(nullptr)
  , current_target_look_pos_()
  , target_lerp_(1.0f)
  , camera_up_(0.0f, 1.0f, 0.0f)
  , view_dirty_(true)
{
  this->entity_ = new GameObject3D();
  this->view_matrix_ = NativeMethod::Matrix().Matrix4x4_Create();
  this->inv_ = NativeMethod::Matrix().Matrix4x4_Create();
}

Camera3D_LookAt::~Camera3D_LookAt()
{
  delete this->entity_;
  NativeMethod::Matrix().Matrix4x4_Delete(this->view_matrix_);
  NativeMethod::Matrix().Matrix4x4_Delete(this->inv_);
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void Camera3D_LookAt::CheckViewDirty()
{
  //if (!this->view_dirty_)
  //{
  //  return;
  //}
  this->OnViewChanged();
  NativeMethod::Matrix().Matrix4x4_Init(this->inv_);
  NativeMethod::Matrix().Matrix4x4_Init(this->view_matrix_);

  if (this->target_)
  {
    NativeMethod::Matrix().Matrix4x4_LookAtLH(
      this->view_matrix_,
      this->GetTransform()->GetWorldPosition(),
      this->current_target_look_pos_,
      this->camera_up_
    );
  }
  //ターゲットが存在しない時の処理
  else
  {
    GameObject3D* player = this->entity_->GetParent();
    if (player)
    {
      //親子関係の適用
      GameObject3D* p = this->entity_;
      while (p)
      {
        NativeMethod::Matrix().Matrix4x4_Multiply(this->inv_, p->GetTransform()->GetMatrix());
        p = p->GetParent();
      }
      NativeMethod::Matrix().Matrix4x4_Inverse(this->view_matrix_, this->inv_);

      //LoodkAtの適用
      TVec3f camera_pos = TVec3f();
      TVec3f look_at_pos = this->look_at_pos_;
      NativeMethod::Matrix().Matrix4x4_Apply(
        this->GetTransform()->GetRotationMatrix(),
        &look_at_pos.x, &look_at_pos.y, &look_at_pos.z
      );
      NativeMethod::Matrix().Matrix4x4_LookAtLH(
        this->inv_,
        camera_pos,
        look_at_pos,
        this->camera_up_
      );
      NativeMethod::Matrix().Matrix4x4_Multiply(this->view_matrix_, this->inv_);
    }
    //プレイヤーが存在しない時の処理
    else
    {
      NativeMethod::Matrix().Matrix4x4_Inverse(this->inv_, this->entity_->GetTransform()->GetMatrix());
      NativeMethod::Matrix().Matrix4x4_Multiply(this->view_matrix_, this->inv_);
    }
  }

  TVec3f direction_root = TVec3f(0.0f, 0.0f, 0.0f);
  TVec3f direction_moved = TVec3f(0.0f, 0.0f, 1.0f);
  NativeMethod::Matrix().Matrix4x4_Apply(this->view_matrix_, &direction_root.x, &direction_root.y, &direction_root.z);
  NativeMethod::Matrix().Matrix4x4_Apply(this->view_matrix_, &direction_moved.x, &direction_moved.y, &direction_moved.z);
  this->direction_ = (direction_moved - direction_root).Normalized();
  this->view_dirty_ = false;
}

LP_MATRIX_4x4 Camera3D_LookAt::GetViewMatrix()
{
  this->CheckViewDirty();
  return this->view_matrix_;
}

// =================================================================
// Methods
// =================================================================
void Camera3D_LookAt::SetPlayer(GameObject3D* player)
{
  if (this->entity_->HasParent())
  {
    this->entity_->RemoveSelf();
  }
  player->AddChild(this->entity_);
}

void Camera3D_LookAt::Update()
{
  if (this->target_)
  {
    //this->current_target_look_pos_ += (this->target_->GetTransform()->GetWorldPosition() - this->current_target_look_pos_) * this->target_lerp_;
    TVec3f pos = this->target_->GetTransform()->GetWorldPosition() - this->current_target_look_pos_;
    if (pos.LengthSquare() > this->target_lerp_ * this->target_lerp_)
    {
      this->current_target_look_pos_ += pos.Normalized() * this->target_lerp_;
    }
    else
    {
      this->current_target_look_pos_ += pos;
    }
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

void Camera3D_LookAt::SetCameraUp(const TVec3f& camera_up)
{
  if (this->camera_up_ == camera_up)
  {
    return;
  }
  this->camera_up_ = camera_up;
  this->OnViewChanged();
}

void Camera3D_LookAt::SetCameraUp(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  if (
    this->camera_up_.x == x &&
    this->camera_up_.y == y &&
    this->camera_up_.z == z
    )
  {
    return;
  }
  this->camera_up_.x = x;
  this->camera_up_.y = y;
  this->camera_up_.z = z;
  this->OnViewChanged();
}

void Camera3D_LookAt::SetCameraUpX(T_FLOAT x)
{
  if (this->camera_up_.x == x)
  {
    return;
  }
  this->camera_up_.x = x;
  this->OnViewChanged();
}

void Camera3D_LookAt::SetCameraUpY(T_FLOAT y)
{
  if (this->camera_up_.y == y)
  {
    return;
  }
  this->camera_up_.y = y;
  this->OnViewChanged();
}

void Camera3D_LookAt::SetCameraUpZ(T_FLOAT z)
{
  if (this->camera_up_.z == z)
  {
    return;
  }
  this->camera_up_.z = z;
  this->OnViewChanged();
}
