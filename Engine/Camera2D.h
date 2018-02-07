#pragma once

#include <deque>
#include "Camera.h"
#include "GameObjectRenderState.h"
#include "GameObject2D.h"

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
  virtual const INativeMatrix* GetViewMatrix() const override;
  virtual const INativeMatrix* GetProjectionMatrix() const override;

protected:
  virtual void OnViewportChanged() override;
  virtual void OnDrawScene(Scene* scene) override;

  // =================================================================
  // Method
  // =================================================================
public:
  inline GameObjectRenderState* GetRenderState()
  {
    return this->render_state_;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline Transform2D* GetTransform()
  {
    return ((GameObject2D*)this->entity_)->GetTransform();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObjectRenderState* render_state_;

  INativeMatrix* projection_matrix_;
  bool projection_dirty_;
};