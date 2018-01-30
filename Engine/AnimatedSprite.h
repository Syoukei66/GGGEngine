#pragma once

#include "Sprite.h"
#include "AnimatedSpriteRenderer.h"

class AnimatedSprite : public Sprite
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static AnimatedSprite* Create();
  static AnimatedSprite* CreateWithTextureRegion(TiledTextureRegion* region);
  static AnimatedSprite* CreateWithMaterial(Material& material, T_UINT8 x_num, T_UINT8 y_num);
  static AnimatedSprite* CreateWithTexture(const Texture& texture, T_UINT8 x_num, T_UINT8 y_num);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  AnimatedSprite() {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline AnimatedSpriteRenderer* GetAnimatedSpriteRenderer() const
  {
    return (AnimatedSpriteRenderer*)this->GetRenderer();
  }
};
