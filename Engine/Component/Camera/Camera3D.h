#pragma once

#include <Engine/GameObject/GameObject.h>

#include "Camera.h"

class Camera3D : public Camera
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_COMPONENT(Camera3D);
  GG_CREATE_FUNC_1(Camera3D, GameObject*, obj);

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual bool FrustumCulling(const TVec3f& positive, const TVec3f& negative, T_INT8* first_index = nullptr) const override;

protected:
  virtual void UpdateViewMatrix() override;
  virtual void UpdateProjectionMatrix() override;

  // =================================================================
  // Methods
  // =================================================================
public:
  TVec3f CalcRayVector(const TVec2f& screen_position);

protected:
  void UpdateBillboardMatrix();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  const TVec3f Get2dPositionScale(const GameObject* obj) const;
  const TVec3f Get2dPosition(const GameObject* obj) const;

  void SetFov(T_FLOAT fov);
  GG_INLINE T_FLOAT GetFov() const
  {
    return this->fov_;
  }
  void SetZNear(T_FLOAT z_near);
  GG_INLINE T_FLOAT GetZNear() const
  {
    return this->z_near_;
  }
  void SetZFar(T_FLOAT z_far);
  GG_INLINE T_FLOAT GetZFar() const
  {
    return this->z_far_;
  }
  GG_INLINE const Matrix4x4& GetBillboardingMatrix() const
  {
    return this->billboarding_matrix_;
  }

protected:
  GG_INLINE void SetDirection(const TVec3f& direction)
  {
    this->direction_ = direction;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Matrix4x4 billboarding_matrix_;

  T_FLOAT fov_;
  T_FLOAT z_near_;
  T_FLOAT z_far_;
};