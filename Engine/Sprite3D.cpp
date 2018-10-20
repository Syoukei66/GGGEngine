#include "Sprite3D.h"

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

Sprite3D* Sprite3D::CreateWithTexture(const SharedRef<const rcTexture>& texture)
{
  return Sprite3D::CreateWithTextureRegion(rcTextureRegion::CreateWithTexture(texture));
}

Sprite3D* Sprite3D::CreateWithTextureRegion(const SharedRef<rcTextureRegion>& region)
{
  Sprite3D* ret = Sprite3D::Create();
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetTextureRegion(region);
  renderer->FitToTexture();
  return ret;
}

Sprite3D* Sprite3D::CreateWithMaterial(const SharedRef<rcMaterial>& material)
{
  Sprite3D* ret = Sprite3D::CreateWithTextureRegion(rcTextureRegion::CreateWithMaterial(material));
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetMaterial(material);
  return ret;
}
