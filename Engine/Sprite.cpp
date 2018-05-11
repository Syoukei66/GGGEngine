#include "Sprite.h"
#include "TextureRegion.h"

// =================================================================
// Factory Method
// =================================================================
Sprite* Sprite::Create()
{
  Sprite* ret = new Sprite();
  ret->SetRenderer(new SpriteRenderer(ret, 1.0f));
  ret->Init();
  return ret;
}

Sprite* Sprite::CreateWithResource(const TextureResource& texture)
{
  TextureRegion* region = TextureRegion::CreateWithTexture(texture.GetContents());
  return Sprite::CreateWithTextureRegion(region, true);
}

Sprite* Sprite::CreateWithTexture(const INativeTexture* texture)
{
  TextureRegion* region = TextureRegion::CreateWithTexture(texture);
  return Sprite::CreateWithTextureRegion(region, true);
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