#include "SpriteRenderer.h"
#include "EngineAsset.h"
#include "TextureRegion.h"

// =================================================================
// Constructor / Destructor
// =================================================================
SpriteRenderer::SpriteRenderer(GameObject* entity, T_FLOAT image_scale)
  : Renderer(entity)
  , texture_region_(nullptr)
  , size_(1.0f, 1.0f)
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
void SpriteRenderer::Draw(GameObjectRenderState* state)
{
  EngineAsset::Mesh::QUAD.GetContents().SetStreamSource();
  Material* material = this->materials_[0];
  T_UINT8 pass_count = material->Begin();
  for (T_UINT8 j = 0; j < pass_count; ++j)
  {
    material->BeginPass(j);
    material->SetDefaultProperties(state);
    this->EditProperty(0, j, material);
    material->CommitChanges();
    EngineAsset::Mesh::QUAD.GetContents().DrawSubset(0);
    material->EndPass();
  }
  material->End();
}

void SpriteRenderer::EditProperty(T_UINT8 material_index, T_UINT8 pass_index, Material* material)
{
  if (!this->texture_region_)
  {
    return;
  }
  this->GetMaterial()->SetMainTexture(this->texture_region_->GetTexture());
  material->Vec2fProperty("_UV0") = this->texture_region_->GetUV0();
  material->Vec2fProperty("_UV1") = this->texture_region_->GetUV1();
  material->FloatProperty("_Width") = this->size_.width * this->image_scale_;
  material->FloatProperty("_Height") = this->size_.height * this->image_scale_;
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