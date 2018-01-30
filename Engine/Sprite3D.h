#pragma once

#include "GameObject3D.h"
#include "SpriteRenderer.h"

class Sprite3D : public GameObject3D
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static Sprite3D* Create();
  static Sprite3D* CreateWithTextureRegion(ITextureRegion* region);
  static Sprite3D* CreateWithMaterial(Material& material);
  static Sprite3D* CreateWithTexture(const Texture& texture);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  Sprite3D() {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline SpriteRenderer* GetSpriteRenderer() const
  {
    return (SpriteRenderer*)this->GetRenderer();
  }
};
