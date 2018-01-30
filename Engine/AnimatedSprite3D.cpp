#include "AnimatedSprite3D.h"
#include "EngineAsset.h"

// =================================================================
// Factory Method
// =================================================================
AnimatedSprite3D* AnimatedSprite3D::Create()
{
  AnimatedSprite3D* ret = new AnimatedSprite3D();
  ret->SetRenderer(new AnimatedSpriteRenderer());
  return ret;
}

AnimatedSprite3D* AnimatedSprite3D::CreateWithTextureRegion(TiledTextureRegion* region)
{
  AnimatedSprite3D* ret = AnimatedSprite3D::Create();
  AnimatedSpriteRenderer* renderer = ret->GetAnimatedSpriteRenderer();
  renderer->SetTextureRegion(region);
  renderer->SetAnimateRange(0, region->GetTileCount() - 1);
  renderer->FitToTexture();
  return ret;
}

AnimatedSprite3D* AnimatedSprite3D::CreateWithMaterial(Material& material, T_UINT8 x_num, T_UINT8 y_num)
{
  TiledTextureRegion* region = TiledTextureRegion::CreateWithMaterial(material, x_num, y_num);
  AnimatedSprite3D* ret = AnimatedSprite3D::CreateWithTextureRegion(region);
  AnimatedSpriteRenderer* renderer = ret->GetAnimatedSpriteRenderer();
  renderer->SetMaterial(material);
  return ret;
}

AnimatedSprite3D* AnimatedSprite3D::CreateWithTexture(const Texture& texture, T_UINT8 x_num, T_UINT8 y_num)
{
  TiledTextureRegion* region = TiledTextureRegion::CreateWithTexture(texture, x_num, y_num);
  AnimatedSprite3D* ret = AnimatedSprite3D::CreateWithTextureRegion(region);
  AnimatedSpriteRenderer* renderer = ret->GetAnimatedSpriteRenderer();
  return ret;
}
