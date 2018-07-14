#pragma once

#include "GameObject.h"
#include "Transform3D.h"

class GameObject3D : public GameObject
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObject3D();
  virtual ~GameObject3D();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline Transform3D* GetTransform()
  {
    return (Transform3D*)this->transform_;
  }
  inline const Transform3D* GetTransform() const
  {
    return (Transform3D*)this->transform_;
  }
  
};
