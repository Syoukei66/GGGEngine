#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

/*!
 * @brief ピクセルシェーダーの基底クラス
 * プラットフォーム毎の処理を派生クラス側で定義する
 */
class rcPixelShader : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcPixelShader);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcPixelShader> Create(const std::vector<unsigned char>& byte_code);

  // =================================================================
  // Method 
  // =================================================================
public:
  virtual void SetShader() const = 0;

};