#pragma once

#include "Camera3D_Transformed.h"

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
  inline Transform3D* GetTransform()
  {
    return this->entity_->GetTransform();
  }

  inline const Transform3D* GetTransform() const
  {
    return this->entity_->GetTransform();
  }

  inline GameObject3D* GetPlayer() const
  {
    return this->entity_->GetParent();
  }

  inline void SetTarget(GameObject3D* target)
  {
    this->target_ = target;
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

  void SetCameraUp(const TVec3f& camera_up);
  void SetCameraUp(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  inline const TVec3f& GetCameraUp() const
  {
    return this->camera_up_;
  }
  void SetCameraUpX(T_FLOAT x);
  inline T_FLOAT GetCameraUpX() const
  {
    return this->camera_up_.x;
  }
  void SetCameraUpY(T_FLOAT y);
  inline T_FLOAT GetCameraUpY() const
  {
    return this->camera_up_.y;
  }
  void SetCameraUpZ(T_FLOAT z);
  inline T_FLOAT GetCameraUpZ() const
  {
    return this->camera_up_.z;
  }
  inline void SetTargetLerp(T_FLOAT lerp)
  {
    this->target_lerp_ = lerp;
  }
  inline T_FLOAT GetTargetLerp() const
  {
    return this->target_lerp_;
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
  GameObject3D* entity_;

  INativeMatrix* view_matrix_;

  TVec3f look_at_pos_;
  TVec3f current_look_at_pos_;

  GameObject3D* target_;
  T_FLOAT target_lerp_;
  TVec3f target_direction_;

  TVec3f camera_up_;
  bool view_dirty_;

};
