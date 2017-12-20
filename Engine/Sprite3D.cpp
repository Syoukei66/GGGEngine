#include "Sprite3D.h"
#include "TextureRegion.h"
#include "HalEngine.h"
#include "GameObject3DRenderState.h"

Sprite3D* Sprite3D::CreateFromAsset(T_UINT8 palette_id, T_UINT16 texture_id)
{
  Sprite3D* ret = new Sprite3D();
  const ITexture* texture = HalEngine::Resource::GetTexture(palette_id, texture_id);
  TextureRegion* region = TextureRegion::CreateWithTexture(texture);
  ret->Init();
  ret->SetTextureRegion(region);
  ret->FitToTexture();
  return ret;
}

Sprite3D::Sprite3D()
  : Shape3D(new VertexBufferObject_Sprite3D())
{
  this->sprite3d_vbo_ = (VertexBufferObject_Sprite3D*)this->vbo_;
}

Sprite3D::~Sprite3D()
{
}


void Sprite3D::PreDraw(GameObject3DRenderState* state)
{
  Shape3D::PreDraw(state);
  if (!this->texture_region_)
  {
    return;
  }
  const ITexture* texture = this->texture_region_->GetTexture();
  if (this->texture_region_->UpdateTextureCoord())
  {
    this->sprite3d_vbo_->OnVertexUvDirty();
  }
  this->sprite3d_vbo_->UpdateTexture(this, this->texture_region_);
}

void Sprite3D::NativeDraw(GameObject3DRenderState* state)
{
  const void* vertexes = this->vbo_->GetVertexes();
  T_UINT32 size = this->vbo_->GetVertexesCount();
  NativeMethod::Graphics().Graphics_SetTexture(this->texture_region_->GetTexture());
  NativeMethod::Graphics().Graphics_SetMaterial(nullptr);
  NativeMethod::Graphics().Graphics_SetLightingEnabled(false);
  NativeMethod::Graphics().Graphics_DrawIndexedVertexes(
    state,
    this->vbo_->GetPrimitiveType(),
    this->vbo_->GetVertexType(),
    vertexes,
    size,
    this->vbo_->GetIndexes()
  );
}

void Sprite3D::OnVertexCoordChanged()
{
  this->sprite3d_vbo_->OnVertexCoordDirty();
}

// =================================================================
// Method
// =================================================================
void Sprite3D::OnTextureChanged()
{
  this->sprite3d_vbo_->OnVertexUvDirty();
}

void Sprite3D::FitToTexture()
{
  if (!this->texture_region_)
  {
    return;
  }
  const ITexture* texture = this->texture_region_->GetTexture();
  if (!texture)
  {
    return;
  }
  TSize textureSize = texture->GetSize();
  this->SetWidth(textureSize.width * (this->texture_region_->GetU1() - this->texture_region_->GetU0()));
  this->SetHeight(textureSize.height * (this->texture_region_->GetV1() - this->texture_region_->GetV0()));
}

void Sprite3D::SetTextureRegion(ITextureRegion* itr)
{
  if (this->texture_region_ == itr)
  {
    return;
  }
  this->texture_region_ = itr;
  this->OnTextureChanged();
}

void Sprite3D::SetWidth(T_FLOAT width)
{
  if (this->size_.width == width)
  {
    return;
  }
  this->size_.width = width;
  this->OnVertexCoordChanged();
}

void Sprite3D::SetHeight(T_FLOAT height)
{
  if (this->size_.height == height)
  {
    return;
  }
  this->size_.height = height;
  this->OnVertexCoordChanged();
}
