#pragma once

#include <list>
#include "GameObjectRenderState.h"

class Camera2D;

class GameObject2DRenderState : public GameObjectRenderState
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObject2DRenderState(Camera2D* camera);
  ~GameObject2DRenderState();

  // =================================================================
  // Method
  // =================================================================
protected:
  virtual void SetupViewProjMatrix(INativeMatrix* view_proj_matrix) override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline Camera2D* GetCamera() const
  {
    return this->camera_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Camera2D* const camera_;
};