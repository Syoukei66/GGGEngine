#include "SpriteRenderer.h"

#include <Asset/Sprite/Sprite.h>

// =================================================================
// GGG Statement
// =================================================================
GG_CREATE_FUNC_IMPL_1(SpriteRenderer, GameObject*, obj)
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

bool SpriteRenderer::BeginPass(T_UINT8 pass, const SharedRef<rcShader>& shader) const
{
  //shader->SetTexture("_MainTex", this->sprite_->GetTexture());
  return shader->BeginPass(pass, this->sprite_->GetMesh()->GetVertexDeclaration());
}

void SpriteRenderer::DrawSubset(T_UINT8 submesh_index) const
{
  this->sprite_->GetMesh()->DrawSubset(submesh_index);
}