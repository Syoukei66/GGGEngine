#include "SubMesh.h"


/*
  memo
  サブメッシュはインデックスバッファの集まり
*/

SubMesh::SubMesh(MeshData* data)
  : orginal_()
  , vertex_buffer_()
  , index_buffer_()
  , type_(Vertex::VERTEX_TYPE_DATANUM)
  , vertices_count_(-1)
  , vertices_()
  , normals_()
  , uvs_()
  , uv2s_()
  , tangents_()
  , colors_()
  , vertices_dirty_(true)
  , indices_count_(-1)
  , indices_()
  , indices_dirty_(true)
{
  const T_UINT16 vertexes_count = data->GetVertexesCount();
  const T_UINT16 indices_count = data->GetIndicesCount();
  const INativeProcess_Graphics::PrimitiveType primitive_type = data->GetPrimitiveType();
  const Vertex::VertexType vertex_type = data->GetVertexType();
  const T_UINT16 polygon_count = INativeProcess_Graphics::PRIMITIVE_SURF_NUM(primitive_type, indices_count);

  this->vertex_buffer_ = INativeVertexBuffer::Create(vertexes_count, polygon_count, vertex_type);
  void* dest_vertexes;
  this->vertex_buffer_->Lock(&dest_vertexes);
  data->SetupVertex(dest_vertexes);
  this->vertex_buffer_->Unlock();

  this->index_buffer_ = INativeIndexBuffer::Create(indices_count);
  T_UINT16* dest_indices;
  this->index_buffer_->Lock((void**)&dest_indices);
  const T_UINT16* indices = data->GetIndices();
  for (T_UINT16 i = 0; i < indices_count; ++i)
  {
    dest_indices[i] = indices[i];
  }
  this->index_buffer_->Unlock();
}

SubMesh::SubMesh(const SubMesh& other)
  : orginal_(&other)
  , vertex_buffer_()
  , index_buffer_()
  , type_(Vertex::VERTEX_TYPE_DATANUM)
  , vertices_count_(other.vertices_count_)
  , vertices_()
  , normals_()
  , uvs_()
  , uv2s_()
  , tangents_()
  , colors_()
  , vertices_dirty_(true)
  , indices_count_(other.vertices_count_)
  , indices_()
  , indices_dirty_(true)
{
  //Vertices Copy
  if (other.HasVertices())
  {
    this->PrepareVertices();
    for (T_UINT16 i = 0; i < this->vertices_count_; ++i)
    {
      this->vertices_[i] = other.vertices_[i];
    }
  }
  if (other.HasNormals())
  {
    this->PrepareNormals();
    for (T_UINT16 i = 0; i < this->vertices_count_; ++i)
    {
      this->normals_[i] = other.normals_[i];
    }
  }
  if (other.HasUvs())
  {
    this->PrepareUvs();
    for (T_UINT16 i = 0; i < this->vertices_count_; ++i)
    {
      this->uvs_[i] = other.uvs_[i];
    }
  }
  if (other.HasUv2s())
  {
    this->PrepareUv2s();
    for (T_UINT16 i = 0; i < this->vertices_count_; ++i)
    {
      this->uv2s_[i] = other.uv2s_[i];
    }
  }
  if (other.HasTangents())
  {
    this->PrepareTangents();
    for (T_UINT16 i = 0; i < this->vertices_count_; ++i)
    {
      this->tangents_[i] = other.tangents_[i];
    }
  }
  if (other.HasColors())
  {
    this->PrepareColors();
    for (T_UINT16 i = 0; i < this->vertices_count_; ++i)
    {
      this->colors_[i] = other.colors_[i];
    }
  }
  //Indices Copy
  this->indices_ = new T_UINT16[this->indices_count_];
  for (T_UINT16 i = 0; i < this->indices_count_; ++i)
  {
    this->indices_[i] = other.indices_[i];
  }
}

SubMesh::~SubMesh()
{
  delete this->vertex_buffer_;
  delete this->index_buffer_;

  delete this->vertices_;
  delete this->normals_;
  delete this->uvs_;
  delete this->uv2s_;
  delete this->tangents_;
  delete this->colors_;
  delete this->indices_;
}

// =================================================================
// Method
// =================================================================

void SubMesh::Init(T_UINT16 vertices_count, T_UINT16 indices_count)
{
  delete this->vertices_;
  delete this->normals_;
  delete this->uvs_;
  delete this->uv2s_;
  delete this->tangents_;
  delete this->colors_;
  delete this->indices_;

  this->vertices_ = nullptr;
  this->normals_ = nullptr;
  this->uvs_ = nullptr;
  this->uv2s_ = nullptr;
  this->tangents_ = nullptr;
  this->colors_ = nullptr;
  this->indices_ = nullptr;

  this->vertices_count_ = vertices_count;
  this->indices_count_ = indices_count;
}

void SubMesh::PrepareVertices()
{
  if (this->vertices_)
  {
    return;
  }
  this->vertices_ = new TVec4f[this->vertices_count_];
}

void SubMesh::PrepareNormals()
{
  if (this->normals_)
  {
    return;
  }
  this->normals_ = new TVec3f[this->vertices_count_];
}

void SubMesh::PrepareUvs()
{
  if (this->uvs_)
  {
    return;
  }
  this->uvs_ = new TVec2f[this->vertices_count_];
}

void SubMesh::PrepareUv2s()
{
  if (this->uv2s_)
  {
    return;
  }
  this->uv2s_ = new TVec2f[this->vertices_count_];
}

void SubMesh::PrepareTangents()
{
  if (this->tangents_)
  {
    return;
  }
  this->tangents_ = new TVec3f[this->vertices_count_];
}

void SubMesh::PrepareColors()
{
  if (this->colors_)
  {
    return;
  }
  this->colors_ = new Color4F[this->vertices_count_];
}

void SubMesh::CommitChanges()
{
  if (this->vertices_dirty_)
  {
    this->CommitVertices();
  }
  if (this->indices_dirty_)
  {
    this->CommitIndices();
  }
}

void SubMesh::CommitVertices() const
{
  NATIVE_ASSERT(mesh.HasVertices(), "頂点に座標情報がありません。座標情報は必須です。");
  if (this->HasColors())
  {
    if (this->HasUvs())
    {
      if (this->HasNormals())
      {
        this->
      }
    }
  }


  SubMesh* casted_this = const_cast<SubMesh*>(this);
  casted_this->vertex_buffer_ = 
    INativeVertexBuffer::Create(vertexes_count, polygon_count, vertex_type);

  void* dest_vertexes;
  this->vertex_buffer_->Lock(&dest_vertexes);
  for (T_UINT16 i = 0; i < this->vertices_count_; ++i)
  {
  }
  data->SetupVertex(dest_vertexes);
  this->vertex_buffer_->Unlock();
}

void SubMesh::CommitIndices() const
{
}

