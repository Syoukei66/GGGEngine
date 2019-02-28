#include "DynamicTexture.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(rcDynamicTexture, const TextureData& data)
{
  this->data_ = data;
  return rcTexture::Init(data);
}

// =================================================================
// Methods
// =================================================================
void rcDynamicTexture::CreatePixels(T_FIXED_UINT16 width, T_FIXED_UINT16 height, Shader::TextureFormat format)
{
  this->data_.resource_data_.bits_per_pixel_ = 0;
  this->data_.resource_data_.block_size_ = 0;
  this->data_.resource_data_.mip_map_levels_ = 0;
  this->data_.resource_data_.width_ = width;
  this->data_.resource_data_.height_ = height;
  this->data_.resource_data_.format_ = static_cast<T_FIXED_UINT8>(format);

  this->width_ = width;
  this->height_ = height;

  this->bytes_per_pixel_ = Shader::GetBytePerPixel(format);
  this->data_.resource_data_.data_.resize(width * height * this->bytes_per_pixel_);

  this->is_new_resource_ = true;
}

void rcDynamicTexture::CommitPixels(rcTextureResource::Usage usage)
{
  if (this->is_new_resource_)
  {
    this->resource_ = rcTextureResource::Create(this->data_.resource_data_, usage);
    this->view_ = rcTextureView::Create(this->data_.view_data_, this->resource_);
    this->is_new_resource_ = false;
    return;
  }
  this->resource_->UpdateSubresource(this->data_.resource_data_);
}

void rcDynamicTexture::ClearPixels()
{
  this->data_.resource_data_.data_.clear();
  this->resource_ = nullptr;
  this->view_ = nullptr;
}

SharedRef<rcTexture> rcDynamicTexture::MoveStatic()
{
  const SharedRef<rcTexture>& ret = rcTexture::Create();
  GG_ASSERT_IS_NULL(this->resource_);
  GG_ASSERT_IS_NULL(this->view_);
  ret->resource_ = std::move(this->resource_);
  ret->view_ = std::move(this->view_);
  ret->width_ = this->width_;
  ret->height_ = this->height_;
  return ret;
}
