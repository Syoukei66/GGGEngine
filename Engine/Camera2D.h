#pragma once

#include "Camera.h"

class Camera2D : public Camera
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Camera2D(GameObject* entity);
  virtual ~Camera2D();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual const Matrix4x4& GetViewMatrix() const override;
  virtual const Matrix4x4& GetProjectionMatrix() const override;
};