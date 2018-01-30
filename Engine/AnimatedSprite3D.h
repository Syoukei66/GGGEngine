#pragma once

#include "Sprite3D.h"
#include "AnimatedSpriteRenderer.h"

class AnimatedSprite3D : public Sprite3D
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static AnimatedSprite3D* Create();
  static AnimatedSprite3D* CreateWithTextureRegion(TiledTextureRegion* region);
  static AnimatedSprite3D* CreateWithMaterial(Material& material, T_UINT8 x_num, T_UINT8 y_num);
  static AnimatedSprite3D* CreateWithTexture(const Texture& texture, T_UINT8 x_num, T_UINT8 y_num);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AnimatedSprite3D() {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline AnimatedSpriteRenderer* GetAnimatedSpriteRenderer() const
  {
    return (AnimatedSpriteRenderer*)this->GetRenderer();
  }
};