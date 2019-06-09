#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

/*!
 * @brief 頂点情報のベースクラス
 * プラットフォーム毎の処理を派生クラス側で定義する。
 */
class rcVertexDeclaration : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcVertexDeclaration);
  GG_NATIVE_CREATE_FUNC_1(rcVertexDeclaration, T_UINT32, format);

  // =================================================================
  // Method
  // =================================================================
public:
  virtual T_UINT32 GetFormat() const = 0;
  virtual T_UINT32 GetVertexSize() const = 0;

};
