#pragma once

#include "Camera3D.h"
#include "GameObject3D.h"

class Camera3D_Transformed : public Camera3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Camera3D_Transformed(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max);
  Camera3D_Transformed();
  virtual ~Camera3D_Transformed();
  
public:
  inline Transform3D* GetTransform()
  {
    return this->entity_->GetTransform();
  }

  inline const Transform3D* GetTransform() const
  {
    return this->entity_->GetTransform();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObject3D* entity_;
};
