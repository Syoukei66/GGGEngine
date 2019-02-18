#pragma once

#include "Texture.h"

class rcDynamicTexture : public rcTexture
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcDynamicTexture);
  GG_ASSET(rcDynamicTexture, TextureData);
  GG_CREATE_FUNC(rcDynamicTexture) { return rcTexture::Init(); }
  GG_DESTRUCT_FUNC(rcDynamicTexture);

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief ピクセルマップを作成する
   */
  void CreatePixels(T_FIXED_UINT16 width, T_FIXED_UINT16 height, Shader::TextureFormat format);

  /*!
   * @brief ピクセルマップの変更を確定する
   */
  void CommitPixels(rcTextureResource::Usage usage = rcTextureResource::Usage::kUltraDynamic);

  /*!
   * @brief ピクセルマップを削除する
   */
  void ClearPixels();

  /*!
   * @brief DynamicTextureを複製する
   */
  GG_INLINE SharedRef<rcDynamicTexture> Clone() const
  {
    return rcDynamicTexture::Create(this->data_);
  }

  /*!
   * @brief 編集不可のクローンを作成する
   */
  GG_INLINE SharedRef<rcTexture> CloneStatic() const
  {
    return rcTexture::Create(this->data_);
  }

  /*!
   * @brief 編集不可のクローンにデータを移動する。
   * CloneStaticよりも低コストだがこのメソッドを使用後、
   * このDynamicTextureは使用不可になる。
   * immutableにcommitしたいのであればCommitPixelsよりこちらを使用した方がいい
   */
  SharedRef<rcTexture> MoveStatic();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  /*!
   * @brief ピクセルの情報を取得する。
   * データ形式はピクセルフォーマットによって異なる
   * @param x テクセルX座標
   * @param y テクセルY座標
   * @return 指定された座標のピクセルデータの先頭ポインタ
   */
  GG_INLINE unsigned char* GetPixel(const T_UINT16 x, T_UINT16 y)
  {
    return &this->data_.resource_data_.data_[(this->width_ * y + x) * this->bytes_per_pixel_];
  }

  /*!
   * @brief ピクセルの情報を取得する。
   * データ形式はピクセルフォーマットによって異なる
   * @param x テクセルX座標
   * @param y テクセルY座標
   * @return 指定された座標のピクセルデータの先頭ポインタ
   */
  GG_INLINE const unsigned char* GetPixel(const T_UINT16 x, T_UINT16 y) const
  {
    return &this->data_.resource_data_.data_[(this->width_ * y + x) * this->bytes_per_pixel_];
  }

  // =================================================================
  // Data Members
  // =================================================================
protected:
  TextureData data_;
  T_UINT8 bytes_per_pixel_;
  bool is_new_resource_;

};
