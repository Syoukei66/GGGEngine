#include "SpriteRenderer.h"

#include <Asset/Sprite/Sprite.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(SpriteRenderer, GameObject* obj)
{
  this->SetMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_UNLIT));
  return Renderer::Init(obj);
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
bool SpriteRenderer::SetStreamSource() const
{
  this->sprite_->GetMesh()->SetStreamSource();
  return true;
}

bool SpriteRenderer::SetInputFormat(const SharedRef<rcShader>& shader) const
{
  this->sprite_->GetMesh()->SetInputFormat(shader);
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