#include "TextureRegion.h"

// =================================================================
// Factory Method
// =================================================================
rcTextureRegion* rcTextureRegion::CreateWithMaterial(const rcMaterial* material)
{
  return rcTextureRegion::CreateWithTexture(material->GetMainTexture());
}

rcTextureRegion* rcTextureRegion::CreateWithTexture(const rcTexture* texture)
{
  rcTextureRegion* ret = rcTextureRegion::Create();
  ret->Init();
  ret->SetTexture(texture);
  ret->FitToTexture();
  return ret;
}

rcTextureRegion* rcTextureRegion::Create()
{
  rcTextureRegion* ret = new rcTextureRegion();
  ret->Resource::Init();
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcTextureRegion::rcTextureRegion()
  : texture_(nullptr)
  , texture_region_(0.0f, 0.0f, 1.0f, 1.0f)
  , uv0_(0.0f, 0.0f)
  , uv1_(1.0f, 1.0f)
  , texture_coord_dirty_(true)
{}

// =================================================================
// Method
// =================================================================
void rcTextureRegion::Init()
{
  this->texture_coord_dirty_ = true;
  this->texture_region_ = TAreaf(0.0f, 0.0f, 1.0f, 1.0f);
  this->uv0_ = TVec2f(0.0f, 0.0f);
  this->uv1_ = TVec2f(1.0f, 1.0f);
}

void rcTextureRegion::FitToTexture()
{
  if (!this->texture_)
  {
    return;
  }
  this->SetWidth((T_FLOAT)this->texture_->GetWidth());
  this->SetHeight((T_FLOAT)this->texture_->GetHeight());
}

bool rcTextureRegion::UpdateTextureCoord()
{
  if (!this->texture_coord_dirty_)
  {
    return false;
  }
  const rcTexture* texture = this->GetTexture();
  if (!texture)
  {
    return true;
  }
  this->OnUpdateTextureCoord(texture);
  this->texture_coord_dirty_ = false;
  return true;
}

void rcTextureRegion::OnTextureCoordDirty()
{
  this->texture_coord_dirty_ = true;
}

void rcTextureRegion::OnUpdateTextureCoord(const rcTexture* texture)
{
  const T_FLOAT tw = (T_FLOAT)texture->GetTwoPoweredWidth();
  const T_FLOAT th = (T_FLOAT)texture->GetTwoPoweredHeight();
  const T_FLOAT x = this->GetX();
  const T_FLOAT y = this->GetY();
  const T_FLOAT w = this->GetWidth();
  const T_FLOAT h = this->GetHeight();
  this->SetU0(x / tw);
  this->SetV0(y / th);
  this->SetU1((x + w) / tw);
  this->SetV1((y + h) / th);
}

// =================================================================
// setter/getter
// =================================================================
void rcTextureRegion::SetTexture(const rcTexture* texture)
{
  texture->Retain();
  if (this->texture_)
  {
    this->texture_->Release();
  }
  this->texture_ = texture;
}

void rcTextureRegion::SetX(T_FLOAT x)
{
  if (this->texture_region_.pos.x == x)
  {
    return;
  }
  this->texture_region_.pos.x = x;
  this->OnTextureCoordDirty();
}

void rcTextureRegion::SetY(T_FLOAT y)
{
  if (this->texture_region_.pos.y == y)
  {
    return;
  }
  this->texture_region_.pos.y = y;
  this->OnTextureCoordDirty();
}

void rcTextureRegion::SetWidth(T_FLOAT width)
{
  if (this->texture_region_.size.width == width)
  {
    return;
  }
  this->texture_region_.size.width = width;
  this->OnTextureCoordDirty();
}

void rcTextureRegion::SetHeight(T_FLOAT height)
{
  if (this->texture_region_.size.height == height)
  {
    return;
  }
  this->texture_region_.size.height = height;
  this->OnTextureCoordDirty();
}
