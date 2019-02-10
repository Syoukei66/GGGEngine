#pragma once

#include <Engine/GameObject/GameObject.h>

#include "Camera.h"

class Camera3D : public Camera
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_COMPONENT(Camera3D);
  GG_INIT_FUNC_1(Camera3D, GameObject*);

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual bool FrustumCulling(const TVec3f& positive, const TVec3f& negative, T_INT8* first_index = nullptr) const override;

  virtual const Matrix4x4& GetViewMatrix() const override;
  virtual const Matrix4x4& GetProjectionMatrix() const override;

protected:
  virtual void SetupCamera() override;

  virtual void OnViewportChanged() override;

  virtual void OnDrawScene(Scene* scene) override;

  // =================================================================
  // Methods
  // =================================================================
public:
  TVec3f CalcRayVector(const TVec2f& screen_position);

protected:
  void CheckProjectionDirty();

private:
  GG_INLINE void OnProjectionChanged()
  {
    this->projection_dirty_ = true;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  const TVec3f Get2dPositionScale(const GameObject* obj) const;
  const TVec3f Get2dPosition(const GameObject* obj) const;

  GG_INLINE Transform* GetTransform()
  {
    return SharedRef<GameObject>::StaticCast(this->GetObject())->GetTransform();
  }
  GG_INLINE const Transform* GetTransform() const
  {
    return SharedRef<const GameObject>::StaticCast(this->GetObject())->GetTransform();
  }
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
  Matrix4x4 projection_matrix_;

  T_FLOAT fov_;
  T_FLOAT z_near_;
  T_FLOAT z_far_;
  bool projection_dirty_;
};