#include "AnimatedSprite3D.h"

// =================================================================
// Factory Method
// =================================================================
AnimatedSprite3D* AnimatedSprite3D::Create()
{
  AnimatedSprite3D* ret = new AnimatedSprite3D();
  ret->SetRenderer(new AnimatedSpriteRenderer(ret));
  return ret;
}

AnimatedSprite3D* AnimatedSprite3D::CreateWithTexture(const SharedRef<const rcTexture>& texture, T_UINT8 x_num, T_UINT8 y_num)
{
  return AnimatedSprite3D::CreateWithTextureRegion(rcTiledTextureRegion::CreateWithTexture(texture, x_num, y_num));
}

AnimatedSprite3D* AnimatedSprite3D::CreateWithTextureRegion(const SharedRef<rcTiledTextureRegion>& region)
{
  AnimatedSprite3D* ret = AnimatedSprite3D::Create();
  AnimatedSpriteRenderer* renderer = ret->GetAnimatedSpriteRenderer();
  renderer->SetTextureRegion(SharedRef<rcTextureRegion>::DynamicCast(region));
  renderer->SetAnimateRange(0, region->GetTileCount() - 1);
  renderer->FitToTexture();
  return ret;
}

AnimatedSprite3D* AnimatedSprite3D::CreateWithMaterial(const SharedRef<rcMaterial>& material, T_UINT8 x_num, T_UINT8 y_num)
{
  AnimatedSprite3D* ret = AnimatedSprite3D::CreateWithTextureRegion(rcTiledTextureRegion::CreateWithMaterial(material, x_num, y_num));
  AnimatedSpriteRenderer* renderer = ret->GetAnimatedSpriteRenderer();
  renderer->SetMaterial(material);
  return ret;
}