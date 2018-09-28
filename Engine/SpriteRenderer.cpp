#include "SpriteRenderer.h"
#include "EngineAsset.h"

// =================================================================
// Constructor / Destructor
// =================================================================
SpriteRenderer::SpriteRenderer(GameObject* entity)
  : Renderer(entity)
  , texture_region_(nullptr)
  , size_(1.0f, 1.0f)
{
  this->SetMaterial(*EngineAsset::rcMaterial::SPRITE.Clone());
}

SpriteRenderer::~SpriteRenderer()
{
  this->texture_region_->Release();
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
bool SpriteRenderer::SetStreamSource() const
{
  EngineAsset::rcCustomMesh::QUAD.GetContents().SetStreamSource();
  return true;
}

void SpriteRenderer::SetProperties(rcMaterial* material) const
{
  if (!this->texture_region_)
  {
    return;
  }
  material->SetMainTexture(this->texture_region_->GetTexture());
  const TVec2f& uv0 = this->texture_region_->GetUV0();
  const TVec2f& uv1 = this->texture_region_->GetUV1();
  material->SetTilingOffset(uv0);
  material->SetTiling({ 1.0f / (uv1.x - uv0.x), 1.0f / (uv1.y - uv0.y) });
}

void SpriteRenderer::DrawSubset(T_UINT8 submesh_index) const
{
  EngineAsset::rcCustomMesh::QUAD.GetContents().DrawSubset(submesh_index);
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