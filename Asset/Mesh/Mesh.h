#pragma once

#include <Core/Application/Platform/API/_Resource/VertexBuffer/VertexBuffer.h>
#include <Core/Application/Platform/API/_Resource/VertexDeclaration/VertexDeclaration.h>
#include <Core/Application/Platform/API/_Resource/IndexBuffer/IndexBuffer.h>

/*!
 * @brief 静的なメッシュのデータ
 * データはそのままバッファに格納できるようになっている
 * Mesh側に頂点の成分毎のデータが残らないので、Decomposeを呼び出す必要がある
 */
struct StaticMeshData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(StaticMeshData)
  {
    archive(vertex_format_);
    archive(vertex_count_);
    archive(vertex_data_);

    archive(index_datas_);
    archive(index_formats_);
    archive(index_counts_);
    archive(polygon_counts_);

    archive(bounds_);
  }

  // =================================================================
  // Data Member
  // =================================================================
public:
  T_FIXED_UINT32 vertex_format_;
  T_FIXED_UINT32 vertex_count_;
  std::vector<unsigned char> vertex_data_;

  std::vector<std::vector<unsigned char>> index_datas_;
  std::vector<T_FIXED_UINT8> index_formats_;
  std::vector<T_FIXED_UINT32> index_counts_;
  std::vector<T_FIXED_UINT32> polygon_counts_;

  Bounds bounds_;
};

/*!
 * @brief 動的なメッシュのデータ
 * データは頂点の各成分に格納される。
 * ロード直後はCPU側にしかデータが存在しないので、
 * GPUへ転送し実際に使用できるようにするにはCommitChangesを呼び出す必要がある
 */
struct DynamicMeshData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(DynamicMeshData)
  {
    archive(vertex_format_);
    archive(vertex_count_);
    archive(vertex_data_);

    archive(index_datas_);
    archive(index_formats_);
    archive(index_counts_);
    archive(polygon_counts_);

    archive(bounds_);
  }

  // =================================================================
  // Data Member
  // =================================================================
public:
  T_FIXED_UINT32 vertex_format_;
  T_FIXED_UINT32 vertex_count_;
  std::vector<unsigned char> vertex_data_;

  std::vector<std::vector<unsigned char>> index_datas_;
  std::vector<T_FIXED_UINT8> index_formats_;
  std::vector<T_FIXED_UINT32> index_counts_;
  std::vector<T_FIXED_UINT32> polygon_counts_;

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
  GG_OBJECT(rcMesh);
  GG_ASSET(rcMesh, StaticMeshData);
  GG_CREATE_FUNC(rcMesh) { return true;  }
  GG_DESTRUCT_FUNC(rcMesh);

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief 頂点情報、インデックス情報、バッファ等の全てのデータを削除する
   */
  void Clear();

  /*!
   * @brief 頂点情報を全て削除する
   * @param clear_buffer 頂点バッファも削除する
   */
  void ClearVertices(bool clear_buffer);

  /*!
   * @brief インデックス情報を全て削除する
   * @param clear_buffer インデックスバッファも削除する
   */
  void ClearIndices(bool clear_buffer);

  /*!
   * @brief Mesh内の頂点、インデックス情報を静的なメッシュデータとしてデータ化する
   */
  void ConvertToData(StaticMeshData* dest);

  /*!
   * @brief Mesh内の頂点、インデックス情報を動的なメッシュデータとしてデータ化する
   */
  void ConvertToData(DynamicMeshData* dest);

  /*!
   * @brief Meshを複製する
   * @param 複製先に頂点の各属性のデータなどを残すかどうか
   */
  UniqueRef<rcMesh> Clone(bool clear_readable_data);

  /*!
   * @brief 頂点バッファを作成する。
   * @param vertex_count 頂点数
   * @param polygon_count ポリゴン数
   * @param format 頂点フォーマット
   * @param primitive_type プリミティブの種類
   */
  void CreateVertices(T_UINT32 vertex_count, T_UINT32 polygon_count, T_UINT32 format, Vertex::PrimitiveType primitive_type = Vertex::PrimitiveType::TRIANGLES);

  /*!
   * @brief 頂点バッファを作成する。
   * ポリゴン数をインデックス数とプリミティブの種類から自動で計算する。
   * @param vertex_count 頂点数
   * @param index_count インデックス数
   * @param format 頂点フォーマット
   * @param primitive_type プリミティブの種類
   */
  GG_INLINE void CreateVerticesWithIndex(T_UINT32 vertex_count, T_UINT32 index_count, T_UINT32 format, Vertex::PrimitiveType primitive_type = Vertex::PrimitiveType::TRIANGLES)
  {
    CreateVertices(vertex_count, Vertex::PRIMITIVE_SURF_NUM(primitive_type, index_count), format, primitive_type);
  }

  /*!
   * @brief インデックスバッファを追加し、サブメッシュを作成する。
   * 必ず頂点バッファを作成した後呼び出すように。
   * @param index_count インデックス数
   * @param polygon_count ポリゴン数
   */
  T_UINT32 AddIndices(T_UINT32 index_count, T_UINT32 polygon_count);

  /*!
   * @brief インデックスバッファを追加し、サブメッシュを作成する。
   * ポリゴン数をインデックス数とプリミティブの種類から自動で計算する。
   * 必ず頂点バッファを作成した後呼び出すように。
   * @param index_count インデックス数
   */
  GG_INLINE T_UINT32 AddIndices(T_UINT32 index_count)
  {
    return this->AddIndices(index_count, Vertex::PRIMITIVE_SURF_NUM(this->primitive_type_, index_count));
  }

  /*!
   * @brief 頂点、インデックス情報を確定し、GPUに転送する
   * @param clear_readable_data 読み込み可能なデータ（頂点情報など）を削除するかどうか
   */
  void CommitChanges(bool clear_readable_data);

  /*!
   * @brief 頂点、インデックス情報をバッファから取得し、再び編集可能なメッシュにする。
   * @param clear_buffer_data バッファを削除するかどうか
   */
  void DecomposeBufferDatas(bool clear_buffer_data);

  /*!
   * @brief 法線を再計算する
   * @param save_face_normals 面法線情報を保持しておくかどうか
   */
  void RecalculateNormals(bool save_face_normals = false);

  /*!
   * @brief タンジェントベクトルを再計算する
   */
  void RecalculateTangents();

  void SetStreamSource() const;
  void DrawSubset(T_UINT8 index) const;

  // =================================================================
  // Setter / Getter
  // =================================================================
private:
  GG_INLINE void VertexAssert(bool has) const
  {
    GG_ASSERT(this->readable_, "メッシュのデータを読み込めません");
    GG_ASSERT(has, "頂点フォーマットで定義されていない属性が呼び出されました");
  }

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
    this->VertexAssert(this->HasVertices());
    return this->vertices_[vertex_index];
  }
  GG_INLINE const TVec3f* GetVertices() const
  {
    this->VertexAssert(this->HasVertices());
    return this->vertices_.data();
  }
  GG_INLINE bool HasVertices() const
  {
    return !this->vertices_.empty();
  }

  void SetNormal(T_UINT32 vertex_index, const TVec3f& normal);
  void SetNormals(const TVec3f* normals);
  GG_INLINE const TVec3f& GetNormal(T_UINT32 vertex_index) const
  {
    this->VertexAssert(this->HasNormals());
    return this->normals_[vertex_index];
  }
  GG_INLINE const TVec3f* GetNormals() const
  {
    this->VertexAssert(this->HasNormals());
    return this->normals_.data();
  }
  GG_INLINE bool HasNormals() const
  {
    return !this->normals_.empty();
  }

  void SetUv(T_UINT32 vertex_index, const TVec2f& uv);
  void SetUvs(const TVec2f* uvs);
  GG_INLINE const TVec2f& GetUv(T_UINT32 vertex_index) const
  {
    this->VertexAssert(this->HasUvs());
    return this->uvs_[vertex_index];
  }
  GG_INLINE const TVec2f* GetUvs() const
  {
    this->VertexAssert(this->HasUvs());
    return this->uvs_.data();
  }
  GG_INLINE bool HasUvs() const
  {
    return !this->uvs_.empty();
  }

  void SetUv2(T_UINT32 vertex_index, const TVec2f& uv2);
  void SetUv2s(const TVec2f* uv2s);
  GG_INLINE const TVec2f& GetUv2(T_UINT32 vertex_index) const
  {
    this->VertexAssert(this->HasUv2s());
    return this->uv2s_[vertex_index];
  }
  GG_INLINE const TVec2f* GetUv2s() const
  {
    this->VertexAssert(this->HasUv2s());
    return this->uv2s_.data();
  }
  GG_INLINE bool HasUv2s() const
  {
    return !this->uv2s_.empty();
  }

  void SetUv3(T_UINT32 vertex_index, const TVec2f& uv3);
  void SetUv3s(const TVec2f* uv3s);
  GG_INLINE const TVec2f& GetUv3(T_UINT32 vertex_index) const
  {
    this->VertexAssert(this->HasUv3s());
    return this->uv3s_[vertex_index];
  }
  GG_INLINE const TVec2f* GetUv3s() const
  {
    this->VertexAssert(this->HasUv3s());
    return this->uv3s_.data();
  }
  GG_INLINE bool HasUv3s() const
  {
    return !this->uv3s_.empty();
  }

  void SetUv4(T_UINT32 vertex_index, const TVec2f& uv4);
  void SetUv4s(const TVec2f* uv4s);
  GG_INLINE const TVec2f& GetUv4(T_UINT32 vertex_index) const
  {
    this->VertexAssert(this->HasUv4s());
    return this->uv4s_[vertex_index];
  }
  GG_INLINE const TVec2f* GetUv4s() const
  {
    this->VertexAssert(this->HasUv4s());
    return this->uv4s_.data();
  }
  GG_INLINE bool HasUv4s() const
  {
    return !this->uv4s_.empty();
  }

  void SetTangent(T_UINT32 vertex_index, const TVec4f& tangent);
  void SetTangents(const TVec4f* tangents);
  GG_INLINE const TVec4f& GetTangent(T_UINT32 vertex_index) const
  {
    this->VertexAssert(this->HasTangents());
    return this->tangents_[vertex_index];
  }
  GG_INLINE const TVec4f* GetTangents() const
  {
    this->VertexAssert(this->HasTangents());
    return this->tangents_.data();
  }
  GG_INLINE bool HasTangents() const
  {
    return !this->tangents_.empty();
  }

  void SetColor(T_UINT32 vertex_index, const TColor& tangent);
  void SetColors(const TColor* colors);
  GG_INLINE const TColor& GetColor(T_UINT32 vertex_index) const
  {
    this->VertexAssert(this->HasColors());
    return this->colors_[vertex_index];
  }
  GG_INLINE const TColor* GetColors() const
  {
    this->VertexAssert(this->HasColors());
    return this->colors_.data();
  }
  GG_INLINE bool HasColors() const
  {
    return !this->colors_.empty();
  }

  GG_INLINE const T_UINT32 GetVertexCount()
  {
    return this->vertex_count_;
  }

  //Index Buffer
  void SetIndex(T_UINT8 submesh_index, T_UINT32 index_index, T_UINT32 index);
  void SetIndices(T_UINT8 submesh_index, const T_UINT32* indices);
  GG_INLINE T_UINT32 GetIndex(T_UINT8 submesh_index, T_UINT32 index_index) const
  {
    GG_ASSERT(submesh_index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
    return this->submesh_indices_[submesh_index][index_index];
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
    return this->submesh_indices_[submesh_index].data();
  }
  GG_INLINE T_UINT32 GetIndexCount(T_UINT8 submesh_index = 0) const
  {
    GG_ASSERT(submesh_index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
    return this->submesh_index_buffers_[submesh_index]->GetVertexCount();
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
    return this->submesh_index_buffers_[submesh_index];
  }
  GG_INLINE SharedRef<const rcIndexBuffer> GetIndexBuffer(T_UINT8 submesh_index = 0) const
  {
    GG_ASSERT(submesh_index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
    return this->submesh_index_buffers_[submesh_index];
  }
  GG_INLINE T_UINT8 GetSubmeshCount() const
  {
    return this->submesh_count_;
  }
  GG_INLINE const Bounds& GetBounds()
  {
    return this->bounds_;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  bool readable_;

  SharedRef<rcVertexDeclaration> vertex_declaration_;

  T_UINT32 vertex_format_;
  Vertex::PrimitiveType primitive_type_;
  T_UINT32 polygon_count_;
  std::vector<TVec3f> face_normals_;

  Bounds bounds_;

  // VertexBuffer Params
  T_UINT32 vertex_count_;
  std::vector<TVec3f> vertices_;
  std::vector<TVec3f> normals_;
  std::vector<TVec2f> uvs_;
  std::vector<TVec2f> uv2s_;
  std::vector<TVec2f> uv3s_;
  std::vector<TVec2f> uv4s_;
  std::vector<TVec4f> tangents_;
  std::vector<TColor> colors_;
  //bindPoses
  //boneWeights
  //bounds
  bool vertices_dirty_;
  SharedRef<rcVertexBuffer> vertex_buffer_;

  // IndexBuffer Params
  T_UINT32 submesh_count_;
  std::vector<std::vector<T_UINT32>> submesh_indices_;
  std::vector<bool> submesh_indices_dirties_;
  std::vector<SharedRef<rcIndexBuffer>> submesh_index_buffers_;

};
