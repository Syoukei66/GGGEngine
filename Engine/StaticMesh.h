#pragma once

#include "IMesh.h"
#include "Mesh.h"

#include "../Common/NativeVertexBuffer.h"
#include "../Common/NativeIndexBuffer.h"

class StaticMesh : public IMesh
{
public:
  StaticMesh(INativeVertexBuffer* vertex_buffer, INativeIndexBuffer** index_buffers, T_UINT8 submesh_count);
  ~StaticMesh();

private:
  //複製する必要性がない為。編集可能なMeshに変換したい場合はCloneDynamicを使用する。
  StaticMesh(const StaticMesh& other) {}

public:
  Mesh* CloneDynamic(bool source_delete);

public:
  virtual void SetStreamSource() const override;
  virtual void DrawSubset(T_UINT8 index) const override;

public:
  inline INativeVertexBuffer* GetVertexBuffer()
  {
    return this->vertex_buffer_;
  }
  inline const INativeVertexBuffer* GetVertexBuffer() const
  {
    return this->vertex_buffer_;
  }
  inline INativeIndexBuffer* GetIndexBuffer(T_UINT8 submesh_index)
  {
    return this->index_buffers_[submesh_index];
  }
  inline const INativeIndexBuffer* GetIndexBuffer(T_UINT8 submesh_index) const
  {
    return this->index_buffers_[submesh_index];
  }
  inline T_UINT8 GetSubmeshCount() const
  {
    return this->submesh_count_;
  }

private:
  INativeVertexBuffer* vertex_buffer_;

  T_UINT8 submesh_count_;
  INativeIndexBuffer** index_buffers_;
};