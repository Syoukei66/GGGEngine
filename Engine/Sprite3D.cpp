#include "Sprite3D.h"
#include "TextureRegion.h"

// =================================================================
// Factory Method
// =================================================================
Sprite3D* Sprite3D::Create()
{
  Sprite3D* ret = new Sprite3D();
  ret->SetRenderer(new SpriteRenderer(ret));
  ret->Init();
  return ret;
}

Sprite3D* Sprite3D::CreateWithTexture(const rcTexture* texture)
{
  rcTextureRegion* region = rcTextureRegion::CreateWithTexture(texture);
  return Sprite3D::CreateWithTextureRegion(region, true);
}

Sprite3D* Sprite3D::CreateWithTextureRegion(rcTextureRegion* region, bool delete_region)
{
  Sprite3D* ret = Sprite3D::Create();
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetTextureRegion(region, delete_region);
  renderer->FitToTexture();
  return ret;
}

Sprite3D* Sprite3D::CreateWithMaterial(rcMaterial& material)
{
  rcTextureRegion* region = rcTextureRegion::CreateWithMaterial(material);
  Sprite3D* ret = Sprite3D::CreateWithTextureRegion(region, true);
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetMaterial(material);
  return ret;
}
