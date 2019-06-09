#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

class rcVertexDeclaration;

/*!
 * @brief 頂点バッファのベースクラス。
 * プラットフォーム毎の処理を派生クラス側で定義する。
 */
class rcVertexBuffer : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcVertexBuffer);
  GG_NATIVE_CREATE_FUNC_1(rcVertexBuffer, T_UINT32, size);
  GG_NATIVE_CREATE_FUNC_2(rcVertexBuffer, T_UINT32, size, void*, data);

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) = 0;
  virtual void Unlock() = 0;

  virtual void SetStreamSource(const SharedRef<const rcVertexDeclaration>& declaration) const = 0;

};