#include "Texture.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(rcTexture, const TextureData& data)
{
  this->width_ = data.resource_data_.width_;
  this->height_ = data.resource_data_.height_;

  this->resource_ = rcTextureResource::Create(data.resource_data_);
  this->view_ = rcTextureView::Create(data.view_data_, this->resource_);

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
