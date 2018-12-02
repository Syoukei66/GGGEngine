#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

class rcIndexBuffer;
class rcVertexDeclaration;
class rcShader;

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

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcVertexBuffer> Create(T_UINT32 size);
  static UniqueRef<rcVertexBuffer> Create(T_UINT32 size, void* data);

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) = 0;
  virtual void Unlock() = 0;

  virtual void SetStreamSource(const SharedRef<const rcVertexDeclaration>& declaration) const = 0;

};