#include "SpriteRenderer.h"
#include "EngineAsset.h"
#include "TextureRegion.h"

// =================================================================
// Constructor / Destructor
// =================================================================
SpriteRenderer::SpriteRenderer(GameObject* entity, T_FLOAT image_scale)
  : Renderer(entity)
  , texture_region_(nullptr)
  , image_scale_(image_scale)
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
  if (this->texture_region_)
  {
    this->GetMaterial()->SetMainTexture(this->texture_region_->GetTexture());
    //const Texture* texture = this->GetTextureRegion()->GetTexture();
    //const T_FLOAT tw = (T_FLOAT)texture->GetWidth() * this->image_scale_;
    //const T_FLOAT th = (T_FLOAT)texture->GetHeight() * this->image_scale_;
    //this->SetWidth(tw * (this->texture_region_->GetUV1().x - this->texture_region_->GetUV0().x));
    //this->SetHeight(th * (this->texture_region_->GetUV1().y - this->texture_region_->GetUV0().y));
  }
  material->Vec2fProperty("_UV0") = this->texture_region_->GetUV0();
  material->Vec2fProperty("_UV1") = this->texture_region_->GetUV1();
  material->FloatProperty("_Width") = this->size_.width;
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
  const INativeTexture* texture = this->GetTextureRegion()->GetTexture();
  if (!texture)
  {
    return;
  }
  this->GetTextureRegion()->FitToTexture();
  const T_FLOAT tw = (T_FLOAT)texture->GetWidth() * this->image_scale_;
  const T_FLOAT th = (T_FLOAT)texture->GetHeight() * this->image_scale_;
  this->SetWidth(tw * (this->texture_region_->GetUV1().x - this->texture_region_->GetUV0().x));
  this->SetHeight(th * (this->texture_region_->GetUV1().y - this->texture_region_->GetUV0().y));
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

void SpriteRenderer::SetTexture(const INativeTexture* texture)
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
