#pragma once

#include <deque>
#include "Camera.h"
#include "GameComponent.h"
#include "GameObject3DRenderState.h"

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
  inline const TVec3f& GetDirection()
  {
    return this->direction_;
  }
  inline GameObject3DRenderState* GetRenderState()
  {
    return this->render_state_;
  }
  inline INativeMatrix* GetBillboardingMatrix() const
  {
    return this->billboarding_matrix_;
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
  GameObject3DRenderState* render_state_;

  INativeMatrix* billboarding_matrix_;
  INativeMatrix* projection_matrix_;

  T_FLOAT fov_;
  T_FLOAT z_near_;
  T_FLOAT z_far_;
  bool projection_dirty_;

protected:
  TVec3f direction_;
};