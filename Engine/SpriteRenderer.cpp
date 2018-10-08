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
{
  this->SetMaterial(AssetManager::GetDefaultAssetLoader<rcMaterial>(DefaultUniqueID::MATERIAL_SPRITE)->CreateFromFile());
  this->mesh_ = AssetManager::GetDefaultAssetLoader<rcMesh>(DefaultUniqueID::MESH_SPRITE)->CreateFromFile();
}

SpriteRenderer::~SpriteRenderer()
{
  this->mesh_->Release();
  this->texture_region_->Release();
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
bool SpriteRenderer::SetStreamSource() const
{
  this->mesh_->SetStreamSource();
  return true;
}

void SpriteRenderer::SetProperties(rcShader* shader) const
{
  if (!this->texture_region_)
  {
    return;
  }
  shader->SetTexture("_Image", this->texture_region_->GetTexture());
  const TVec2f& uv0 = this->texture_region_->GetUV0();
  const TVec2f& uv1 = this->texture_region_->GetUV1();
  shader->SetVec2f("_UV0", uv0);
  shader->SetVec2f("_UV1", { 1.0f / (uv1.x - uv0.x), 1.0f / (uv1.y - uv0.y) });
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
  const rcTexture* texture = this->GetTextureRegion()->GetTexture();
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
void SpriteRenderer::SetTextureRegion(rcTextureRegion* region)
{
  if (this->texture_region_)
  {
    this->texture_region_->Release();
  }
  this->texture_region_ = region;
  this->texture_region_->Retain();
}

void SpriteRenderer::SetTexture(const rcTexture* texture)
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