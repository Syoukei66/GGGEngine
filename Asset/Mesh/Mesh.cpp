#include "Mesh.h"

#include "DynamicMesh.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(rcMesh, const StaticMeshData& data)
{
  using namespace Vertex;

  this->vertex_declaration_ = rcVertexDeclaration::Create(data.vertex_format_);
  this->primitive_type_ = Vertex::PrimitiveType::TRIANGLES;
  this->bounds_ = data.bounds_;

  GG_ASSERT(data.vertex_count_ > 0, "頂点がメッシュデータに含まれていませんでした");

  // Vertex Bufferの作成
  this->vertex_count_ = data.vertex_count_;
  const T_UINT32 vertex_buffer_size = this->vertex_count_ * this->vertex_declaration_->GetVertexSize();
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
  }

  return true;
}

// =================================================================
// Methods
// =================================================================
UniqueRef<rcDynamicMesh> rcMesh::CloneDynamic() const
{
  using namespace Vertex;

  const T_UINT32 vertex_format = this->vertex_declaration_->GetFormat();

  UniqueRef<rcDynamicMesh> ret = rcDynamicMesh::Create();

  ret->CreateVertices(this->vertex_count_, vertex_format);

  // 頂点バッファからデータをコピーする
  unsigned char* p;
  this->vertex_buffer_->Lock((void**)&p);
  for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
  {
    if (vertex_format & V_ATTR_POSITION) GetVertexPosition(&ret->vertices_[i], &p);
    if (vertex_format & V_ATTR_NORMAL)   GetVertexNormal(&ret->normals_[i], &p);
    if (vertex_format & V_ATTR_UV)       GetVertexUv(&ret->uvs_[i], &p);
    if (vertex_format & V_ATTR_UV2)      GetVertexUv2(&ret->uv2s_[i], &p);
    if (vertex_format & V_ATTR_UV3)      GetVertexUv3(&ret->uv3s_[i], &p);
    if (vertex_format & V_ATTR_UV4)      GetVertexUv4(&ret->uv4s_[i], &p);
    if (vertex_format & V_ATTR_TANGENT)  GetVertexTangent(&ret->tangents_[i], &p);
    if (vertex_format & V_ATTR_COLOR)    GetVertexColor(&ret->colors_[i], &p);
  }
  this->vertex_buffer_->Unlock();

  ret->vertices_dirty_ = false;

  // インデックスバッファからデータをコピーする
  for (T_UINT8 i = 0; i < this->submesh_count_; ++i)
  {
    const T_UINT32 submesh_index_count = this->submesh_index_buffers_[i]->GetVertexCount();
    const IndexFormat index_format = this->submesh_index_buffers_[i]->GetIndexFormat();
    ret->AddIndices(submesh_index_count);

    unsigned char* p;
    this->submesh_index_buffers_[i]->Lock((void**)&p);
    for (T_UINT32 j = 0; j < submesh_index_count; ++j)
    {
      GetIndexIndex(&ret->submesh_indices_[i][j], index_format, &p);
    }
    this->submesh_index_buffers_[i]->Unlock();

    ret->submesh_indices_dirties_[i] = false;
  }

  return ret;
}

UniqueRef<rcDynamicMesh> rcMesh::MoveDynamic()
{
  using namespace Vertex;

  UniqueRef<rcDynamicMesh> ret = rcDynamicMesh::Create();

  ret->vertex_declaration_ = std::move(this->vertex_declaration_);
  ret->vertex_buffer_ = std::move(this->vertex_buffer_);
  ret->vertex_format_ = ret->vertex_declaration_->GetFormat();
  ret->primitive_type_ = this->primitive_type_;

  // 頂点データの作成
  if (ret->vertex_format_ & V_ATTR_POSITION) ret->vertices_.resize(this->vertex_count_);
  if (ret->vertex_format_ & V_ATTR_NORMAL)   ret->normals_.resize(this->vertex_count_);
  if (ret->vertex_format_ & V_ATTR_UV)       ret->uvs_.resize(this->vertex_count_);
  if (ret->vertex_format_ & V_ATTR_UV2)      ret->uv2s_.resize(this->vertex_count_);
  if (ret->vertex_format_ & V_ATTR_UV3)      ret->uv3s_.resize(this->vertex_count_);
  if (ret->vertex_format_ & V_ATTR_UV4)      ret->uv4s_.resize(this->vertex_count_);
  if (ret->vertex_format_ & V_ATTR_TANGENT)  ret->tangents_.resize(this->vertex_count_);
  if (ret->vertex_format_ & V_ATTR_COLOR)    ret->colors_.resize(this->vertex_count_);

  // 頂点バッファからデータをコピーする
  unsigned char* p;
  ret->vertex_buffer_->Lock((void**)&p);
  for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
  {
    if (ret->vertex_format_ & V_ATTR_POSITION) GetVertexPosition(&ret->vertices_[i], &p);
    if (ret->vertex_format_ & V_ATTR_NORMAL)   GetVertexNormal(&ret->normals_[i], &p);
    if (ret->vertex_format_ & V_ATTR_UV)       GetVertexUv(&ret->uvs_[i], &p);
    if (ret->vertex_format_ & V_ATTR_UV2)      GetVertexUv2(&ret->uv2s_[i], &p);
    if (ret->vertex_format_ & V_ATTR_UV3)      GetVertexUv3(&ret->uv3s_[i], &p);
    if (ret->vertex_format_ & V_ATTR_UV4)      GetVertexUv4(&ret->uv4s_[i], &p);
    if (ret->vertex_format_ & V_ATTR_TANGENT)  GetVertexTangent(&ret->tangents_[i], &p);
    if (ret->vertex_format_ & V_ATTR_COLOR)    GetVertexColor(&ret->colors_[i], &p);
  }
  ret->vertex_buffer_->Unlock();
  ret->vertices_dirty_ = false;

  ret->submesh_count_ = this->submesh_count_;
  ret->submesh_index_buffers_.resize(ret->submesh_count_);
  ret->submesh_indices_.resize(ret->submesh_count_);
  ret->submesh_indices_dirties_.resize(ret->submesh_count_);
  // インデックスバッファからデータをコピーする
  for (T_UINT8 i = 0; i < ret->submesh_count_; ++i)
  {
    const T_UINT32 submesh_index_count = this->submesh_index_buffers_[i]->GetVertexCount();
    const IndexFormat index_format = this->submesh_index_buffers_[i]->GetIndexFormat();
    ret->submesh_indices_[i].resize(submesh_index_count);

    ret->submesh_index_buffers_[i] = std::move(this->submesh_index_buffers_[i]);

    unsigned char* p;
    ret->submesh_index_buffers_[i]->Lock((void**)&p);
    for (T_UINT32 j = 0; j < submesh_index_count; ++j)
    {
      GetIndexIndex(&ret->submesh_indices_[i][j], index_format, &p);
    }
    ret->submesh_index_buffers_[i]->Unlock();
    ret->polygon_count_ += PRIMITIVE_SURF_NUM(ret->primitive_type_, submesh_index_count);
    ret->submesh_indices_dirties_[i] = false;
  }

  ret->bounds_ = this->bounds_;

  return ret;
}

void rcMesh::SetStreamSource() const
{
  if (!this->vertex_buffer_)
  {
    return;
  }
  this->vertex_buffer_->SetStreamSource(this->vertex_declaration_);
}

void rcMesh::SetInputFormat(const SharedRef<rcShader>& shader) const
{
  if (!this->vertex_buffer_)
  {
    return;
  }
  this->vertex_declaration_->SetInputLayout(shader);
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
  return sizeof(rcMesh);
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
