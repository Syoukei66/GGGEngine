#include "Mesh.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(rcMesh, const StaticMeshData& data)
{
  using namespace Vertex;

  this->readable_ = false;
  this->vertex_declaration_ = rcVertexDeclaration::Create(data.vertex_format_);
  this->primitive_type_ = Vertex::PrimitiveType::TRIANGLES;
  this->bounds_ = data.bounds_;

  GG_ASSERT(data.vertex_count_ > 0, "頂点がメッシュデータに含まれていませんでした");

  // Vertex Bufferの作成
  const T_UINT32 vertex_buffer_size = data.vertex_count_ * this->vertex_declaration_->GetVertexSize();
  this->vertex_buffer_ = rcVertexBuffer::Create(vertex_buffer_size);
  unsigned char* p;
  this->vertex_buffer_->Lock((void**)&p);
  for (T_UINT32 i = 0; i < vertex_buffer_size; ++i)
  {
    p[i] = data.vertex_data_[i];
  }
  this->vertex_buffer_->Unlock();

  // Index Bufferの作成
  this->submesh_count_ = (T_UINT32)data.index_datas_.size();
  this->submesh_index_buffers_.resize(this->submesh_count_);
  
  for (T_UINT32 i = 0; i < this->submesh_count_; ++i)
  {
    // インデックスバッファフォーマット
    const IndexFormat index_format = static_cast<IndexFormat>(data.index_formats_[i]);
    const T_UINT8 index_size = INDEX_FORMAT_SIZES[data.index_formats_[i]];

    const T_UINT32 index_count = data.index_counts_[i];
    this->submesh_index_buffers_[i] = rcIndexBuffer::Create(index_count, data.polygon_counts_[i], index_format);

    const T_UINT32 index_buffer_size = index_count * index_size;
    unsigned char* p;
    this->submesh_index_buffers_[i]->Lock((void**)&p);
    for (T_UINT32 ii = 0; ii < index_buffer_size; ++ii)
    {
      p[ii] = data.index_datas_[i][ii];
    }
    this->submesh_index_buffers_[i]->Unlock();

    this->polygon_count_ += data.polygon_counts_[i];
  }

  return true;
}

GG_DESTRUCT_FUNC_IMPL(rcMesh)
{
  this->Clear();
  return true;
}

// =================================================================
// Methods
// =================================================================
void rcMesh::Clear()
{
  this->ClearVertices(true);
  this->ClearIndices(true);
}

void rcMesh::ClearVertices(bool clear_buffer)
{
  this->vertices_.clear();
  this->normals_.clear();
  this->uvs_.clear();
  this->uv2s_.clear();
  this->uv3s_.clear();
  this->uv4s_.clear();
  this->tangents_.clear();
  this->colors_.clear();

  this->vertices_dirty_ = false;

  if (clear_buffer)
  {
    this->vertex_count_ = 0;
    this->vertex_buffer_ = nullptr;
    this->vertex_declaration_ = nullptr;
  }
}

void rcMesh::ClearIndices(bool clear_buffer)
{
  this->face_normals_.clear();

  this->submesh_indices_.clear();

  if (clear_buffer)
  {
    this->submesh_count_ = 0;
    this->submesh_index_buffers_.clear();
  }
}

void rcMesh::ConvertToData(StaticMeshData* dest)
{
  using namespace Vertex;
  GG_ASSERT(this->readable_, "メッシュのデータを読み込めません");

  // Vertices
  dest->vertex_format_ = this->vertex_format_;
  dest->vertex_count_ = this->vertex_count_;
  const T_UINT32 vertex_size = Vertex::CalcVertexSize(dest->vertex_format_);
  dest->vertex_data_.resize(dest->vertex_count_ * vertex_size);
  unsigned char* p = &dest->vertex_data_[0];
  for (T_UINT32 i = 0; i < dest->vertex_count_; ++i)
  {
    if (this->vertex_format_ & V_ATTR_POSITION) Vertex::SetVertexPosition(this->vertices_[i], &p);
    if (this->vertex_format_ & V_ATTR_NORMAL)   Vertex::SetVertexNormal(this->normals_[i], &p);
    if (this->vertex_format_ & V_ATTR_UV)       Vertex::SetVertexUv(this->uvs_[i], &p);
    if (this->vertex_format_ & V_ATTR_UV2)      Vertex::SetVertexUv2(this->uv2s_[i], &p);
    if (this->vertex_format_ & V_ATTR_UV3)      Vertex::SetVertexUv3(this->uv3s_[i], &p);
    if (this->vertex_format_ & V_ATTR_UV4)      Vertex::SetVertexUv4(this->uv4s_[i], &p);
    if (this->vertex_format_ & V_ATTR_TANGENT)  Vertex::SetVertexTangent(this->tangents_[i], &p);
    if (this->vertex_format_ & V_ATTR_COLOR)    Vertex::SetVertexColor(this->colors_[i], &p);
    //SetVertexBoneWeights(this->bone_weights_[i], dest->vertex_format_, &p);
  }

  // Indices
  dest->index_datas_.resize(this->submesh_count_);
  dest->index_formats_.resize(this->submesh_count_);
  dest->index_counts_.resize(this->submesh_count_);
  dest->polygon_counts_.resize(this->submesh_count_);
  for (T_UINT32 i = 0; i < this->submesh_count_; ++i)
  {
    const SharedRef<rcIndexBuffer>& index_buffer = this->submesh_index_buffers_[i];
    const Vertex::IndexFormat index_format = index_buffer->GetIndexFormat();
    const T_UINT32 index_size = Vertex::INDEX_FORMAT_SIZES[static_cast<T_UINT8>(index_format)];
    const T_UINT32 index_count = index_buffer->GetVertexCount();
    dest->index_formats_[i] = static_cast<T_UINT8>(index_format);
    dest->index_counts_[i] = index_count;
    dest->polygon_counts_[i] = index_buffer->GetPolygonCount();
    dest->index_datas_[i].resize(index_count * index_size);
    unsigned char* p = &dest->index_datas_[i][0];
    for (T_UINT32 ii = 0; ii < index_count; ++ii)
    {
      Vertex::SetIndexIndex(this->submesh_indices_[i][ii], index_format, &p);
    }
  }

  dest->bounds_ = this->bounds_;
}

void rcMesh::ConvertToData(DynamicMeshData* dest)
{
}

UniqueRef<rcMesh> rcMesh::Clone(bool clear_readable_data)
{
  UniqueRef<rcMesh> clone = rcMesh::Create();

  // clone Vertices
  clone->CreateVertices(this->vertex_count_, this->polygon_count_, this->vertex_format_, this->primitive_type_);
  if (this->HasVertices())  clone->SetVertices(this->vertices_.data());
  if (this->HasNormals())   clone->SetNormals(this->normals_.data());
  if (this->HasUvs())       clone->SetUvs(this->uvs_.data());
  if (this->HasUv2s())      clone->SetUv2s(this->uv2s_.data());
  if (this->HasUv3s())      clone->SetUv3s(this->uv3s_.data());
  if (this->HasUv4s())      clone->SetUv4s(this->uv4s_.data());
  if (this->HasTangents())  clone->SetTangents(this->tangents_.data());
  if (this->HasColors())    clone->SetColors(this->colors_.data());

  // clone indices
  for (const SharedRef<rcIndexBuffer>& index_buffer : this->submesh_index_buffers_ )
  {
    const T_UINT32 submesh_index_index = clone->AddIndices(index_buffer->GetVertexCount(), index_buffer->GetPolygonCount(), index_buffer->GetIndexFormat());
    const std::vector<T_UINT32>& submesh_indices = this->submesh_indices_[submesh_index_index];
    const T_UINT32 submesh_index_count = (T_UINT32)submesh_indices.size();
    clone->SetIndices(submesh_index_index, this->GetIndices(submesh_index_index));
  }

  clone->CommitChanges(clear_readable_data);
  return clone;
}

void rcMesh::CreateVertices(T_UINT32 vertex_count, T_UINT32 polygon_count, T_UINT32 format, Vertex::PrimitiveType primitive_type)
{
  this->readable_ = true;

  this->ClearVertices(true);

  this->vertex_declaration_ = rcVertexDeclaration::Create(format);

  this->vertex_format_ = format;
  this->vertex_count_ = vertex_count;
  this->polygon_count_ = polygon_count;
  this->primitive_type_ = primitive_type;

  using namespace Vertex;

  if (format & V_ATTR_POSITION) this->vertices_.resize(vertex_count);
  if (format & V_ATTR_NORMAL)   this->normals_.resize(vertex_count);
  if (format & V_ATTR_UV)       this->uvs_.resize(vertex_count);
  if (format & V_ATTR_UV2)      this->uv2s_.resize(vertex_count);
  if (format & V_ATTR_UV3)      this->uv3s_.resize(vertex_count);
  if (format & V_ATTR_UV4)      this->uv4s_.resize(vertex_count);
  if (format & V_ATTR_TANGENT)  this->tangents_.resize(vertex_count);
  if (format & V_ATTR_COLOR)    this->colors_.resize(vertex_count);
  this->vertex_buffer_ = rcVertexBuffer::Create(vertex_count * this->vertex_declaration_->GetVertexSize());
  this->vertices_dirty_ = true;
}

T_UINT32 rcMesh::AddIndices(T_UINT32 index_count, T_UINT32 polygon_count)
{
  this->submesh_indices_.emplace_back(std::vector<T_UINT32>());
  this->submesh_indices_[this->submesh_count_].resize(index_count);
  this->submesh_indices_dirties_.emplace_back(true);
  
  // 頂点数からインデックスフォーマットを判別する
  Vertex::IndexFormat format = Vertex::IndexFormat::INDEX_FMT_16;
  if (this->vertex_count_ > Limit::T_FIXED_UINT16_MAX)
  {
    format = Vertex::IndexFormat::INDEX_FMT_32;
  }

  this->submesh_index_buffers_.push_back(rcIndexBuffer::Create(index_count, polygon_count, format));
  ++this->submesh_count_;
  return this->submesh_count_ - 1;
}

void rcMesh::CommitChanges(bool clear_readable_data)
{
  using namespace Vertex;
  
  if (this->vertices_dirty_)
  {
    void* dest;
    this->vertex_buffer_->Lock(&dest);
    unsigned char* p = (unsigned char*)dest;
    for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
    {
      if (this->vertex_format_ & V_ATTR_POSITION) SetVertexPosition(this->vertices_[i], &p);
      if (this->vertex_format_ & V_ATTR_NORMAL)   SetVertexNormal(this->normals_[i], &p);
      if (this->vertex_format_ & V_ATTR_UV)       SetVertexUv(this->uvs_[i], &p);
      if (this->vertex_format_ & V_ATTR_UV2)      SetVertexUv2(this->uv2s_[i], &p);
      if (this->vertex_format_ & V_ATTR_UV3)      SetVertexUv3(this->uv3s_[i], &p);
      if (this->vertex_format_ & V_ATTR_UV4)      SetVertexUv4(this->uv4s_[i], &p);
      if (this->vertex_format_ & V_ATTR_TANGENT)  SetVertexTangent(this->tangents_[i], &p);
      if (this->vertex_format_ & V_ATTR_COLOR)    SetVertexColor(this->colors_[i], &p);
    }
    this->vertex_buffer_->Unlock();
    this->vertices_dirty_ = false;
  }
  for (T_UINT8 i = 0; i < this->submesh_count_; ++i)
  {
    if (!this->submesh_indices_dirties_[i])
    {
      continue;
    }
    const T_UINT32 submesh_index_count = this->submesh_index_buffers_[i]->GetVertexCount();
    const IndexFormat index_format = this->submesh_index_buffers_[i]->GetIndexFormat();
    unsigned char* p;
    this->submesh_index_buffers_[i]->Lock((void**)&p);
    for (T_UINT32 j = 0; j < submesh_index_count; ++j)
    {
      SetIndexIndex(this->submesh_indices_[i][j], index_format, &p);
    }
    this->submesh_index_buffers_[i]->Unlock();
    this->submesh_indices_dirties_[i] = false;
  }
  if (clear_readable_data)
  {
    this->ClearVertices(false);
    this->ClearIndices(false);
    this->readable_ = false;
  }
}

void rcMesh::DecomposeBufferDatas(bool clear_buffer_data)
{
}

void rcMesh::RecalculateNormals(bool save_face_normals)
{
  GG_ASSERT(this->primitive_type_ == Vertex::PrimitiveType::TRIANGLES, "まだできてません！");

  GG_ASSERT(this->vertex_format_ & Vertex::V_ATTR_NORMAL, "フォーマットに法線情報が含まれていません");

  this->face_normals_.resize(this->polygon_count_);
  for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
  {
    this->normals_[i] = TVec3f::zero;
  }
  for (T_UINT8 i = 0; i < this->submesh_count_; ++i)
  {
    const T_UINT32 submesh_index_count = this->submesh_index_buffers_[i]->GetVertexCount();
    for (T_UINT32 j = 0, s = 0; j < submesh_index_count; j += 3, ++s)
    {
      TVec3f v0 = this->vertices_[this->submesh_indices_[i][j]];
      TVec3f v1 = this->vertices_[this->submesh_indices_[i][j + 1]];
      TVec3f v2 = this->vertices_[this->submesh_indices_[i][j + 2]];
      TVec3f vv1 = v1 - v0;
      TVec3f vv2 = v2 - v1;
      this->face_normals_[s] = TVec3f::Cross(vv1, vv2).Normalized();
      this->normals_[this->submesh_indices_[i][j]] += this->face_normals_[s];
      this->normals_[this->submesh_indices_[i][j + 1]] += this->face_normals_[s];
      this->normals_[this->submesh_indices_[i][j + 2]] += this->face_normals_[s];
    }
  }
  for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
  {
    this->normals_[i] = this->normals_[i].Normalized();
  }
  if (!save_face_normals)
  {
    this->face_normals_.clear();
  }
}

void rcMesh::RecalculateTangents()
{
  GG_ASSERT(this->primitive_type_ == Vertex::PrimitiveType::TRIANGLES, "まだできてません！");

  GG_ASSERT(this->vertex_format_ & Vertex::V_ATTR_NORMAL, "フォーマットに法線情報が含まれていません");
  GG_ASSERT(this->vertex_format_ & Vertex::V_ATTR_TANGENT, "フォーマットにtangentベクトル情報が含まれていません");

  /*
  https://answers.unity.com/questions/7789/calculating-tangents-vector4.html
  */
  for (T_UINT8 i = 0; i < this->submesh_count_; ++i)
  {
    const T_UINT32 submesh_index_count = this->submesh_index_buffers_[i]->GetVertexCount();
    TVec3f* tan0 = new TVec3f[submesh_index_count];
    TVec3f* tan1 = new TVec3f[submesh_index_count];

    for (T_UINT32 j = 0; j < submesh_index_count; j += 3)
    {
      const T_UINT32 i0 = this->submesh_indices_[i][j + 0];
      const T_UINT32 i1 = this->submesh_indices_[i][j + 1];
      const T_UINT32 i2 = this->submesh_indices_[i][j + 2];
                                
      const TVec3f& v0 = this->vertices_[i0];
      const TVec3f& v1 = this->vertices_[i1];
      const TVec3f& v2 = this->vertices_[i2];

      const TVec2f& w0 = this->uvs_[i0];
      const TVec2f& w1 = this->uvs_[i1];
      const TVec2f& w2 = this->uvs_[i2];

      const T_FLOAT x0 = v1.x - v0.x;
      const T_FLOAT x1 = v2.x - v0.x;

      const T_FLOAT y0 = v1.y - v0.y;
      const T_FLOAT y1 = v2.y - v0.y;

      const T_FLOAT z0 = v1.z - v0.z;
      const T_FLOAT z1 = v2.z - v0.z;

      const T_FLOAT s0 = w1.x - w0.x;
      const T_FLOAT s1 = w2.x - w0.x;

      const T_FLOAT t0 = w1.y - w0.y;
      const T_FLOAT t1 = w2.y - w0.y;

      const T_FLOAT div = s0 * t1 - s1 * t0;
      const T_FLOAT r = div == 0.0f ? 0.0f : 1.0f / div;

      const TVec3f sdir = TVec3f(
        (t1 * x0 - t0 * x1) * r,
        (t1 * y0 - t0 * y1) * r,
        (t1 * z0 - t0 * z1) * r
      );
      const TVec3f tdir = TVec3f(
        (s0 * x1 - s1 * x0) * r,
        (s0 * y1 - s1 * y0) * r,
        (s0 * z1 - s1 * z0) * r
      );

      tan0[i0] += sdir;
      tan0[i1] += sdir;
      tan0[i2] += sdir;

      tan1[i0] += tdir;
      tan1[i1] += tdir;
      tan1[i2] += tdir;
    }

    for (T_UINT32 j = 0; j < submesh_index_count; j++)
    {
      const T_UINT32 index = this->submesh_indices_[i][j];
      const TVec3f n = this->normals_[index];
      const TVec3f t = tan0[index];
      const TVec3f tmp = (t - n * TVec3f::Dot(n, t)).Normalized();
      this->tangents_[index] = TVec4f(tmp.x, tmp.y, tmp.z, 0.0f);
      this->tangents_[index].w = (TVec3f::Dot(TVec3f::Cross(n, t), tan1[index]) < 0.0f) ? -1.0f : 1.0f;
    }
    delete[] tan0;
    delete[] tan1;
  }
}

void rcMesh::SetStreamSource() const
{
  if (!this->vertex_buffer_)
  {
    return;
  }
  this->vertex_buffer_->SetStreamSource(this->vertex_declaration_);
}

void rcMesh::DrawSubset(T_UINT8 index) const
{
  if (!this->vertex_buffer_)
  {
    return;
  }
  GG_ASSERT(index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
  this->submesh_index_buffers_[index]->SetIndices();
  Application::GetPlatform()->GetGraphicsAPI()->DrawIndexedPrimitive(this->primitive_type_, this->submesh_index_buffers_[index]);
}

// =================================================================
// Setter / Getter
// =================================================================
size_t rcMesh::GetMemorySize() const
{
  size_t ret = sizeof(rcMesh);
  using namespace Vertex;
  ret += this->vertex_count_ * CalcVertexSize(this->vertex_format_);
  if (this->face_normals_.size() > 0)
  {
    ret += sizeof(TVec3f) * this->polygon_count_;
  }
  for (T_UINT8 i = 0; i < this->submesh_count_; ++i)
  {
    if (!this->submesh_index_buffers_[i])
    {
      continue;
    }
    ret += sizeof(T_UINT32) * this->submesh_index_buffers_[i]->GetVertexCount();
  }
  ret += sizeof(T_UINT32) * this->submesh_count_;
  ret += sizeof(bool) * this->submesh_count_;
  return ret;
}

size_t rcMesh::GetVideoMemorySize() const
{
  size_t ret = 0;
  if (this->vertex_buffer_)
  {
    ret += this->vertex_buffer_->GetMemorySize();
  }
  for (T_UINT8 i = 0; i < this->submesh_count_; ++i)
  {
    if (!this->submesh_index_buffers_[i])
    {
      continue;
    }
    ret += sizeof(T_UINT32) * this->submesh_index_buffers_[i]->GetVertexCount();
  }
  return ret;
}

void rcMesh::SetVertex(T_UINT32 vertex_index, const TVec3f& vertex)
{
  GG_ASSERT(this->HasVertices(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->vertices_[vertex_index] == vertex)
  {
    return;
  }
  this->vertices_[vertex_index] = vertex;
  this->vertices_dirty_ = true;
}

void rcMesh::SetVertices(const TVec3f* vertices)
{
  GG_ASSERT(this->HasVertices(), "頂点フォーマットで定義されていない属性が呼び出されました");
  for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
  {
    if (this->vertices_[i] == vertices[i])
    {
      continue;
    }
    this->vertices_[i] = vertices[i];
    this->vertices_dirty_ = true;
  }
}

void rcMesh::SetNormal(T_UINT32 vertex_index, const TVec3f& normal)
{
  GG_ASSERT(this->HasNormals(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->normals_[vertex_index] == normal)
  {
    return;
  }
  this->normals_[vertex_index] = normal;
  this->vertices_dirty_ = true;
}

void rcMesh::SetNormals(const TVec3f* normals)
{
  GG_ASSERT(this->HasNormals(), "頂点フォーマットで定義されていない属性が呼び出されました");
  for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
  {
    if (this->normals_[i] == normals[i])
    {
      continue;
    }
    this->normals_[i] = normals[i];
    this->vertices_dirty_ = true;
  }
}

void rcMesh::SetUv(T_UINT32 vertex_index, const TVec2f& uv)
{
  GG_ASSERT(this->HasUvs(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->uvs_[vertex_index] == uv)
  {
    return;
  }
  this->uvs_[vertex_index] = uv;
  this->vertices_dirty_ = true;
}

void rcMesh::SetUvs(const TVec2f* uvs)
{
  GG_ASSERT(this->HasUvs(), "頂点フォーマットで定義されていない属性が呼び出されました");
  for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
  {
    if (this->uvs_[i] == uvs[i])
    {
      continue;
    }
    this->uvs_[i] = uvs[i];
    this->vertices_dirty_ = true;
  }
}

void rcMesh::SetUv2(T_UINT32 vertex_index, const TVec2f& uv2)
{
  GG_ASSERT(this->HasUv2s(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->uv2s_[vertex_index] == uv2)
  {
    return;
  }
  this->uv2s_[vertex_index] = uv2;
  this->vertices_dirty_ = true;
}

void rcMesh::SetUv2s(const TVec2f* uv2s)
{
  GG_ASSERT(this->HasUv2s(), "頂点フォーマットで定義されていない属性が呼び出されました");
  for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
  {
    if (this->uv2s_[i] == uv2s[i])
    {
      continue;
    }
    this->uv2s_[i] = uv2s[i];
    this->vertices_dirty_ = true;
  }
}

void rcMesh::SetUv3(T_UINT32 vertex_index, const TVec2f& uv3)
{
  GG_ASSERT(this->HasUv3s(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->uv3s_[vertex_index] == uv3)
  {
    return;
  }
  this->uv3s_[vertex_index] = uv3;
  this->vertices_dirty_ = true;
}

void rcMesh::SetUv3s(const TVec2f* uv3s)
{
  GG_ASSERT(this->HasUv3s(), "頂点フォーマットで定義されていない属性が呼び出されました");
  for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
  {
    if (this->uv3s_[i] == uv3s[i])
    {
      continue;
    }
    this->uv3s_[i] = uv3s[i];
    this->vertices_dirty_ = true;
  }
}

void rcMesh::SetUv4(T_UINT32 vertex_index, const TVec2f& uv4)
{
  GG_ASSERT(this->HasUv4s(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->uv4s_[vertex_index] == uv4)
  {
    return;
  }
  this->uv4s_[vertex_index] = uv4;
  this->vertices_dirty_ = true;
}

void rcMesh::SetUv4s(const TVec2f* uv4s)
{
  GG_ASSERT(this->HasUv4s(), "頂点フォーマットで定義されていない属性が呼び出されました");
  for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
  {
    if (this->uv4s_[i] == uv4s[i])
    {
      continue;
    }
    this->uv4s_[i] = uv4s[i];
    this->vertices_dirty_ = true;
  }
}

void rcMesh::SetTangent(T_UINT32 vertex_index, const TVec4f& tangent)
{
  GG_ASSERT(this->HasTangents(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->tangents_[vertex_index] == tangent)
  {
    return;
  }
  this->tangents_[vertex_index] = tangent;
  this->vertices_dirty_ = true;
}

void rcMesh::SetTangents(const TVec4f* tangents)
{
  GG_ASSERT(this->HasTangents(), "頂点フォーマットで定義されていない属性が呼び出されました");
  for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
  {
    if (this->tangents_[i] == tangents[i])
    {
      continue;
    }
    this->tangents_[i] = tangents[i];
    this->vertices_dirty_ = true;
  }
}

void rcMesh::SetColor(T_UINT32 vertex_index, const TColor& color)
{
  GG_ASSERT(this->HasColors(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->colors_[vertex_index] == color)
  {
    return;
  }
  this->colors_[vertex_index] = color;
  this->vertices_dirty_ = true;
}

void rcMesh::SetColors(const TColor* colors)
{
  GG_ASSERT(this->HasColors(), "頂点フォーマットで定義されていない属性が呼び出されました");
  for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
  {
    if (this->colors_[i] == colors[i])
    {
      continue;
    }
    this->colors_[i] = colors[i];
    this->vertices_dirty_ = true;
  }
}

void rcMesh::SetIndex(T_UINT8 submesh_index, T_UINT32 index_index, T_UINT32 index)
{
  GG_ASSERT(submesh_index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
  if (this->submesh_indices_[submesh_index][index_index] == index)
  {
    return;
  }
  this->submesh_indices_[submesh_index][index_index] = index;
  this->submesh_indices_dirties_[submesh_index] = true;
}

void rcMesh::SetIndices(T_UINT8 submesh_index, const T_UINT32* indices)
{
  GG_ASSERT(submesh_index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
  const T_UINT32 submesh_index_count = this->submesh_index_buffers_[submesh_index]->GetVertexCount();
  for (T_UINT32 i = 0; i < submesh_index_count; ++i)
  {
    if (this->submesh_indices_[submesh_index][i] == indices[i])
    {
      continue;
    }
    this->submesh_indices_[submesh_index][i] = indices[i];
    this->submesh_indices_dirties_[submesh_index] = true;
  }
}
