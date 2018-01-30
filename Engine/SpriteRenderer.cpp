#include "SpriteRenderer.h"
#include "EngineAsset.h"

// =================================================================
// Constructor / Destructor
// =================================================================
SpriteRenderer::SpriteRenderer()
  : texture_region_(nullptr)
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
void SpriteRenderer::EditProperty(T_UINT8 material_index, T_UINT8 pass_index, Material* material)
{
  material->Vec2fProperty("_UV0") = this->texture_region_->GetUV0();
  material->Vec2fProperty("_UV1") = this->texture_region_->GetUV1();
  material->FloatProperty("_Width") = this->texture_region_->GetWidth();
  material->FloatProperty("_Height") = this->size_.height;
}

void SpriteRenderer::DrawSubset(T_UINT8 material_index, T_UINT8 pass_index)
{
  EngineAsset::Mesh::QUAD.GetContents().DrawSubMesh(material_index);
}

// =================================================================
// Method
// =================================================================
void SpriteRenderer::FitToTexture()
{
  const Texture* texture = this->GetTextureRegion()->GetTexture();
  if (!texture)
  {
    return;
  }
  this->SetTexture(*texture);
  const T_FLOAT tw = (T_FLOAT)texture->GetWidth();
  const T_FLOAT th = (T_FLOAT)texture->GetHeight();
  this->SetWidth(tw * (this->texture_region_->GetUV1().x - this->texture_region_->GetUV0().x));
  this->SetHeight(th * (this->texture_region_->GetUV1().y - this->texture_region_->GetUV0().y));
  this->size_.width = tw;
  this->size_.height = th;
}

// =================================================================
// setter/getter
// =================================================================
void SpriteRenderer::SetTextureRegion(ITextureRegion * region, bool delete_region)
{
  if (this->delete_region_)
  {
    delete this->texture_region_;
  }
  this->texture_region_ = region;
  this->delete_region_ = delete_region;
}
