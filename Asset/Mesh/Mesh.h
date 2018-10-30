#pragma once

struct MeshData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(MeshData)
  {
    archive(vertex_format_);
    archive(vertex_size_);
    archive(vertex_count_);
    archive(data_);
    archive(indices_);
    archive(submesh_count_);
    archive(submesh_index_counts_);
    archive(submesh_polygon_counts_);
    archive(bounds_);
  }

  // =================================================================
  // Data Member
  // =================================================================
public:
  T_FIXED_UINT32 vertex_format_;
  T_FIXED_UINT32 vertex_size_;
  T_FIXED_UINT32 vertex_count_;
  std::vector<unsigned char> data_;

  std::vector<T_FIXED_UINT32> indices_;

  T_FIXED_UINT32 submesh_count_;
  std::vector<T_FIXED_UINT32> submesh_index_counts_;
  std::vector<T_FIXED_UINT32> submesh_polygon_counts_;

  Bounds bounds_;
};

/*!
 * @brief ゲーム上に表示されるオブジェクトの頂点バッファとインデックスバッファを
 * 管理するクラス。編集する機能も有している。
 */
class rcMesh : public GGAssetObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_ASSET(rcMesh, MeshData);
  GG_CREATE_FUNC(rcMesh) {}

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  virtual ~rcMesh();

  // =================================================================
  // Methods
  // =================================================================
public:
  void Clear();
  void ClearVertices(bool clear_buffer);
  void ClearIndices(bool clear_buffer);

  UniqueRef<rcMesh> Clone(bool read_only);

  void CreateVertices(T_UINT32 vertex_count, T_UINT32 polygon_count, T_UINT32 format, Vertex::PrimitiveType primitive_type = Vertex::PRIMITIVE_TRIANGLES);
  GG_INLINE void CreateVerticesWithIndex(T_UINT32 vertex_count, T_UINT32 index_count, T_UINT32 format, Vertex::PrimitiveType primitive_type = Vertex::PRIMITIVE_TRIANGLES)
  {
    CreateVertices(vertex_count, Vertex::PRIMITIVE_SURF_NUM(primitive_type, index_count), format, primitive_type);
  }
  GG_INLINE void CreateIndices(T_UINT32 index_count)
  {
    this->CreateIndices(1, &index_count);
  }
  void CreateIndices(T_UINT8 submesh_count, T_UINT32* index_counts, T_UINT32* polygon_counts = nullptr);

  void CommitChanges(bool read_only);
  void RecalculateNormals(bool save_face_normals = false);
  void RecalculateTangents();

  void SetStreamSource() const;
  void DrawSubset(T_UINT8 index) const;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual size_t GetMemorySize() const override;
  virtual size_t GetVideoMemorySize() const override;

  GG_INLINE void SetPrimitiveType(Vertex::PrimitiveType type)
  {
    this->primitive_type_ = type;
  }

  GG_INLINE T_UINT32 GetFaceCount() const
  {
    return this->polygon_count_;
  }
  GG_INLINE const TVec3f& GetFaceNormal(T_UINT32 index) const
  {
    return this->face_normals_[index];
  }

  //Vertex Buffer
  void SetVertex(T_UINT32 vertex_index, const TVec3f& vertex);
  void SetVertices(const TVec3f* vertices);
  GG_INLINE const TVec3f& GetVertex(T_UINT32 vertex_index) const
  {
    GG_ASSERT(this->HasVertices(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->vertices_[vertex_index];
  }
  GG_INLINE const TVec3f* GetVertices() const
  {
    GG_ASSERT(this->HasVertices(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->vertices_;
  }
  GG_INLINE bool HasVertices() const
  {
    return this->vertices_;
  }

  void SetNormal(T_UINT32 vertex_index, const TVec3f& normal);
  void SetNormals(const TVec3f* normals);
  GG_INLINE const TVec3f& GetNormal(T_UINT32 vertex_index) const
  {
    GG_ASSERT(this->HasNormals(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->normals_[vertex_index];
  }
  GG_INLINE const TVec3f* GetNormals() const
  {
    GG_ASSERT(this->HasNormals(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->normals_;
  }
  GG_INLINE bool HasNormals() const
  {
    return this->normals_;
  }

  void SetUv(T_UINT32 vertex_index, const TVec2f& uv);
  void SetUvs(const TVec2f* uvs);
  GG_INLINE const TVec2f& GetUv(T_UINT32 vertex_index) const
  {
    GG_ASSERT(this->HasUvs(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uvs_[vertex_index];
  }
  GG_INLINE const TVec2f* GetUvs() const
  {
    GG_ASSERT(this->HasUvs(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uvs_;
  }
  GG_INLINE bool HasUvs() const
  {
    return this->uvs_;
  }

  void SetUv2(T_UINT32 vertex_index, const TVec2f& uv2);
  void SetUv2s(const TVec2f* uv2s);
  GG_INLINE const TVec2f& GetUv2(T_UINT32 vertex_index) const
  {
    GG_ASSERT(this->HasUv2s(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uv2s_[vertex_index];
  }
  GG_INLINE const TVec2f* GetUv2s() const
  {
    GG_ASSERT(this->HasUv2s(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uv2s_;
  }
  GG_INLINE bool HasUv2s() const
  {
    return this->uv2s_;
  }

  void SetUv3(T_UINT32 vertex_index, const TVec2f& uv3);
  void SetUv3s(const TVec2f* uv3s);
  GG_INLINE const TVec2f& GetUv3(T_UINT32 vertex_index) const
  {
    GG_ASSERT(this->HasUv3s(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uv3s_[vertex_index];
  }
  GG_INLINE const TVec2f* GetUv3s() const
  {
    GG_ASSERT(this->HasUv3s(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uv3s_;
  }
  GG_INLINE bool HasUv3s() const
  {
    return this->uv3s_;
  }

  void SetUv4(T_UINT32 vertex_index, const TVec2f& uv4);
  void SetUv4s(const TVec2f* uv4s);
  GG_INLINE const TVec2f& GetUv4(T_UINT32 vertex_index) const
  {
    GG_ASSERT(this->HasUv4s(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uv4s_[vertex_index];
  }
  GG_INLINE const TVec2f* GetUv4s() const
  {
    GG_ASSERT(this->HasUv4s(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->uv4s_;
  }
  GG_INLINE bool HasUv4s() const
  {
    return this->uv4s_;
  }

  void SetTangent(T_UINT32 vertex_index, const TVec4f& tangent);
  void SetTangents(const TVec4f* tangents);
  GG_INLINE const TVec4f& GetTangent(T_UINT32 vertex_index) const
  {
    GG_ASSERT(this->HasTangents(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->tangents_[vertex_index];
  }
  GG_INLINE const TVec4f* GetTangents() const
  {
    GG_ASSERT(this->HasTangents(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->tangents_;
  }
  GG_INLINE bool HasTangents() const
  {
    return this->tangents_;
  }

  void SetColor(T_UINT32 vertex_index, const TColor& tangent);
  void SetColors(const TColor* colors);
  GG_INLINE const TColor& GetColor(T_UINT32 vertex_index) const
  {
    GG_ASSERT(this->HasColors(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->colors_[vertex_index];
  }
  GG_INLINE const TColor* GetColors() const
  {
    GG_ASSERT(this->HasColors(), "頂点フォーマットで定義されていない属性が呼び出されました");
    return this->colors_;
  }
  GG_INLINE bool HasColors() const
  {
    return this->colors_;
  }

  GG_INLINE const T_UINT32 GetVertexCount()
  {
    return this->vertex_count_;
  }

  //Index Buffer
  void SetIndex(T_UINT8 submesh_index, T_UINT32 index_index, T_UINT32 index);
  void SetIndices(T_UINT8 submesh_index, T_UINT32* indices);
  GG_INLINE T_UINT32 GetIndex(T_UINT8 submesh_index, T_UINT32 index_index) const
  {
    GG_ASSERT(submesh_index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
    return this->indices_[submesh_index][index_index];
  }

  GG_INLINE void SetIndex(T_UINT32 index_index, T_UINT32 index)
  {
    this->SetIndex(0, index_index, index);
  }
  GG_INLINE void SetIndices(T_UINT32* indices)
  {
    this->SetIndices(0, indices);
  }
  GG_INLINE T_UINT32 GetIndex(T_UINT32 index_index) const
  {
    return this->GetIndex(0, index_index);
  }

  GG_INLINE const T_UINT32* GetIndices(T_UINT8 submesh_index = 0) const
  {
    GG_ASSERT(submesh_index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
    return this->indices_[submesh_index];
  }
  GG_INLINE T_UINT32 GetIndexCount(T_UINT8 submesh_index = 0) const
  {
    GG_ASSERT(submesh_index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
    return this->index_counts_[submesh_index];
  }

  GG_INLINE Vertex::PrimitiveType GetPrimitiveType() const
  {
    return this->primitive_type_;
  }
  GG_INLINE SharedRef<rcVertexBuffer> GetVertexBuffer()
  {
    return this->vertex_buffer_;
  }
  GG_INLINE SharedRef<const rcVertexBuffer> GetVertexBuffer() const
  {
    return this->vertex_buffer_;
  }
  GG_INLINE SharedRef<rcIndexBuffer> GetIndexBuffer(T_UINT8 submesh_index = 0)
  {
    GG_ASSERT(submesh_index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
    return this->index_buffers_[submesh_index];
  }
  GG_INLINE SharedRef<const rcIndexBuffer> GetIndexBuffer(T_UINT8 submesh_index = 0) const
  {
    GG_ASSERT(submesh_index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
    return this->index_buffers_[submesh_index];
  }
  GG_INLINE T_UINT8 GetSubmeshCount() const
  {
    return this->submesh_count_;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  const rcMesh* orginal_;

  bool read_only_;

  T_UINT32 format_;
  T_UINT32 polygon_count_;
  TVec3f* face_normals_;

  T_UINT32 vertex_count_;
  TVec3f* vertices_;
  TVec3f* normals_;
  TVec2f* uvs_;
  TVec2f* uv2s_;
  TVec2f* uv3s_;
  TVec2f* uv4s_;
  //wは法線マップのミラーリングに使用(Unityを参考)
  TVec4f* tangents_;
  TColor* colors_;
  //bindPoses
  //boneWeights
  //bounds
  bool vertices_dirty_;

  T_UINT32* index_counts_;
  T_UINT32** indices_;
  bool* indices_dirties_;

  Vertex::PrimitiveType primitive_type_;
  SharedRef<rcVertexBuffer> vertex_buffer_;

  T_UINT8 submesh_count_;
  SharedRef<rcIndexBuffer>* index_buffers_;

};
