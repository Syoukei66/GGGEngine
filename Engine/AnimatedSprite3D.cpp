#include "AnimatedSprite3D.h"
#include "EngineAsset.h"

// =================================================================
// Factory Method
// =================================================================
AnimatedSprite3D* AnimatedSprite3D::Create()
{
  AnimatedSprite3D* ret = new AnimatedSprite3D();
  ret->SetRenderer(new AnimatedSpriteRenderer(ret, 0.01f));
  return ret;
}

AnimatedSprite3D* AnimatedSprite3D::CreateWithResource(const TextureResource& texture, T_UINT8 x_num, T_UINT8 y_num)
{
  return AnimatedSprite3D::CreateWithTexture(texture.GetContents(), x_num, y_num);
}

AnimatedSprite3D* AnimatedSprite3D::CreateWithTexture(const INativeTexture* texture, T_UINT8 x_num, T_UINT8 y_num)
{
  TiledTextureRegion* region = TiledTextureRegion::CreateWithTexture(texture, x_num, y_num);
  return AnimatedSprite3D::CreateWithTextureRegion(region, true);
}

AnimatedSprite3D* AnimatedSprite3D::CreateWithTextureRegion(TiledTextureRegion* region, bool delete_region)
{
  AnimatedSprite3D* ret = AnimatedSprite3D::Create();
  AnimatedSpriteRenderer* renderer = ret->GetAnimatedSpriteRenderer();
  renderer->SetTextureRegion(region, delete_region);
  renderer->SetAnimateRange(0, region->GetTileCount() - 1);
  renderer->FitToTexture();
  return ret;
}

AnimatedSprite3D* AnimatedSprite3D::CreateWithMaterial(Material& material, T_UINT8 x_num, T_UINT8 y_num)
{
  TiledTextureRegion* region = TiledTextureRegion::CreateWithMaterial(material, x_num, y_num);
  AnimatedSprite3D* ret = AnimatedSprite3D::CreateWithTextureRegion(region, true);
  AnimatedSpriteRenderer* renderer = ret->GetAnimatedSpriteRenderer();
  renderer->SetMaterial(material);
  return ret;
}