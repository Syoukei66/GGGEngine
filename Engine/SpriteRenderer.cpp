#include "SpriteRenderer.h"
#include "TextureRegion.h"
#include "EngineAsset.h"

// =================================================================
// Constructor / Destructor
// =================================================================
SpriteRenderer::SpriteRenderer(GameObject* entity)
  : Renderer(entity)
  , texture_region_(nullptr)
  , size_(1.0f, 1.0f)
{
  this->SetMaterial(*EngineAsset::Material::SPRITE.Clone());
}

SpriteRenderer::~SpriteRenderer()
{
  if (this->delete_region_)
  {
    delete this->texture_region_;
  }
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
bool SpriteRenderer::SetStreamSource() const
{
  EngineAsset::rcCustomMesh::QUAD.GetContents().SetStreamSource();
  return true;
}

void SpriteRenderer::SetProperties(Material* material) const
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
void SpriteRenderer::SetTextureRegion(ITextureRegion* region, bool delete_region)
{
  if (this->delete_region_)
  {
    delete this->texture_region_;
  }
  this->texture_region_ = region;
  this->delete_region_ = delete_region;
}

void SpriteRenderer::SetTexture(const rcTexture* texture)
{
  if (!this->texture_region_)
  {
    this->texture_region_ = TextureRegion::CreateWithTexture(texture);
    this->delete_region_ = true;
  }
  else
  {
    this->texture_region_->SetTexture(texture);
  }
  this->GetMaterial()->SetMainTexture(texture);
}