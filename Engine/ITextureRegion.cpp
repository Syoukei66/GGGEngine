#include "ITextureRegion.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ITextureRegion::ITextureRegion()
  : texture_(nullptr)
  , texture_region_(0.0f, 0.0f, 1.0f, 1.0f)
  , uv0_(0.0f, 0.0f)
  , uv1_(1.0f, 1.0f)
  , texture_coord_dirty_(true)
{}

// =================================================================
// Method
// =================================================================
void ITextureRegion::Init()
{
  this->texture_coord_dirty_ = true;
  this->texture_region_ = TAreaf(0.0f, 0.0f, 1.0f, 1.0f);
  this->uv0_ = TVec2f(0.0f, 0.0f);
  this->uv1_ = TVec2f(1.0f, 1.0f);
}

void ITextureRegion::FitToTexture()
{
  if (!this->texture_)
  {
    return;
  }
  this->SetWidth((T_FLOAT)this->texture_->GetWidth());
  this->SetHeight((T_FLOAT)this->texture_->GetHeight());
}

bool ITextureRegion::UpdateTextureCoord()
{
  if (!this->texture_coord_dirty_)
  {
    return false;
  }
  const INativeTexture* texture = this->GetTexture();
  if (!texture)
  {
    return true;
  }
  this->OnUpdateTextureCoord(texture);
  this->texture_coord_dirty_ = false;
  return true;
}

void ITextureRegion::OnTextureCoordDirty()
{
  this->texture_coord_dirty_ = true;
}

// =================================================================
// setter/getter
// =================================================================
void ITextureRegion::SetX(T_FLOAT x)
{
  if (this->texture_region_.pos.x == x)
  {
    return;
  }
  this->texture_region_.pos.x = x;
  this->OnTextureCoordDirty();
}

void ITextureRegion::SetY(T_FLOAT y)
{
  if (this->texture_region_.pos.y == y)
  {
    return;
  }
  this->texture_region_.pos.y = y;
  this->OnTextureCoordDirty();
}

void ITextureRegion::SetWidth(T_FLOAT width)
{
  if (this->texture_region_.size.width == width)
  {
    return;
  }
  this->texture_region_.size.width = width;
  this->OnTextureCoordDirty();
}

void ITextureRegion::SetHeight(T_FLOAT height)
{
  if (this->texture_region_.size.height == height)
  {
    return;
  }
  this->texture_region_.size.height = height;
  this->OnTextureCoordDirty();
}
