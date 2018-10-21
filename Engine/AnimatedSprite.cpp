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

AnimatedSprite* AnimatedSprite::CreateWithTexture(const SharedRef<const rcTexture>& texture, T_UINT8 x_num, T_UINT8 y_num)
{
  return AnimatedSprite::CreateWithTextureRegion(rcTiledTextureRegion::CreateWithTexture(texture, x_num, y_num));
}

AnimatedSprite* AnimatedSprite::CreateWithTextureRegion(const SharedRef<rcTiledTextureRegion>& region)
{
  AnimatedSprite* ret = AnimatedSprite::Create();
  AnimatedSpriteRenderer* renderer = ret->GetAnimatedSpriteRenderer();
  renderer->SetTextureRegion(SharedRef<rcTextureRegion>::DynamicCast(region));
  renderer->SetAnimateRange(0, region->GetTileCount() - 1);
  renderer->FitToTexture();
  return ret;
}

AnimatedSprite* AnimatedSprite::CreateWithMaterial(const SharedRef<rcMaterial>& material, T_UINT8 x_num, T_UINT8 y_num)
{
  AnimatedSprite* ret = AnimatedSprite::CreateWithTextureRegion(rcTiledTextureRegion::CreateWithMaterial(material, x_num, y_num));
  AnimatedSpriteRenderer* renderer = ret->GetAnimatedSpriteRenderer();
  renderer->SetSharedMaterial(material);
  return ret;
}
