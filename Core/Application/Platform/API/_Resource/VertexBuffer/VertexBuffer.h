#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

class rcIndexBuffer;

/*!
 * @brief 頂点バッファのベースクラス。
 * プラットフォーム毎の処理を派生クラス側で定義する。
 */
class rcVertexBuffer : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT_NAME(rcVertexBuffer);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcVertexBuffer> Create(T_UINT32 vertex_count, T_UINT32 format);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcVertexBuffer() {}
  virtual ~rcVertexBuffer() {}

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) = 0;
  virtual void Unlock() = 0;

  virtual void SetStreamSource() const = 0;

  virtual void DrawIndexedPrimitive(const SharedRef<const rcIndexBuffer>& index_buffer, Vertex::PrimitiveType primitive_type) const = 0;

};