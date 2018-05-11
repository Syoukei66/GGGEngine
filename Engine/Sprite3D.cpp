#include "Sprite3D.h"
#include "TextureRegion.h"

// =================================================================
// Factory Method
// =================================================================
Sprite3D* Sprite3D::Create()
{
  Sprite3D* ret = new Sprite3D();
  ret->SetRenderer(new SpriteRenderer(ret, 0.01f));
  ret->Init();
  return ret;
}

Sprite3D* Sprite3D::CreateWithResource(const TextureResource& texture)
{
  return Sprite3D::CreateWithTexture(texture.GetContents());
}

Sprite3D* Sprite3D::CreateWithTexture(const INativeTexture* texture)
{
  TextureRegion* region = TextureRegion::CreateWithTexture(texture);
  return Sprite3D::CreateWithTextureRegion(region, true);
}

Sprite3D* Sprite3D::CreateWithTextureRegion(ITextureRegion* region, bool delete_region)
{
  Sprite3D* ret = Sprite3D::Create();
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetTextureRegion(region, delete_region);
  renderer->FitToTexture();
  return ret;
}

Sprite3D* Sprite3D::CreateWithMaterial(Material& material)
{
  TextureRegion* region = TextureRegion::CreateWithMaterial(material);
  Sprite3D* ret = Sprite3D::CreateWithTextureRegion(region, true);
  SpriteRenderer* renderer = ret->GetSpriteRenderer();
  renderer->SetMaterial(material);
  return ret;
}
