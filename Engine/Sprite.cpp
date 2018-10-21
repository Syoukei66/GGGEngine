#include "Sprite.h"
#include <Core/TextureRegion.h>

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

Sprite* Sprite::CreateWithTexture(const SharedRef<const rcTexture>& texture)
{
  return Sprite::CreateWithTextureRegion(rcTextureRegion::CreateWithTexture(texture));
}

Sprite* Sprite::CreateWithTextureRegion(const SharedRef<rcTextureRegion>& region)
{
  Sprite* ret = Sprite::Create();
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetTextureRegion(region);
  renderer->FitToTexture();
  return ret;
}

Sprite* Sprite::CreateWithMaterial(const SharedRef<rcMaterial>& material)
{
  Sprite* ret = Sprite::CreateWithTextureRegion(rcTextureRegion::CreateWithMaterial(material));
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetSharedMaterial(material);
  return ret;
}