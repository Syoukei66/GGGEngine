#pragma once

#include "IMesh.h"
#include "Mesh.h"

#include "NativeVertexBuffer.h"
#include "NativeIndexBuffer.h"

class StaticMesh : public IMesh
{
public:
  StaticMesh(INativeVertexBuffer* vertex_buffer, INativeIndexBuffer** index_buffers, T_UINT8 submesh_count);
  ~StaticMesh();

private:
  //��������K�v�����Ȃ��ׁB�ҏW�\��Mesh�ɕϊ��������ꍇ��CloneDynamic���g�p����B
  StaticMesh(const StaticMesh& other) {}

public:
  Mesh* CloneDynamic(bool source_delete);


public:
  virtual void SetStreamSource() const override;
  virtual void DrawSubset(T_UINT8 index) const override;

private:
  INativeVertexBuffer* vertex_buffer_;

  T_UINT8 submesh_count_;
  INativeIndexBuffer** index_buffers_;
};