#pragma once

#include "Camera.h"

class Camera3D : public Camera
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Camera3D(GameObject* entity);
  virtual ~Camera3D();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual const Matrix4x4& GetViewMatrix() const override;
  virtual const Matrix4x4& GetProjectionMatrix() const override;

protected:
  virtual void SetupCamera() override;

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
  inline const Matrix4x4& GetBillboardingMatrix() const
  {
    return this->billboarding_matrix_;
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