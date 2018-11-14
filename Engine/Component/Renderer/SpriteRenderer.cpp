#include "SpriteRenderer.h"

#include <Asset/Sprite/Sprite.h>

// =================================================================
// FactoryMethod
// =================================================================
SpriteRenderer* SpriteRenderer::Create(const SharedRef<rcSprite>& sprite, GameObject* obj)
{
  SpriteRenderer* ret = new SpriteRenderer(obj);
  ret->SetSprite(sprite);
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
SpriteRenderer::SpriteRenderer(GameObject* entity)
  : Renderer(entity)
{
  this->SetMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_UNLIT));
}

SpriteRenderer::~SpriteRenderer()
{
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
bool SpriteRenderer::SetStreamSource() const
{
  this->sprite_->GetMesh()->SetStreamSource();
  return true;
}

void SpriteRenderer::SetProperties(const SharedRef<rcShader>& shader) const
{
  if (!this->sprite_)
  {
    return;
  }
  shader->SetTexture("_MainTex", this->sprite_->GetTexture());
}

void SpriteRenderer::DrawSubset(T_UINT8 submesh_index) const
{
  this->sprite_->GetMesh()->DrawSubset(submesh_index);
}