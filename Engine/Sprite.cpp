#include "Sprite.h"

// =================================================================
// Factory Method
// =================================================================
Sprite* Sprite::Create()
{
  Sprite* ret = new Sprite();
  ret->SetRenderer(new SpriteRenderer());
  ret->Init();
  return ret;
}

Sprite* Sprite::CreateWithMaterial(Material* material)
{
  Sprite* ret = Sprite::Create();
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetMaterial(*material);
  renderer->FitToTexture();
  return ret;
}

Sprite* Sprite::CreateWithTexture(const Texture& texture)
{
  Sprite* ret = Sprite::Create();
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetTexture(texture);
  renderer->FitToTexture();
  return ret;
}
