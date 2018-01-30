#pragma once

#include "GameObject2D.h"
#include "SpriteRenderer.h"

class Sprite : public GameObject2D
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static Sprite* Create();
  static Sprite* CreateWithMaterial(Material* material);
  static Sprite* CreateWithTexture(const Texture& texture);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  Sprite() {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline SpriteRenderer* GetSpriteRenderer() const
  {
    return (SpriteRenderer*)this->GetRenderer();
  }
};
