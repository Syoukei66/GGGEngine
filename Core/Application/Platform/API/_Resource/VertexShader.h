#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

class rcVertexDeclaration;

/*!
 * @brief ピクセルシェーダーの基底クラス
 * プラットフォーム毎の処理を派生クラス側で定義する
 */
class rcVertexShader : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcVertexShader);
  GG_NATIVE_CREATE_FUNC_1(rcVertexShader, const std::vector<unsigned char>&, byte_code);
  
  // =================================================================
  // Method 
  // =================================================================
public:
  virtual void SetInputLayout(const SharedRef<const rcVertexDeclaration>& declaration) const = 0;
  virtual void SetShader() const = 0;

};