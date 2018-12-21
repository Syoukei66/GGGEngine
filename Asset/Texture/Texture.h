#pragma once

#include <Core/Application/Platform/API/_Resource/TextureResource.h>
#include <Core/Application/Platform/API/_Resource/TextureSampler.h>

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
    archive(sampler_data_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureData()
    : resource_data_()
    , sampler_data_()
  {}

  // =================================================================
  // Data Members
  // =================================================================
public:
  TextureResourceData resource_data_;
  TextureSamplerData sampler_data_;
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
  GG_ASSET(rcTexture, TextureData);

  // =================================================================
  // Method 
  // =================================================================
public:
  void SetToHardware(T_UINT8 index) const;

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

  // =================================================================
  // Data Members
  // =================================================================
protected:
  SharedRef<rcTextureResource> resource_;
  SharedRef<rcTextureSampler> sampler_;

  T_UINT16 width_;
  T_UINT16 height_;
};