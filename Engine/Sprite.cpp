#include "Sprite.h"
#include "TextureRegion.h"

// =================================================================
// Factory Method
// =================================================================
Sprite* Sprite::Create()
{
  Sprite* ret = new Sprite();
  ret->SetRenderer(new SpriteRenderer(ret));
  ret->Init();
  return ret;
}

Sprite* Sprite::CreateWithTexture(const rcTexture* texture)
{
  rcTextureRegion* region = rcTextureRegion::CreateWithTexture(texture);
  return Sprite::CreateWithTextureRegion(region, true);
}

Sprite* Sprite::CreateWithTextureRegion(rcTextureRegion* region, bool delete_region)
{
  Sprite* ret = Sprite::Create();
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetTextureRegion(region, delete_region);
  renderer->FitToTexture();
  return ret;
}

Sprite* Sprite::CreateWithMaterial(rcMaterial& material)
{
  rcTextureRegion* region = rcTextureRegion::CreateWithMaterial(material);
  Sprite* ret = Sprite::CreateWithTextureRegion(region, true);
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetMaterial(material);
  return ret;
}