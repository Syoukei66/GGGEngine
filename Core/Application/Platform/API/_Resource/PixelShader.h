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
  GG_NATIVE_CREATE_FUNC_1(rcPixelShader, const std::vector<unsigned char>&, byte_code);

  // =================================================================
  // Method 
  // =================================================================
public:
  virtual void SetShader() const = 0;

};