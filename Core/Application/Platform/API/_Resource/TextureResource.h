#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

/*!
 * @brief 各データ作成済みのテクスチャリソースのデータ
 */
struct TextureResourceData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(TextureResourceData)
  {
    archive(bits_per_pixel_);
    archive(block_size_);
    archive(mip_map_levels_);
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
    : bits_per_pixel_(0)
    , block_size_(0)
    , mip_map_levels_(0)
    , width_(1)
    , height_(1)
    , format_(static_cast<T_FIXED_UINT8>(Shader::TextureFormat::kRGB))
    , data_()
  {}

  // =================================================================
  // Data Members
  // =================================================================
public:
  T_FIXED_UINT8 bits_per_pixel_; // 0の場合実行時に計算される
  T_FIXED_UINT8 block_size_;     // 0の場合実行時に計算される
  T_FIXED_UINT8 mip_map_levels_; // 0の場合実行時に計算される
  T_FIXED_UINT16 width_; // two power value
  T_FIXED_UINT16 height_; // two power value
  T_FIXED_UINT8 format_; // TextureFormat

  // bits_per_pixel_が1以上の場合はプラットフォーム向けに最適化されている為、
  // バイト配列を用いたピクセルへのアクセスは使用できない。（未定義）
  // bits_per_pixel_が0の場合は非最適化データなので
  // その場合はformat_を引数にShader::GetBytePerPixelを用いる事で
  // 実際のピクセル当たりのバイト数が取得できる。
  std::vector<unsigned char> data_;
};

/*!
 * @brief テクスチャリソースの基底クラス
 * プラットフォーム毎の処理を派生クラス側で定義する
 */
class rcTextureResource : public GGAPIResourceObject
{
public:
  // テクスチャの用途
  enum class Usage
  {
    // 変更しない
    kImmutable,

    // 変更する
    // TODO:Map/Unmap UpdateSubresourceのコストに関するリサーチをして
    // UpdateSubresourceでのリソースの更新に意義を感じたら実装する
    //kDynamic,

    // ほぼ毎フレーム変更する
    kUltraDynamic,
  };

  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcTextureResource);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcTextureResource> Create(const TextureResourceData& data, Usage usage = Usage::kImmutable);

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void UpdateSubresource(const TextureResourceData& data, Usage usage = Usage::kImmutable) = 0;

};