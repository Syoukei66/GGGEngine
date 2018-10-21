#include "SpriteRenderer.h"
#include <Core/AssetManager.h>

/*
  Sprite毎に専用シェーダー用意するのはコスパが悪いので、
  やはりメッシュを作成して動的にバッチングする仕組みが必要
*/

// =================================================================
// Constructor / Destructor
// =================================================================
SpriteRenderer::SpriteRenderer(GameObject* entity)
  : Renderer(entity)
  , texture_region_(nullptr)
  , size_(1.0f, 1.0f)
  , mesh_(AssetManager::Load<rcMesh>(DefaultUniqueID::MESH_SPRITE))
{
  this->SetSharedMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_SPRITE));
}

SpriteRenderer::~SpriteRenderer()
{
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
bool SpriteRenderer::SetStreamSource() const
{
  this->mesh_->SetStreamSource();
  return true;
}

void SpriteRenderer::SetProperties(const SharedRef<rcShader>& shader) const
{
  if (!this->texture_region_)
  {
    return;
  }
  shader->SetTexture("_Image", this->texture_region_->GetTexture());
  const TVec2f& uv0 = this->texture_region_->GetUV0();
  const TVec2f& uv1 = this->texture_region_->GetUV1();
  shader->SetVec2f("_UV0", uv0);
  shader->SetVec2f("_UV1", uv1);
  //shader->SetVec2f("_UV0", uv0);
  //shader->SetVec2f("_UV1", { 1.0f / (uv1.x - uv0.x), 1.0f / (uv1.y - uv0.y) });
  shader->SetFloat("_Width", this->size_.width);
  shader->SetFloat("_Height", this->size_.height);
}

void SpriteRenderer::DrawSubset(T_UINT8 submesh_index) const
{
  this->mesh_->DrawSubset(submesh_index);
}

// =================================================================
// Method
// =================================================================
void SpriteRenderer::FitToTexture()
{
  const SharedRef<const rcTexture>& texture = this->GetTextureRegion()->GetTexture();
  if (!texture)
  {
    return;
  }
  this->GetTextureRegion()->FitToTexture();
  this->SetWidth((T_FLOAT)texture->GetWidth());
  this->SetHeight((T_FLOAT)texture->GetHeight());
}

// =================================================================
// setter/getter
// =================================================================
void SpriteRenderer::SetTextureRegion(const SharedRef<rcTextureRegion>& region)
{
  this->texture_region_ = region;
}

void SpriteRenderer::SetTexture(const SharedRef<const rcTexture>& texture)
{
  if (!this->texture_region_)
  {
    this->texture_region_ = rcTextureRegion::CreateWithTexture(texture);
  }
  else
  {
    this->texture_region_->SetTexture(texture);
  }
  this->GetMaterial()->SetMainTexture(texture);
}