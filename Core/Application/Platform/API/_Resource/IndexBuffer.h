#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

/*!
 * @brief インデックスバッファの基底クラス
 * API毎の処理を派生クラス側で定義する
 */
class rcIndexBuffer : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcIndexBuffer);
  GG_NATIVE_CREATE_FUNC_3(rcIndexBuffer, T_UINT32, vertex_count, T_UINT32, polygon_count, Vertex::IndexFormat, format);
  GG_NATIVE_CREATE_FUNC_4(rcIndexBuffer, T_UINT32, vertex_count, T_UINT32, polygon_count, Vertex::IndexFormat, format, void*, data);

public:
  static UniqueRef<rcIndexBuffer> Create(T_UINT32 vertex_count, T_UINT32 polygon_count, T_UINT32 max_value)
  {
    return Create(vertex_count, polygon_count, Vertex::CalcIndexFormat(max_value));
  }

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) = 0;
  virtual void Unlock() = 0;
  virtual void SetIndices() const = 0;
  virtual T_UINT32 GetVertexCount() const = 0;
  virtual T_UINT32 GetPolygonCount() const = 0;
  virtual Vertex::IndexFormat GetIndexFormat() const = 0;

};