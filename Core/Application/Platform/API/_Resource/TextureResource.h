#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

/*!
 * @brief テクスチャリソースのデータ
 */
struct TextureResourceData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(TextureResourceData)
  {
    archive(bytes_per_pixel_);
    archive(width_);
    archive(height_);
    archive(format_);
    archive(data_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureResourceData()
    : bytes_per_pixel_(1)
    , width_(1)
    , height_(1)
    , format_(static_cast<T_FIXED_UINT8>(Shader::TextureFormat::kR8G8B8A8_UINT))
    , data_()
  {}

  // =================================================================
  // Data Members
  // =================================================================
public:
  T_FIXED_UINT8 bytes_per_pixel_;
  T_FIXED_UINT16 width_; // two power value
  T_FIXED_UINT16 height_; // two power value
  T_FIXED_UINT8 format_; // TextureFormat
  std::vector<unsigned char> data_;
};

/*!
 * @brief テクスチャリソースの基底クラス
 * プラットフォーム毎の処理を派生クラス側で定義する
 */
class rcTextureResource : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcTextureResource);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcTextureResource> Create(const TextureResourceData& data);

  // =================================================================
  // Method 
  // =================================================================
public:
  virtual void SetResource(T_UINT8 index) const = 0;

};