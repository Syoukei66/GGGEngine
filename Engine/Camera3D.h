#pragma once

#include <deque>
#include "Camera.h"
#include "GameComponent.h"
#include "GameObject3D.h"

class Camera3D : public Camera
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Camera3D(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max);
  Camera3D();
  virtual ~Camera3D();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual const INativeMatrix* GetViewMatrix() const override;
  virtual const INativeMatrix* GetProjectionMatrix() const override;

protected:
  virtual void SetupCamera() override;

  virtual void OnViewportChanged() override;

  virtual void OnDrawScene(Scene* scene) override;

  // =================================================================
  // Method
  // =================================================================
protected:
  void CheckProjectionDirty();

private:
  inline void OnProjectionChanged()
  {
    this->projection_dirty_ = true;
  }

  // =================================================================
  // setter/getter
  // =================================================================
public:
  const TVec3f Get2dPositionScale(const GameObject3D* obj) const;
  const TVec3f Get2dPosition(const GameObject3D* obj) const;

  inline Transform3D* GetTransform()
  {
    return ((GameObject3D*)this->entity_)->GetTransform();
  }
  inline const Transform3D* GetTransform() const
  {
    return ((GameObject3D*)this->entity_)->GetTransform();
  }
  void SetFov(T_FLOAT fov);
  inline T_FLOAT GetFov() const
  {
    return this->fov_;
  }
  void SetZNear(T_FLOAT z_near);
  inline T_FLOAT GetZNear() const
  {
    return this->z_near_;
  }
  void SetZFar(T_FLOAT z_far);
  inline T_FLOAT GetZFar() const
  {
    return this->z_far_;
  }
  inline GameObjectRenderState* GetRenderState()
  {
    return this->render_state_;
  }
  inline const INativeMatrix& GetBillboardingMatrix() const
  {
    return *this->billboarding_matrix_;
  }

protected:
  inline void SetDirection(const TVec3f& direction)
  {
    this->direction_ = direction;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObjectRenderState* render_state_;

  INativeMatrix* billboarding_matrix_;
  INativeMatrix* projection_matrix_;
  INativeMatrix* calc_2dpos_matrix_;

  T_FLOAT fov_;
  T_FLOAT z_near_;
  T_FLOAT z_far_;
  bool projection_dirty_;
};