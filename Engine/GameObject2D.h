#pragma once

#include "GameObject.h"
#include "Transform2D.h"

class EntityModifierRoot;

class GameObject2D : public GameObject
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObject2D();
  virtual ~GameObject2D();
  
  // =================================================================
  // Method
  // =================================================================
public:
  void RegisterEntityModifier(EntityModifierRoot* root);
  void UnregisterEntityModifier(EntityModifierRoot* root);
  void ClearEntityModifiers();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline Transform2D* GetTransform()
  {
    return (Transform2D*)this->transform_;
  }
  inline const Transform2D* GetTransform() const
  {
    return (Transform2D*)this->transform_;
  }

};
