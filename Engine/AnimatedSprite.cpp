#include "AnimatedSprite.h"

// =================================================================
// Factory Method
// =================================================================
AnimatedSprite* AnimatedSprite::Create()
{
  AnimatedSprite* ret = new AnimatedSprite();
  ret->SetRenderer(new AnimatedSpriteRenderer(ret, 1.0f));
  ret->Init();
  return ret;
}

AnimatedSprite* AnimatedSprite::CreateWithResource(const TextureResource& texture, T_UINT8 x_num, T_UINT8 y_num)
{
  return AnimatedSprite::CreateWithTexture(texture.GetContents(), x_num, y_num);
}

AnimatedSprite* AnimatedSprite::CreateWithTexture(const INativeTexture* texture, T_UINT8 x_num, T_UINT8 y_num)
{
  TiledTextureRegion* region = TiledTextureRegion::CreateWithTexture(texture, x_num, y_num);
  return AnimatedSprite::CreateWithTextureRegion(region, true);
}

AnimatedSprite* AnimatedSprite::CreateWithTextureRegion(TiledTextureRegion* region, bool delete_region)
{
  AnimatedSprite* ret = AnimatedSprite::Create();
  AnimatedSpriteRenderer* renderer = ret->GetAnimatedSpriteRenderer();
  renderer->SetTextureRegion(region, delete_region);
  renderer->SetAnimateRange(0, region->GetTileCount() - 1);
  renderer->FitToTexture();
  return ret;
}

AnimatedSprite* AnimatedSprite::CreateWithMaterial(Material& material, T_UINT8 x_num, T_UINT8 y_num)
{
  TiledTextureRegion* region = TiledTextureRegion::CreateWithMaterial(material, x_num, y_num);
  AnimatedSprite* ret = AnimatedSprite::CreateWithTextureRegion(region, true);
  AnimatedSpriteRenderer* renderer = ret->GetAnimatedSpriteRenderer();
  renderer->SetMaterial(material);
  return ret;
}
