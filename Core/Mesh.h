#pragma once

#include "NativeType.h"
#include "Resource.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

class rcMesh : public Resource
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcMesh();
  virtual ~rcMesh();

  // =================================================================
  // Methods
  // =================================================================
public:
  void SetStreamSource() const;
  void DrawSubset(T_UINT8 index) const;

  // =================================================================
  // Getter / Setter
  // =================================================================
public:
  inline Graphics::PrimitiveType GetPrimitiveType() const
  {
    return this->primitive_type_;
  }
  inline rcVertexBuffer* GetVertexBuffer()
  {
    return this->vertex_buffer_;
  }
  inline const rcVertexBuffer* GetVertexBuffer() const
  {
    return this->vertex_buffer_;
  }
  inline rcIndexBuffer* GetIndexBuffer(T_UINT8 submesh_index)
  {
    NATIVE_ASSERT(submesh_index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
    return this->index_buffers_[submesh_index];
  }
  inline const rcIndexBuffer* GetIndexBuffer(T_UINT8 submesh_index = 0) const
  {
    NATIVE_ASSERT(submesh_index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
    return this->index_buffers_[submesh_index];
  }
  inline T_UINT8 GetSubmeshCount() const
  {
    return this->submesh_count_;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  Graphics::PrimitiveType primitive_type_;
  rcVertexBuffer* vertex_buffer_;

  T_UINT8 submesh_count_;
  rcIndexBuffer** index_buffers_;
};
