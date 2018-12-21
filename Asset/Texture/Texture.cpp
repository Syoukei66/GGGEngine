#include "Texture.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(rcTexture, const TextureData& data)
{
  this->width_ = data.resource_data_.width_;
  this->height_ = data.resource_data_.height_;

  this->resource_ = rcTextureResource::Create(data.resource_data_);
  //this->sampler_ = rcTextureSampler::Create(data.sampler_data_);

  return true;
}

// =================================================================
// Method 
// =================================================================
void rcTexture::SetToHardware(T_UINT8 index) const
{
  this->resource_->SetResource(index);
  //this->sampler_->SetSampler(index);
}
