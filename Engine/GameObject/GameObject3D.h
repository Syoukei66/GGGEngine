#pragma once

#include "GameObject.h"

class Transform3D;

class GameObject3D : public GameObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(GameObject3D);
  GG_CREATE_FUNC(GameObject3D);
  GG_DESTRUCT_FUNC(GameObject3D);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE Transform3D* GetTransform()
  {
    return (Transform3D*)this->transform_;
  }
  GG_INLINE const Transform3D* GetTransform() const
  {
    return (Transform3D*)this->transform_;
  }
  
};
