#pragma once

#include <Core/Application/Platform/API/_Resource/TextureResource.h>

/*!
 * @brief シェーダーリソースとしてのテクスチャのデータ
 */
struct TextureData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(TextureData)
  {
    archive(resource_data_);
    archive(filter_);
    archive(address_u_);
    archive(address_v_);
    archive(aniso_level_);
    archive(fade_start_);
    archive(fade_end_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureData()
    : resource_data_()
    , filter_(static_cast<T_FIXED_UINT8>(Shader::TextureFilter::kBilinear))
    , address_u_(static_cast<T_FIXED_UINT8>(Shader::TextureAddress::kClamp))
    , address_v_(static_cast<T_FIXED_UINT8>(Shader::TextureAddress::kClamp))
    , aniso_level_(1)
    , fade_start_(0)
    , fade_end_(0)
  {}

  // =================================================================
  // Data Members
  // =================================================================
public:
  TextureResourceData resource_data_;
  T_FIXED_UINT8 filter_; // TextureFilter
  T_FIXED_UINT8 address_u_; // TextureAddress
  T_FIXED_UINT8 address_v_; // TextureAddress
  T_FIXED_UINT8 aniso_level_;

  // start == end == 0で無効(デフォルト)
  T_FIXED_UINT8 fade_start_;
  T_FIXED_UINT8 fade_end_;
};

/*!
 * @brief シェーダーリソースとしての2Dテクスチャ
 */
class rcTexture : public GGAssetObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcTexture);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcTexture> Create(const SharedRef<rcTextureResource>& texture_resource);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcTexture(const SharedRef<rcTextureResource>& texture_resource);
  virtual ~rcTexture();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<rcTextureResource> GetTextureResource()
  {
    return this->resource_;
  }
  GG_INLINE SharedRef<const rcTextureResource> GetTextureResource() const
  {
    return this->resource_;
  }

  GG_INLINE T_UINT16 GetWidth() const
  {
    return this->width_;
  }
  GG_INLINE T_UINT16 GetHeight() const
  {
    return this->height_;
  }
  GG_INLINE T_UINT16 GetTwoPoweredWidth() const
  {
    return two_powered_width_;
  }
  GG_INLINE T_UINT16 GetTwoPoweredHeight() const
  {
    return two_powered_height_;
  }

  // =================================================================
  // Data Members
  // =================================================================
protected:
  SharedRef<rcTextureResource> resource_;

  T_UINT16 width_;
  T_UINT16 height_;

  T_UINT16 two_powered_width_;
  T_UINT16 two_powered_height_;

  Shader::TextureFilter filter_;
  Shader::TextureAddress address_u_;
  Shader::TextureAddress address_v_;
  T_UINT8 aniso_level_;

  T_UINT8 fade_start_;
  T_UINT8 fade_end_;

};