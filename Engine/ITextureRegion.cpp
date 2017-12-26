#include "ITextureRegion.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ITextureRegion::ITextureRegion()
  : texture_(NULL)
  , texture_region_(0.0f, 0.0f, 1.0f, 1.0f)
  , u0_(0.0f)
  , v0_(0.0f)
  , u1_(1.0f)
  , v1_(1.0f)
  , texture_coord_dirty_(true)
{}

// =================================================================
// Method
// =================================================================
void ITextureRegion::Init()
{
  this->texture_coord_dirty_ = true;
  this->texture_region_ = TAreaf(0.0f, 0.0f, 1.0f, 1.0f);
  this->u0_ = 0.0f;
  this->v0_ = 0.0f;
  this->u1_ = 1.0f;
  this->v1_ = 1.0f;
}

void ITextureRegion::FitToTexture()
{
  this->SetWidth((T_FLOAT)this->GetTexture()->GetWidth());
  this->SetHeight((T_FLOAT)this->GetTexture()->GetHeight());
}

bool ITextureRegion::UpdateTextureCoord()
{
  if (!this->texture_coord_dirty_)
  {
    return false;
  }
  this->OnUpdateTextureCoord();
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
T_FLOAT ITextureRegion::GetU0()
{
  this->UpdateTextureCoord();
  return this->u0_;
}

T_FLOAT ITextureRegion::GetV0()
{
  this->UpdateTextureCoord();
  return this->v0_;
}

T_FLOAT ITextureRegion::GetU1()
{
  this->UpdateTextureCoord();
  return this->u1_;
}

T_FLOAT ITextureRegion::GetV1()
{
  this->UpdateTextureCoord();
  return this->v1_;
}

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
