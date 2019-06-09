#include "Texture.h"

// =================================================================
// GGG Statement
// =================================================================
GG_ASSET_INIT(rcTexture, TextureData)
{
  this->width_ = data.resource_data_.width_;
  this->height_ = data.resource_data_.height_;

  this->resource_ = rcTextureResource::Create(data.resource_data_, rcTextureResource::Usage::kImmutable);
  this->view_ = rcTextureView::Create(data.view_data_, this->resource_);

  return true;
}

GG_CREATE_FUNC_IMPL(rcTexture)
{
  return true;
}

// =================================================================
// Method 
// =================================================================
void rcTexture::SetToHardware(T_UINT8 index) const
{
  if (!this->view_)
  {
    return;
  }
  this->view_->SetToHardware(index);
}
