#include "Sprite3D.h"
#include "EngineAsset.h"
#include "TextureRegion.h"

// =================================================================
// Factory Method
// =================================================================
Sprite3D* Sprite3D::Create()
{
  Sprite3D* ret = new Sprite3D();
  ret->SetRenderer(new SpriteRenderer());
  ret->Init();
  return ret;
}

Sprite3D* Sprite3D::CreateWithTextureRegion(ITextureRegion* region)
{
  Sprite3D* ret = Sprite3D::Create();
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetTextureRegion(region);
  renderer->FitToTexture();
  return ret;
}

Sprite3D* Sprite3D::CreateWithMaterial(Material& material)
{
  TextureRegion* region = TextureRegion::CreateWithMaterial(material);
  Sprite3D* ret = Sprite3D::CreateWithTextureRegion(region);
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetMaterial(material);
  return ret;
}

Sprite3D* Sprite3D::CreateWithTexture(const Texture& texture)
{
  TextureRegion* region = TextureRegion::CreateWithTexture(texture);
  Sprite3D* ret = Sprite3D::CreateWithTextureRegion(region);
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  return ret;
}
