#include "Mesh.h"
#include "GraphicsConstants.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Mesh::Mesh()
  : orginal_()
  , format_()
  , primitive_type_()
  , polygon_count_()
  , face_normals_()
  , vertex_count_()
  , vertices_()
  , normals_()
  , uvs_()
  , uv2s_()
  , uv3s_()
  , uv4s_()
  , tangents_()
  , colors_()
  , vertices_dirty_()
  , vertex_buffer_()
  , submesh_count_()
  , index_counts_()
  , indices_()
  , indices_dirties_()
  , index_buffers_()
{
}

Mesh::~Mesh()
{
  this->Clear();
}

// =================================================================
// Method
// =================================================================
void Mesh::Clear()
{
  this->ClearVertices();
  this->ClearIndices();
}

void Mesh::ClearVertices()
{
  delete[] this->vertices_;
  delete[] this->normals_;
  delete[] this->uvs_;
  delete[] this->uv2s_;
  delete[] this->uv3s_;
  delete[] this->uv4s_;
  delete[] this->tangents_;
  delete[] this->colors_;

  delete this->vertex_buffer_;

  this->vertex_count_ = 0;
  this->vertices_ = nullptr;
  this->normals_ = nullptr;
  this->uvs_ = nullptr;
  this->uv2s_ = nullptr;
  this->uv3s_ = nullptr;
  this->uv4s_ = nullptr;
  this->tangents_ = nullptr;
  this->colors_ = nullptr;
  this->vertex_buffer_ = nullptr;

  this->vertices_dirty_ = false;
}

void Mesh::ClearIndices()
{
  delete[] this->face_normals_;
  for (T_UINT8 i = 0; i < this->submesh_count_; ++i)
  {
    delete[] this->indices_[i];
    delete this->index_buffers_[i];
  }
  delete[] this->indices_;
  delete[] this->index_counts_;
  delete[] this->index_buffers_;
  delete[] this->indices_dirties_;

  this->face_normals_ = nullptr;
  this->submesh_count_ = 0;
  this->indices_ = nullptr;
  this->index_counts_ = nullptr;
  this->index_buffers_ = nullptr;
  this->indices_dirties_ = nullptr;
}

Mesh* Mesh::Clone()
{
  Mesh* clone = new Mesh();

  clone->orginal_ = this;
  clone->CreateVertices(this->vertex_count_, this->format_, this->primitive_type_);
  clone->CreateIndices(this->submesh_count_, this->index_counts_);
  if (this->HasVertices())
  {
    clone->SetVertices(this->vertices_);
  }
  if (this->HasNormals())
  {
    clone->SetNormals(this->normals_);
  }
  if (this->HasUvs())
  {
    clone->SetUvs(this->uvs_);
  }
  if (this->HasUv2s())
  {
    clone->SetUv2s(this->uv2s_);
  }
  if (this->HasUv3s())
  {
    clone->SetUv3s(this->uv3s_);
  }
  if (this->HasUv4s())
  {
    clone->SetUv4s(this->uv4s_);
  }
  if (this->HasTangents())
  {
    clone->SetTangents(this->tangents_);
  }
  if (this->HasColors())
  {
    clone->SetColors(this->colors_);
  }
  clone->CommitChanges();
  return clone;
}

void Mesh::CreateVertices(T_UINT32 vertex_count, T_UINT32 polygon_count, T_UINT32 format, GraphicsConstants::PrimitiveType primitive_type)
{
  this->ClearVertices();

  this->vertex_count_ = vertex_count;
  this->polygon_count_ = polygon_count;
  this->format_ = format;
  this->primitive_type_ = primitive_type;

  using namespace GraphicsConstants;

  if (format & V_ATTR_POSITION)
  {
    this->vertices_ = new TVec3f[vertex_count]{};
  }
  if (format & V_ATTR_NORMAL)
  {
    this->normals_ = new TVec3f[vertex_count]{};
  }
  if (format & V_ATTR_UV)
  {
    this->uvs_ = new TVec2f[vertex_count]{};
  }
  if (format & V_ATTR_UV2)
  {
    this->uv2s_ = new TVec2f[vertex_count]{};
  }
  if (format & V_ATTR_UV3)
  {
    this->uv3s_ = new TVec2f[vertex_count]{};
  }
  if (format & V_ATTR_UV4)
  {
    this->uv4s_ = new TVec2f[vertex_count]{};
  }
  if (format & V_ATTR_TANGENT)
  {
    this->tangents_ = new TVec4f[vertex_count]{};
  }
  if (format & V_ATTR_COLOR)
  {
    this->colors_ = new Color4F[vertex_count]{};
  }
  this->vertex_buffer_ = INativeVertexBuffer::Create(
    vertex_count, 
    polygon_count,
    format
  );
  this->vertices_dirty_ = true;
}

void Mesh::CreateIndices(T_UINT8 submesh_count, T_UINT32* index_counts)
{
  this->ClearIndices();
  this->submesh_count_ = submesh_count;
  this->index_counts_ = new T_UINT32[submesh_count]{};
  this->indices_ = new T_UINT32*[submesh_count]{};
  this->indices_dirties_ = new bool[submesh_count]{};
  this->index_buffers_ = new INativeIndexBuffer*[submesh_count]{};
  for (T_UINT8 i = 0; i < submesh_count; ++i)
  {
    this->index_counts_[i] = index_counts[i];
    this->indices_[i] = new T_UINT32[index_counts[i]]{};
    this->index_buffers_[i] = INativeIndexBuffer::Create(index_counts[i]);
    this->indices_dirties_[i] = true;
  }
}

void Mesh::CommitChanges()
{
  using namespace GraphicsConstants;

  if (this->vertices_dirty_)
  {
    void* dest;
    this->vertex_buffer_->Lock(&dest);
    char* p = (char*)dest;
    for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
    {
      if (this->format_ & V_ATTR_POSITION)
      {
        T_FLOAT* vertex = (T_FLOAT*)p;
        vertex[0] = this->vertices_[i].x;
        vertex[1] = this->vertices_[i].y;
        vertex[2] = this->vertices_[i].z;
        p += VERTEX_ATTRIBUTE_SIZE(V_ATTR_POSITION);
      }
      if (this->format_ & V_ATTR_NORMAL)
      {
        T_FLOAT* normal = (T_FLOAT*)p;
        normal[0] = this->normals_[i].x;
        normal[1] = this->normals_[i].y;
        normal[2] = this->normals_[i].z;
        p += VERTEX_ATTRIBUTE_SIZE(V_ATTR_NORMAL);
      }
      if (this->format_ & V_ATTR_UV)
      {
        T_FLOAT* uv = (T_FLOAT*)p;
        uv[0] = this->uvs_[i].x;
        uv[1] = this->uvs_[i].y;
        p += VERTEX_ATTRIBUTE_SIZE(V_ATTR_UV);
      }
      if (this->format_ & V_ATTR_UV2)
      {
        T_FLOAT* uv2 = (T_FLOAT*)p;
        uv2[0] = this->uv2s_[i].x;
        uv2[1] = this->uv2s_[i].y;
        p += VERTEX_ATTRIBUTE_SIZE(V_ATTR_UV2);
      }
      if (this->format_ & V_ATTR_UV3)
      {
        T_FLOAT* uv3 = (T_FLOAT*)p;
        uv3[0] = this->uv3s_[i].x;
        uv3[1] = this->uv3s_[i].y;
        p += VERTEX_ATTRIBUTE_SIZE(V_ATTR_UV3);
      }
      if (this->format_ & V_ATTR_UV4)
      {
        T_FLOAT* uv4 = (T_FLOAT*)p;
        uv4[0] = this->uv4s_[i].x;
        uv4[1] = this->uv4s_[i].y;
        p += VERTEX_ATTRIBUTE_SIZE(V_ATTR_UV4);
      }
      if (this->format_ & V_ATTR_TANGENT)
      {
        T_FLOAT* tangent = (T_FLOAT*)p;
        tangent[0] = this->tangents_[i].x;
        tangent[1] = this->tangents_[i].y;
        tangent[2] = this->tangents_[i].z;
        tangent[3] = this->tangents_[i].w;
        p += VERTEX_ATTRIBUTE_SIZE(V_ATTR_TANGENT);
      }
      if (this->format_ & V_ATTR_COLOR)
      {
        T_UINT32* color = (T_UINT32*)p;
        color[0] = this->colors_[i].GetPackedColor();
        p += VERTEX_ATTRIBUTE_SIZE(V_ATTR_COLOR);
      }
    }
    this->vertex_buffer_->Unlock();
    this->vertices_dirty_ = false;
  }
  for (T_UINT8 i = 0; i < this->submesh_count_; ++i)
  {
    if (!this->indices_dirties_[i])
    {
      continue;
    }
    T_UINT32* dest;
    this->index_buffers_[i]->Lock((void**)&dest);
    for (T_UINT32 j = 0; j < this->index_counts_[i]; ++j)
    {
      dest[j] = this->indices_[i][j];
    }
    this->index_buffers_[i]->Unlock();
    this->indices_dirties_[i] = false;
  }
}

void Mesh::RecalculateNormals(bool save_face_normals)
{
  NATIVE_ASSERT(this->primitive_type_ == GraphicsConstants::PRIMITIVE_TRIANGLES, "まだできてません！");

  NATIVE_ASSERT(this->format_ & GraphicsConstants::V_ATTR_NORMAL, "フォーマットに法線情報が含まれていません");
  
  if (!this->face_normals_)
  {
    this->face_normals_ = new TVec3f[this->polygon_count_];
  }
  for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
  {
    this->normals_[i] = TVec3f::zero;
  }
  for (T_UINT8 i = 0; i < this->submesh_count_; ++i)
  {
    T_UINT32 s = 0;
    for (T_UINT32 j = 0; j < this->index_counts_[i]; j += 3, ++s)
    {
      TVec3f v0 = this->vertices_[this->indices_[i][j]];
      TVec3f v1 = this->vertices_[this->indices_[i][j + 1]];
      TVec3f v2 = this->vertices_[this->indices_[i][j + 2]];
      TVec3f vv1 = v1 - v0;
      TVec3f vv2 = v2 - v1;
      this->face_normals_[s] = TVec3f::OuterProduct(vv1, vv2).Normalized();
    }
    s = 0;
    for (T_UINT32 j = 0; j < this->index_counts_[i]; j += 3, ++s)
    {
      this->normals_[this->indices_[i][j]] += this->face_normals_[s];
      this->normals_[this->indices_[i][j + 1]] += this->face_normals_[s];
      this->normals_[this->indices_[i][j + 2]] += this->face_normals_[s];
    }
  }
  for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
  {
    this->normals_[i] = this->normals_[i].Normalized();
  }
  if (this->format_ & GraphicsConstants::V_ATTR_TANGENT)
  {
    for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
    {
      const TVec3f normal = this->normals_[i];
      const TVec3f tangent = normal.x == 0.0f && normal.z == 0.0f ? TVec3f::OuterProduct(normal, TVec3f::forward) : TVec3f::OuterProduct(normal, TVec3f::up);
      this->tangents_[i].x = tangent.x;
      this->tangents_[i].y = tangent.y;
      this->tangents_[i].z = tangent.z;
      this->tangents_[i].w = 1.0f;
    }
  }
  if (!save_face_normals)
  {
    delete[] this->face_normals_;
    this->face_normals_ = nullptr;
  }
}

void Mesh::SetStreamSource() const
{
  this->vertex_buffer_->SetStreamSource();
}

void Mesh::DrawSubset(T_UINT8 index) const
{
  NATIVE_ASSERT(index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
  this->index_buffers_[index]->SetIndices();
  this->vertex_buffer_->DrawIndexedPrimitive(this->index_buffers_[index], this->primitive_type_);
}

// =================================================================
// setter/getter
// =================================================================
void Mesh::SetVertex(T_UINT32 vertex_index, const TVec3f& vertex)
{
  NATIVE_ASSERT(this->HasVertices(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->vertices_[vertex_index] == vertex)
  {
    return;
  }
  this->vertices_[vertex_index] = vertex;
  this->vertices_dirty_ = true;
}

void Mesh::SetVertices(const TVec3f* vertices)
{
  NATIVE_ASSERT(this->HasVertices(), "頂点フォーマットで定義されていない属性が呼び出されました");
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

void Mesh::SetNormal(T_UINT32 vertex_index, const TVec3f& normal)
{
  NATIVE_ASSERT(this->HasNormals(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->normals_[vertex_index] == normal)
  {
    return;
  }
  this->normals_[vertex_index] = normal;
  this->vertices_dirty_ = true;
}

void Mesh::SetNormals(const TVec3f* normals)
{
  NATIVE_ASSERT(this->HasNormals(), "頂点フォーマットで定義されていない属性が呼び出されました");
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

void Mesh::SetUv(T_UINT32 vertex_index, const TVec2f& uv)
{
  NATIVE_ASSERT(this->HasUvs(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->uvs_[vertex_index] == uv)
  {
    return;
  }
  this->uvs_[vertex_index] = uv;
  this->vertices_dirty_ = true;
}

void Mesh::SetUvs(const TVec2f* uvs)
{
  NATIVE_ASSERT(this->HasUvs(), "頂点フォーマットで定義されていない属性が呼び出されました");
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

void Mesh::SetUv2(T_UINT32 vertex_index, const TVec2f& uv2)
{
  NATIVE_ASSERT(this->HasUv2s(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->uv2s_[vertex_index] == uv2)
  {
    return;
  }
  this->uv2s_[vertex_index] = uv2;
  this->vertices_dirty_ = true;
}

void Mesh::SetUv2s(const TVec2f* uv2s)
{
  NATIVE_ASSERT(this->HasUv2s(), "頂点フォーマットで定義されていない属性が呼び出されました");
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

void Mesh::SetUv3(T_UINT32 vertex_index, const TVec2f& uv3)
{
  NATIVE_ASSERT(this->HasUv3s(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->uv3s_[vertex_index] == uv3)
  {
    return;
  }
  this->uv3s_[vertex_index] = uv3;
  this->vertices_dirty_ = true;
}

void Mesh::SetUv3s(const TVec2f* uv3s)
{
  NATIVE_ASSERT(this->HasUv3s(), "頂点フォーマットで定義されていない属性が呼び出されました");
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

void Mesh::SetUv4(T_UINT32 vertex_index, const TVec2f& uv4)
{
  NATIVE_ASSERT(this->HasUv4s(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->uv4s_[vertex_index] == uv4)
  {
    return;
  }
  this->uv4s_[vertex_index] = uv4;
  this->vertices_dirty_ = true;
}

void Mesh::SetUv4s(const TVec2f* uv4s)
{
  NATIVE_ASSERT(this->HasUv4s(), "頂点フォーマットで定義されていない属性が呼び出されました");
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

void Mesh::SetTangent(T_UINT32 vertex_index, const TVec4f& tangent)
{
  NATIVE_ASSERT(this->HasTangents(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->tangents_[vertex_index] == tangent)
  {
    return;
  }
  this->tangents_[vertex_index] = tangent;
  this->vertices_dirty_ = true;
}

void Mesh::SetTangents(const TVec4f* tangents)
{
  NATIVE_ASSERT(this->HasTangents(), "頂点フォーマットで定義されていない属性が呼び出されました");
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

void Mesh::SetColor(T_UINT32 vertex_index, const Color4F& color)
{
  NATIVE_ASSERT(this->HasColors(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->colors_[vertex_index] == color)
  {
    return;
  }
  this->colors_[vertex_index] = color;
  this->vertices_dirty_ = true;
}

void Mesh::SetColors(const Color4F* colors)
{
  NATIVE_ASSERT(this->HasColors(), "頂点フォーマットで定義されていない属性が呼び出されました");
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

void Mesh::SetIndex(T_UINT8 submesh_index, T_UINT32 index_index, T_UINT32 index)
{
  NATIVE_ASSERT(submesh_index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
  if (this->indices_[submesh_index][index_index] == index)
  {
    return;
  }
  this->indices_[submesh_index][index_index] = index;
  this->indices_dirties_[submesh_index] = true;
}

void Mesh::SetIndices(T_UINT8 submesh_index, T_UINT32* indices)
{
  NATIVE_ASSERT(submesh_index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
  for (T_UINT32 i = 0; i < this->index_counts_[submesh_index]; ++i)
  {
    if (this->indices_[submesh_index][i] == indices[i])
    {
      continue;
    }
    this->indices_[submesh_index][i] = indices[i];
    this->indices_dirties_[submesh_index] = true;
  }
}
