#pragma once

#include "GameObject.h"

class EntityModifierRoot;
class Transform2D;

class GameObject2D : public GameObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(GameObject2D);
  GG_CREATE_FUNC(GameObject2D);
  GG_CREATE_FUNC_1(GameObject2D, const std::string&);
  GG_DESTRUCT_FUNC(GameObject2D);
  
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
