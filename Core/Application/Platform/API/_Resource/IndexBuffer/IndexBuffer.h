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

  // =================================================================
  // Factory Method
  // =================================================================
public:
  GG_INLINE static UniqueRef<rcIndexBuffer> Create(T_UINT32 vertex_count, T_UINT32 polygon_count, Vertex::IndexFormat format)
  {
    return Application::GetPlatform()->GetGraphicsAPI()->CreateIndexBuffer(vertex_count, polygon_count, format);
  }
  GG_INLINE static UniqueRef<rcIndexBuffer> Create(T_UINT32 vertex_count, T_UINT32 polygon_count, T_UINT32 max_value)
  {
    // 頂点数からインデックスフォーマットを判別する
    Vertex::IndexFormat format = Vertex::IndexFormat::INDEX_FMT_16;
    if (max_value > Limit::T_FIXED_UINT16_MAX)
    {
      format = Vertex::IndexFormat::INDEX_FMT_32;
    }
    return Create(vertex_count, polygon_count, format);
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