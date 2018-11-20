#pragma once

#include "GameObject.h"

class EntityModifierRoot;
class Transform2D;

class GameObject2D : public GameObject
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObject2D();
  virtual ~GameObject2D();
  
  // =================================================================
  // Methods
  // =================================================================
public:
  void RegisterEntityModifier(EntityModifierRoot* root);
  void UnregisterEntityModifier(EntityModifierRoot* root);
  void ClearEntityModifiers();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE Transform2D* GetTransform()
  {
    return (Transform2D*)this->transform_;
  }
  GG_INLINE const Transform2D* GetTransform() const
  {
    return (Transform2D*)this->transform_;
  }
  
};
