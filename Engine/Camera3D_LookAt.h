#pragma once

#include "Camera3D.h"

class Camera3D_LookAt : public Camera3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Camera3D_LookAt(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max);
  Camera3D_LookAt();
  ~Camera3D_LookAt();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual INativeMatrix* GetViewMatrix() const override;

protected:
  virtual void SetupCamera() override;

  // =================================================================
  // Methods
  // =================================================================
public:
  void CheckViewDirty();
  void SetPlayer(GameObject3D* player);
  void Update();

private:
  inline void OnViewChanged()
  {
    this->view_dirty_ = true;
  }

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline GameObject3D* GetPlayer() const
  {
    return ((GameObject3D*)this->entity_)->GetParent();
  }

  inline void SetTarget(GameObject3D* target)
  {
    this->target_ = target;
    this->target_direction_ = !this->target_ ? this->target_direction_ : (this->target_->GetTransform()->GetWorldPosition() - this->GetEntity()->GetWorldMatrix().GetPosition3d()).Normalized();
  }

  void SetLookAtPos(const TVec3f& look_at_pos);
  void SetLookAtPos(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  inline const TVec3f& GetLookAtPos() const
  {
    return this->look_at_pos_;
  }
  void SetLookAtPosX(T_FLOAT x);
  inline T_FLOAT GetLookAtPosX() const
  {
    return this->look_at_pos_.x;
  }
  void SetLookAtPosY(T_FLOAT y);
  inline T_FLOAT GetLookAtPosY() const
  {
    return this->look_at_pos_.y;
  }
  void SetLookAtPosZ(T_FLOAT z);
  inline T_FLOAT GetLookAtPosZ() const
  {
    return this->look_at_pos_.z;
  }

  inline void SetTargetLerpDeltaTime(T_FLOAT t)
  {
    this->target_lerp_t_ = t;
  }
  inline T_FLOAT GetTargetLerpDeltaTime() const
  {
    return this->target_lerp_t_;
  }

  inline const TVec3f& GetCurrentLookAtPos() const
  {
    return this->current_look_at_pos_;
  }

  inline const TVec3f& GetTargetDirection() const
  {
    return this->target_direction_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  INativeMatrix* const view_matrix_;

  TVec3f look_at_pos_;
  TVec3f current_look_at_pos_;

  GameObject3D* target_;
  TVec3f target_direction_;
  T_FLOAT target_lerp_t_;

  bool view_dirty_;

};
