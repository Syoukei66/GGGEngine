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
  static AnimatedSprite* CreateWithResource(const TextureResource& texture, T_UINT8 x_num, T_UINT8 y_num);
  static AnimatedSprite* CreateWithTexture(const INativeTexture* texture, T_UINT8 x_num, T_UINT8 y_num);
  static AnimatedSprite* CreateWithTextureRegion(TiledTextureRegion* region, bool delete_region);
  static AnimatedSprite* CreateWithMaterial(Material& material, T_UINT8 x_num, T_UINT8 y_num);

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

  // =================================================================
  // delegate to AnimatedSpriteRenderer
  // =================================================================
public:
  inline void SetAnimateRange(T_UINT16 begin, T_UINT16 end)
  {
    this->GetAnimatedSpriteRenderer()->SetAnimateRange(begin, end);
  }
  inline void Animate(T_UINT16 duration_frame)
  {
    this->GetAnimatedSpriteRenderer()->Animate(duration_frame);
  }
  inline void SetCurrentIndex(T_UINT16 index)
  {
    this->GetAnimatedSpriteRenderer()->SetCurrentIndex(index);
  }
  inline T_UINT16 GetCurrentIndex() const
  {
    return this->GetAnimatedSpriteRenderer()->GetCurrentIndex();
  }
  inline TiledTextureRegion* GetTiledTextureRegion() const
  {
    return this->GetAnimatedSpriteRenderer()->GetTiledTextureRegion();
  }
};
