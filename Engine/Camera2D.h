#pragma once

#include <deque>
#include "Camera.h"
#include "GameObject2DRenderState.h"

class Camera2D : public Camera
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Camera2D(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max);
  Camera2D();
  virtual ~Camera2D();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void DrawScene(Scene* scene) override;

protected:
  virtual void OnViewportDirty() override;
  virtual LP_MATRIX_4x4 GetViewMatrix() override;
  virtual LP_MATRIX_4x4 GetProjectionMatrix() override;

  // =================================================================
  // Method
  // =================================================================
public:
  inline GameObject2DRenderState* GetRenderState()
  {
    return this->render_state_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObject2DRenderState* render_state_;

  LP_MATRIX_4x4 projection_matrix_;
};