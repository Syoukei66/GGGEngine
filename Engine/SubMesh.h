#pragma once

#include "MeshData.h"
#include "NativeVertexBuffer.h"
#include "NativeIndexBuffer.h"

class SubMesh
{
public:
  SubMesh(MeshData* data);
  SubMesh(const SubMesh& other);
  ~SubMesh();

  // =================================================================
  // Method
  // =================================================================
public:
  SubMesh* Clone();

  void Draw() const;

  //TVec4f* vertices_;
  //TVec3f* normals_;
  //TVec2f* uvs_;
  //TVec2f* uv2s_;
  //TVec3f* tangents_;
  //Color4F* color_;
  void Init(T_UINT16 vertices_count, T_UINT16 indices_count);
  void PrepareVertices();
  void PrepareNormals();
  void PrepareUvs();
  void PrepareUv2s();
  void PrepareTangents();
  void PrepareColors();

  void CommitChanges();

protected:
  void CommitVertices() const;
  void CommitIndices() const;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline const INativeVertexBuffer* GetVertexBuffer() const
  {
    return this->vertex_buffer_;
  }

  inline const INativeIndexBuffer* GetIndexBuffer() const
  {
    return this->index_buffer_;
  }

  void SetVertex(int vertex_index, const TVec4f& vertex);
  inline const TVec4f& GetVertex(int vertex_index) const
  {
    NATIVE_ASSERT(this->vertices_, "PrepareVertices()が呼ばれていません。");
    return this->vertices_[vertex_index];
  }
  inline bool HasVertices() const
  {
    return this->vertices_;
  }

  void SetNormal(int vertex_index, const TVec3f& normal);
  inline const TVec3f& GetNormal(int vertex_index) const
  {
    NATIVE_ASSERT(this->normals_, "PrepareNormals()が呼ばれていません。");
    return this->normals_[vertex_index];
  }
  inline bool HasNormals() const
  {
    return this->normals_;
  }

  void SetUv(int vertex_index, const TVec2f& uv);
  inline const TVec2f& GetUv(int vertex_index) const
  {
    NATIVE_ASSERT(this->uvs_, "PrepareUvs()が呼ばれていません。");
    return this->uvs_[vertex_index];
  }
  inline bool HasUvs() const
  {
    return this->uvs_;
  }

  void SetUv2(int vertex_index, const TVec2f& uv2);
  inline const TVec2f& GetUv2(int vertex_index) const
  {
    NATIVE_ASSERT(this->uv2s_, "PrepareUv2s()が呼ばれていません。");
    return this->uv2s_[vertex_index];
  }
  inline bool HasUv2s() const
  {
    return this->uv2s_;
  }

  void SetTangent(int vertex_index, const TVec3f& tangent);
  inline const TVec3f& GetTangent(int vertex_index) const
  {
    NATIVE_ASSERT(this->tangents_, "PrepareTangents()が呼ばれていません。");
    return this->tangents_[vertex_index];
  }
  inline bool HasTangents() const
  {
    return this->tangents_;
  }

  void SetColor(int vertex_index, const Color4F& tangent);
  inline const Color4F& GetColor(int vertex_index) const
  {
    NATIVE_ASSERT(this->colors_, "PrepareColors()が呼ばれていません。");
    return this->colors_[vertex_index];
  }
  inline bool HasColors() const
  {
    return this->colors_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const SubMesh* orginal_;

  INativeVertexBuffer* vertex_buffer_;
  INativeIndexBuffer* index_buffer_;

  Vertex::VertexType type_;

  /* ============================================
    nullptrではないパラメータに応じて
    バッファに渡すデータのサイズを変更できるように
   * ============================================ */
  T_UINT16 vertices_count_;
  TVec4f* vertices_;
  TVec3f* normals_;
  TVec2f* uvs_;
  TVec2f* uv2s_;
  TVec3f* tangents_;
  Color4F* colors_;
  //bindPoses
  //boneWeights
  //bounds
  bool vertices_dirty_;

  T_UINT16 indices_count_;
  T_UINT16* indices_;
  bool indices_dirty_;

};