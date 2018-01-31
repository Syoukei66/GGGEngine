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

Sprite* Sprite::CreateWithTextureRegion(ITextureRegion* region, bool delete_region)
{
  Sprite* ret = Sprite::Create();
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetTextureRegion(region, delete_region);
  renderer->FitToTexture();
  return ret;
}

Sprite* Sprite::CreateWithMaterial(Material& material)
{
  TextureRegion* region = TextureRegion::CreateWithMaterial(material);
  Sprite* ret = Sprite::CreateWithTextureRegion(region, true);
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetMaterial(material);
  return ret;
}

Sprite* Sprite::CreateWithTexture(const Texture& texture)
{
  TextureRegion* region = TextureRegion::CreateWithTexture(texture);
  Sprite* ret = Sprite::CreateWithTextureRegion(region, true);
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  return ret;
}
