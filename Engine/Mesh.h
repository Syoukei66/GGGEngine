#pragma once

#include <vector>
#include "NativeType.h"
#include "NativeAssert.h"
#include "Geometry.h"
#include "Color.h"
#include "NativeVertexBuffer.h"
#include "NativeIndexBuffer.h"
#include "GraphicsConstants.h"

class Mesh
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Mesh();
  ~Mesh();

private:
  //Cloneメソッドを使用すること
  Mesh(const Mesh& other) {}

  // =================================================================
  // Method
  // =================================================================
public:
  void Clear();
  void ClearVertices();
  void ClearIndices();

  Mesh* Clone();

  void CreateVertices(T_UINT32 vertex_count, T_UINT32 polygon_count, T_UINT32 format, GraphicsConstants::PrimitiveType primitive_type = GraphicsConstants::PRIMITIVE_TRIANGLES);
  inline void CreateVerticesWithIndex(T_UINT32 vertex_count, T_UINT32 index_count, T_UINT32 format, GraphicsConstants::PrimitiveType primitive_type = GraphicsConstants::PRIMITIVE_TRIANGLES)
  {
    CreateVertices(vertex_count, GraphicsConstants::PRIMITIVE_SURF_NUM(primitive_type, index_count), format, primitive_type);
  }
  inline void CreateIndices(T_UINT32 index_count)
  {
    this->CreateIndices(1, &index_count);
  }
  void CreateIndices(T_UINT8 submesh_count, T_UINT32* index_counts);

  void CommitChanges();

  void SetStreamSource() const;
  void DrawSubset(T_UINT8 index) const;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  //Vertex Buffer

  void SetVertex(T_UINT32 vertex_index, const TVec3f& vertex);
  void SetVertices(const TVec3f* vertices);
  inline const TVec3f& GetVertex(T_UINT32 vertex_index) const
  {
    NATIVE_ASSERT(this->HasVertices(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->vertices_[vertex_index];
  }
  inline const TVec3f* GetVertices() const
  {
    NATIVE_ASSERT(this->HasVertices(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->vertices_;
  }
  inline bool HasVertices() const
  {
    return this->vertices_;
  }

  void SetNormal(T_UINT32 vertex_index, const TVec3f& normal);
  void SetNormals(const TVec3f* normals);
  inline const TVec3f& GetNormal(T_UINT32 vertex_index) const
  {
    NATIVE_ASSERT(this->HasNormals(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->normals_[vertex_index];
  }
  inline const TVec3f* GetNormals() const
  {
    NATIVE_ASSERT(this->HasNormals(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->normals_;
  }
  inline bool HasNormals() const
  {
    return this->normals_;
  }

  void SetUv(T_UINT32 vertex_index, const TVec2f& uv);
  void SetUvs(const TVec2f* uvs);
  inline const TVec2f& GetUv(T_UINT32 vertex_index) const
  {
    NATIVE_ASSERT(this->HasUvs(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uvs_[vertex_index];
  }
  inline const TVec2f* GetUvs() const
  {
    NATIVE_ASSERT(this->HasUvs(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uvs_;
  }
  inline bool HasUvs() const
  {
    return this->uvs_;
  }

  void SetUv2(T_UINT32 vertex_index, const TVec2f& uv2);
  void SetUv2s(const TVec2f* uv2s);
  inline const TVec2f& GetUv2(T_UINT32 vertex_index) const
  {
    NATIVE_ASSERT(this->HasUv2s(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uv2s_[vertex_index];
  }
  inline const TVec2f* GetUv2s() const
  {
    NATIVE_ASSERT(this->HasUv2s(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uv2s_;
  }
  inline bool HasUv2s() const
  {
    return this->uv2s_;
  }

  void SetUv3(T_UINT32 vertex_index, const TVec2f& uv3);
  void SetUv3s(const TVec2f* uv3s);
  inline const TVec2f& GetUv3(T_UINT32 vertex_index) const
  {
    NATIVE_ASSERT(this->HasUv3s(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uv3s_[vertex_index];
  }
  inline const TVec2f* GetUv3s() const
  {
    NATIVE_ASSERT(this->HasUv3s(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uv3s_;
  }
  inline bool HasUv3s() const
  {
    return this->uv3s_;
  }

  void SetUv4(T_UINT32 vertex_index, const TVec2f& uv4);
  void SetUv4s(const TVec2f* uv4s);
  inline const TVec2f& GetUv4(T_UINT32 vertex_index) const
  {
    NATIVE_ASSERT(this->HasUv4s(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uv4s_[vertex_index];
  }
  inline const TVec2f* GetUv4s() const
  {
    NATIVE_ASSERT(this->HasUv4s(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uv4s_;
  }
  inline bool HasUv4s() const
  {
    return this->uv4s_;
  }

  void SetTangent(T_UINT32 vertex_index, const TVec4f& tangent);
  void SetTangents(const TVec4f* tangents);
  inline const TVec4f& GetTangent(T_UINT32 vertex_index) const
  {
    NATIVE_ASSERT(this->HasTangents(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->tangents_[vertex_index];
  }
  inline const TVec4f* GetTangents() const
  {
    NATIVE_ASSERT(this->HasTangents(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->tangents_;
  }
  inline bool HasTangents() const
  {
    return this->tangents_;
  }

  void SetColor(T_UINT32 vertex_index, const Color4F& tangent);
  void SetColors(const Color4F* colors);
  inline const Color4F& GetColor(T_UINT32 vertex_index) const
  {
    NATIVE_ASSERT(this->HasColors(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->colors_[vertex_index];
  }
  inline const Color4F* GetColors() const
  {
    NATIVE_ASSERT(this->HasColors(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->colors_;
  }
  inline bool HasColors() const
  {
    return this->colors_;
  }

  inline const T_UINT32 GetVertexCount()
  {
    return this->vertex_count_;
  }

  inline const INativeVertexBuffer* GetVertexBuffer() const
  {
    return this->vertex_buffer_;
  }

  //Index Buffer

  void SetIndex(T_UINT8 submesh_index, T_UINT32 index_index, T_UINT32 index);
  void SetIndices(T_UINT8 submesh_index, T_UINT32* indices);
  inline T_UINT32 GetIndex(T_UINT8 submesh_index, T_UINT32 index_index) const
  {
    NATIVE_ASSERT(this->submesh_count_ < submesh_index, "インデックス指定がサブメッシュの最大個数を超過しました。");
    return this->indices_[submesh_index][index_index];
  }

  inline void SetIndex(T_UINT32 index_index, T_UINT32 index)
  {
    this->SetIndex(0, index_index, index);
  }
  inline void SetIndices(T_UINT32* indices)
  {
    this->SetIndices(0, indices);
  }
  inline T_UINT32 GetIndex(T_UINT32 index_index) const
  {
    return this->GetIndex(0, index_index);
  }

  inline const T_UINT32* GetIndices(T_UINT8 submesh_index = 0) const
  {
    NATIVE_ASSERT(this->submesh_count_ < submesh_index, "インデックス指定がサブメッシュの最大個数を超過しました。");
    return this->indices_[submesh_index];
  }
  inline T_UINT32 GetIndexCount(T_UINT8 submesh_index = 0) const
  {
    NATIVE_ASSERT(this->submesh_count_ < submesh_index, "インデックス指定がサブメッシュの最大個数を超過しました。");
    return this->index_counts_[submesh_index];
  }
  inline T_UINT8 GetSubmeshCount() const
  {
    return this->submesh_count_;
  }
  inline const INativeIndexBuffer* GetIndexBuffer(T_UINT8 submesh_index = 0) const
  {
    return this->index_buffers_[submesh_index];
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const Mesh* orginal_;

  T_UINT32 format_;
  GraphicsConstants::PrimitiveType primitive_type_;
  T_UINT32 polygon_count_;

  T_UINT32 vertex_count_;
  TVec3f* vertices_;
  TVec3f* normals_;
  TVec2f* uvs_;
  TVec2f* uv2s_;
  TVec2f* uv3s_;
  TVec2f* uv4s_;
  //wは法線マップのミラーリングに使用(Unityを参考)
  TVec4f* tangents_;
  Color4F* colors_;
  //bindPoses
  //boneWeights
  //bounds
  bool vertices_dirty_;
  INativeVertexBuffer* vertex_buffer_;

  T_UINT8 submesh_count_;
  T_UINT32* index_counts_;
  T_UINT32** indices_;
  bool* indices_dirties_;
  INativeIndexBuffer** index_buffers_;
};