#pragma once

#include <Engine/GameObject/Transform/Transform.h>
#include "Camera3D.h"

class Camera3D_LookAt : public Camera3D
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_COMPONENT(Camera3D_LookAt);
  GG_CREATE_FUNC_1(Camera3D_LookAt, GameObject*, obj);

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
protected:
  virtual void UpdateViewMatrix() override;

  // =================================================================
  // Methods
  // =================================================================
public:
  void Update();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<GameObject> GetPlayer() const
  {
    return SharedRef<GameObject>::StaticCast(this->GetObject()->GetParent());
  }

  GG_INLINE void SetTarget(GameObject* target)
  {
    this->target_ = target;
    this->target_direction_ = !this->target_ ? this->target_direction_ : (this->target_->GetTransform()->GetWorldPosition() - this->GetObject()->GetTransform()->GetWorldMatrix().GetPosition3d()).Normalized();
  }

  void SetLookAtPos(const TVec3f& look_at_pos);
  void SetLookAtPos(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  GG_INLINE const TVec3f& GetLookAtPos() const
  {
    return this->look_at_pos_;
  }
  void SetLookAtPosX(T_FLOAT x);
  GG_INLINE T_FLOAT GetLookAtPosX() const
  {
    return this->look_at_pos_.x;
  }
  void SetLookAtPosY(T_FLOAT y);
  GG_INLINE T_FLOAT GetLookAtPosY() const
  {
    return this->look_at_pos_.y;
  }
  void SetLookAtPosZ(T_FLOAT z);
  GG_INLINE T_FLOAT GetLookAtPosZ() const
  {
    return this->look_at_pos_.z;
  }

  GG_INLINE void SetTargetLerpDeltaTime(T_FLOAT t)
  {
    this->target_lerp_t_ = t;
  }
  GG_INLINE T_FLOAT GetTargetLerpDeltaTime() const
  {
    return this->target_lerp_t_;
  }

  GG_INLINE const TVec3f& GetCurrentLookAtPos() const
  {
    return this->current_look_at_pos_;
  }

  GG_INLINE const TVec3f& GetTargetDirection() const
  {
    return this->target_direction_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  TVec3f look_at_pos_;
  TVec3f current_look_at_pos_;

  GameObject* target_;
  TVec3f target_direction_;
  T_FLOAT target_lerp_t_;

};
