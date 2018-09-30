#include "AnimatedSprite.h"

// =================================================================
// Factory Method
// =================================================================
AnimatedSprite* AnimatedSprite::Create()
{
  AnimatedSprite* ret = new AnimatedSprite();
  ret->SetRenderer(new AnimatedSpriteRenderer(ret));
  ret->Init();
  return ret;
}

AnimatedSprite* AnimatedSprite::CreateWithTexture(const rcTexture* texture, T_UINT8 x_num, T_UINT8 y_num)
{
  rcTiledTextureRegion* region = rcTiledTextureRegion::CreateWithTexture(texture, x_num, y_num);
  return AnimatedSprite::CreateWithTextureRegion(region);
}

AnimatedSprite* AnimatedSprite::CreateWithTextureRegion(rcTiledTextureRegion* region)
{
  AnimatedSprite* ret = AnimatedSprite::Create();
  AnimatedSpriteRenderer* renderer = ret->GetAnimatedSpriteRenderer();
  renderer->SetTextureRegion(region);
  renderer->SetAnimateRange(0, region->GetTileCount() - 1);
  renderer->FitToTexture();
  return ret;
}

AnimatedSprite* AnimatedSprite::CreateWithMaterial(rcMaterial* material, T_UINT8 x_num, T_UINT8 y_num)
{
  rcTiledTextureRegion* region = rcTiledTextureRegion::CreateWithMaterial(material, x_num, y_num);
  AnimatedSprite* ret = AnimatedSprite::CreateWithTextureRegion(region);
  AnimatedSpriteRenderer* renderer = ret->GetAnimatedSpriteRenderer();
  renderer->SetMaterial(material);
  return ret;
}
