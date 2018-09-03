#include "CustomMesh.h"
#include "StaticMesh.h"

// =================================================================
// Factory Method
// =================================================================
rcCustomMesh* rcCustomMesh::Create()
{
  rcCustomMesh* ret = new rcCustomMesh();
  ret->Resource::Init();
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcCustomMesh::rcCustomMesh()
  : orginal_()
  , format_()
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
  , index_counts_()
  , indices_()
  , indices_dirties_()
{
}

rcCustomMesh::~rcCustomMesh()
{
  this->Clear();
}

// =================================================================
// Method
// =================================================================
void rcCustomMesh::Clear()
{
  this->ClearVertices(true);
  this->ClearIndices(true);
}

void rcCustomMesh::ClearVertices(bool clear_buffer)
{
  delete[] this->vertices_;
  delete[] this->normals_;
  delete[] this->uvs_;
  delete[] this->uv2s_;
  delete[] this->uv3s_;
  delete[] this->uv4s_;
  delete[] this->tangents_;
  delete[] this->colors_;

  this->vertices_ = nullptr;
  this->normals_ = nullptr;
  this->uvs_ = nullptr;
  this->uv2s_ = nullptr;
  this->uv3s_ = nullptr;
  this->uv4s_ = nullptr;
  this->tangents_ = nullptr;
  this->colors_ = nullptr;

  this->vertices_dirty_ = false;

  if (clear_buffer)
  {
    this->vertex_count_ = 0;
    if (this->vertex_buffer_)
    {
      this->vertex_buffer_->Release();
    }
    this->vertex_buffer_ = nullptr;
  }
}

void rcCustomMesh::ClearIndices(bool clear_buffer)
{
  delete[] this->face_normals_;
  if (this->indices_)
  {
    for (T_UINT8 i = 0; i < this->submesh_count_; ++i)
    {
      delete[] this->indices_[i];
    }
    delete[] this->indices_;
    delete[] this->index_counts_;
    delete[] this->indices_dirties_;
  }

  this->face_normals_ = nullptr;
  this->indices_ = nullptr;
  this->index_counts_ = nullptr;
  this->indices_dirties_ = nullptr;

  if (clear_buffer)
  {
    for (T_UINT8 i = 0; i < this->submesh_count_; ++i)
    {
      if (this->index_buffers_[i])
      {
        this->index_buffers_[i]->Release();
      }
    }
    delete[] this->index_buffers_;
    this->index_buffers_ = nullptr;
    this->submesh_count_ = 0;
  }
}

rcCustomMesh* rcCustomMesh::Clone()
{
  rcCustomMesh* clone = rcCustomMesh::Create();

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

rcStaticMesh* rcCustomMesh::CloneStatic()
{
  rcCustomMesh* clone = this->Clone();
  rcStaticMesh* ret = rcStaticMesh::Create(clone->vertex_buffer_, clone->index_buffers_, clone->submesh_count_, clone->primitive_type_);
  clone->Release();
  return ret;
}

rcStaticMesh* rcCustomMesh::MoveStatic()
{
  rcStaticMesh* ret = rcStaticMesh::Create(this->vertex_buffer_, this->index_buffers_, this->submesh_count_, this->primitive_type_);
  this->Clear();
  return ret;
}

void rcCustomMesh::CreateVertices(T_UINT32 vertex_count, T_UINT32 polygon_count, T_UINT32 format, Graphics::PrimitiveType primitive_type)
{
  this->ClearVertices(true);

  this->vertex_count_ = vertex_count;
  this->polygon_count_ = polygon_count;
  this->format_ = format;
  this->primitive_type_ = primitive_type;

  using namespace Graphics;

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
    this->colors_ = new TColor[vertex_count]{};
  }
  this->vertex_buffer_ = rcVertexBuffer::Create(
    vertex_count, 
    polygon_count,
    format
  );
  this->vertices_dirty_ = true;
}

void rcCustomMesh::CreateIndices(T_UINT8 submesh_count, T_UINT32* index_counts)
{
  this->ClearIndices(true);
  this->submesh_count_ = submesh_count;
  this->index_counts_ = new T_UINT32[submesh_count]{};
  this->indices_ = new T_UINT32*[submesh_count]{};
  this->indices_dirties_ = new bool[submesh_count]{};
  this->index_buffers_ = new rcIndexBuffer*[submesh_count]{};
  for (T_UINT8 i = 0; i < submesh_count; ++i)
  {
    this->index_counts_[i] = index_counts[i];
    this->indices_[i] = new T_UINT32[index_counts[i]]{};
    this->index_buffers_[i] = rcIndexBuffer::Create(index_counts[i]);
    this->indices_dirties_[i] = true;
  }
}

void rcCustomMesh::CommitChanges()
{
  using namespace Graphics;

  if (this->vertices_dirty_)
  {
    void* dest;
    this->vertex_buffer_->Lock(&dest);
    unsigned char* p = (unsigned char*)dest;
    for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
    {
      if (this->format_ & V_ATTR_POSITION)
      {
        T_FLOAT* vertex = (T_FLOAT*)p;
        vertex[0] = this->vertices_[i].x;
        vertex[1] = this->vertices_[i].y;
        vertex[2] = this->vertices_[i].z;
        p += V_ATTRSIZE_POSITION;
      }
      if (this->format_ & V_ATTR_NORMAL)
      {
        T_FLOAT* normal = (T_FLOAT*)p;
        normal[0] = this->normals_[i].x;
        normal[1] = this->normals_[i].y;
        normal[2] = this->normals_[i].z;
        p += V_ATTRSIZE_NORMAL;
      }
      if (this->format_ & V_ATTR_UV)
      {
        T_FLOAT* uv = (T_FLOAT*)p;
        uv[0] = this->uvs_[i].x;
        uv[1] = this->uvs_[i].y;
        p += V_ATTRSIZE_UV;
      }
      if (this->format_ & V_ATTR_UV2)
      {
        T_FLOAT* uv2 = (T_FLOAT*)p;
        uv2[0] = this->uv2s_[i].x;
        uv2[1] = this->uv2s_[i].y;
        p += V_ATTRSIZE_UV2;
      }
      if (this->format_ & V_ATTR_UV3)
      {
        T_FLOAT* uv3 = (T_FLOAT*)p;
        uv3[0] = this->uv3s_[i].x;
        uv3[1] = this->uv3s_[i].y;
        p += V_ATTRSIZE_UV3;
      }
      if (this->format_ & V_ATTR_UV4)
      {
        T_FLOAT* uv4 = (T_FLOAT*)p;
        uv4[0] = this->uv4s_[i].x;
        uv4[1] = this->uv4s_[i].y;
        p += V_ATTRSIZE_UV4;
      }
      if (this->format_ & V_ATTR_TANGENT)
      {
        T_FLOAT* tangent = (T_FLOAT*)p;
        tangent[0] = this->tangents_[i].x;
        tangent[1] = this->tangents_[i].y;
        tangent[2] = this->tangents_[i].z;
        tangent[3] = this->tangents_[i].w;
        p += V_ATTRSIZE_TANGENT;
      }
      if (this->format_ & V_ATTR_COLOR)
      {
        T_UINT32* color = (T_UINT32*)p;
        color[0] = this->colors_[i].GetPackedColor();
        p += V_ATTRSIZE_COLOR;
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

void rcCustomMesh::RecalculateNormals(bool save_face_normals)
{
  NATIVE_ASSERT(this->primitive_type_ == Graphics::PRIMITIVE_TRIANGLES, "まだできてません！");

  NATIVE_ASSERT(this->format_ & Graphics::V_ATTR_NORMAL, "フォーマットに法線情報が含まれていません");
  
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
    for (T_UINT32 j = 0, s = 0; j < this->index_counts_[i]; j += 3, ++s)
    {
      TVec3f v0 = this->vertices_[this->indices_[i][j]];
      TVec3f v1 = this->vertices_[this->indices_[i][j + 1]];
      TVec3f v2 = this->vertices_[this->indices_[i][j + 2]];
      TVec3f vv1 = v1 - v0;
      TVec3f vv2 = v2 - v1;
      this->face_normals_[s] = TVec3f::OuterProduct(vv1, vv2).Normalized();
      this->normals_[this->indices_[i][j]] += this->face_normals_[s];
      this->normals_[this->indices_[i][j + 1]] += this->face_normals_[s];
      this->normals_[this->indices_[i][j + 2]] += this->face_normals_[s];
    }
  }
  for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
  {
    this->normals_[i] = this->normals_[i].Normalized();
  }
  if (!save_face_normals)
  {
    delete[] this->face_normals_;
    this->face_normals_ = nullptr;
  }
}

void rcCustomMesh::RecalculateTangents()
{
  NATIVE_ASSERT(this->primitive_type_ == Graphics::PRIMITIVE_TRIANGLES, "まだできてません！");

  NATIVE_ASSERT(this->format_ & Graphics::V_ATTR_NORMAL, "フォーマットに法線情報が含まれていません");
  NATIVE_ASSERT(this->format_ & Graphics::V_ATTR_TANGENT, "フォーマットにtangentベクトル情報が含まれていません");

  /*
  https://answers.unity.com/questions/7789/calculating-tangents-vector4.html
  */
  for (T_UINT8 i = 0; i < this->submesh_count_; ++i)
  {
    TVec3f* tan0 = new TVec3f[this->index_counts_[i]];
    TVec3f* tan1 = new TVec3f[this->index_counts_[i]];
    
    for (T_UINT32 j = 0; j < this->index_counts_[i]; j += 3)
    {
      const T_UINT32 i0 = this->indices_[i][j + 0];
      const T_UINT32 i1 = this->indices_[i][j + 1];
      const T_UINT32 i2 = this->indices_[i][j + 2];

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

    for (T_UINT32 j = 0; j < this->index_counts_[i]; j++)
    {
      const T_UINT32 index = this->indices_[i][j];
      const TVec3f n = this->normals_[index];
      const TVec3f t = tan0[index];
      const TVec3f tmp = (t - n * TVec3f::InnerProduct(n, t)).Normalized();
      this->tangents_[index] = TVec4f(tmp.x, tmp.y, tmp.z, 0.0f);
      this->tangents_[index].w = (TVec3f::InnerProduct(TVec3f::OuterProduct(n, t), tan1[index]) < 0.0f) ? -1.0f : 1.0f;
    }
    delete[] tan0;
    delete[] tan1;
  }
}

// =================================================================
// setter/getter
// =================================================================
size_t rcCustomMesh::GetMemorySize() const
{
  size_t ret = sizeof(rcCustomMesh);
  using namespace Graphics;
  if (this->vertices_)
  {
    ret += V_ATTRSIZE_POSITION * this->vertex_count_;
  }
  if (this->normals_)
  {
    ret += V_ATTRSIZE_NORMAL * this->vertex_count_;
  }
  if (this->uvs_)
  {
    ret += V_ATTRSIZE_UV * this->vertex_count_;
  }
  if (this->uv2s_)
  {
    ret += V_ATTRSIZE_UV2 * this->vertex_count_;
  }
  if (this->uv3s_)
  {
    ret += V_ATTRSIZE_UV3 * this->vertex_count_;
  }
  if (this->uv4s_)
  {
    ret += V_ATTRSIZE_UV4 * this->vertex_count_;
  }
  if (this->tangents_)
  {
    ret += V_ATTRSIZE_TANGENT * this->vertex_count_;
  }
  if (this->colors_)
  {
    ret += V_ATTRSIZE_COLOR * this->vertex_count_;
  }
  if (this->face_normals_)
  {
    ret += sizeof(TVec3f) * this->polygon_count_;
  }
  if (this->indices_)
  {
    for (T_UINT8 i = 0; i < submesh_count_; ++i)
    {
      ret += sizeof(T_UINT32) * this->index_counts_[i];
    }
    ret += sizeof(T_UINT32) * this->submesh_count_;
    ret += sizeof(bool) * this->submesh_count_;
  }
  return ret;
}

size_t rcCustomMesh::GetVideoMemorySize() const
{
  size_t ret = 0;
  if (this->vertex_buffer_)
  {
    ret += this->vertex_buffer_->GetMemorySize();
  }
  if (this->index_buffers_)
  {
    for (T_UINT8 i = 0; i < this->submesh_count_; ++i)
    {
      if (!this->index_buffers_[i])
      {
        continue;
      }
      ret += sizeof(T_UINT32) * this->index_buffers_[i]->GetVertexesCount();
    }
  }
  return ret;
}

void rcCustomMesh::SetVertex(T_UINT32 vertex_index, const TVec3f& vertex)
{
  NATIVE_ASSERT(this->HasVertices(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->vertices_[vertex_index] == vertex)
  {
    return;
  }
  this->vertices_[vertex_index] = vertex;
  this->vertices_dirty_ = true;
}

void rcCustomMesh::SetVertices(const TVec3f* vertices)
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

void rcCustomMesh::SetNormal(T_UINT32 vertex_index, const TVec3f& normal)
{
  NATIVE_ASSERT(this->HasNormals(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->normals_[vertex_index] == normal)
  {
    return;
  }
  this->normals_[vertex_index] = normal;
  this->vertices_dirty_ = true;
}

void rcCustomMesh::SetNormals(const TVec3f* normals)
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

void rcCustomMesh::SetUv(T_UINT32 vertex_index, const TVec2f& uv)
{
  NATIVE_ASSERT(this->HasUvs(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->uvs_[vertex_index] == uv)
  {
    return;
  }
  this->uvs_[vertex_index] = uv;
  this->vertices_dirty_ = true;
}

void rcCustomMesh::SetUvs(const TVec2f* uvs)
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

void rcCustomMesh::SetUv2(T_UINT32 vertex_index, const TVec2f& uv2)
{
  NATIVE_ASSERT(this->HasUv2s(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->uv2s_[vertex_index] == uv2)
  {
    return;
  }
  this->uv2s_[vertex_index] = uv2;
  this->vertices_dirty_ = true;
}

void rcCustomMesh::SetUv2s(const TVec2f* uv2s)
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

void rcCustomMesh::SetUv3(T_UINT32 vertex_index, const TVec2f& uv3)
{
  NATIVE_ASSERT(this->HasUv3s(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->uv3s_[vertex_index] == uv3)
  {
    return;
  }
  this->uv3s_[vertex_index] = uv3;
  this->vertices_dirty_ = true;
}

void rcCustomMesh::SetUv3s(const TVec2f* uv3s)
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

void rcCustomMesh::SetUv4(T_UINT32 vertex_index, const TVec2f& uv4)
{
  NATIVE_ASSERT(this->HasUv4s(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->uv4s_[vertex_index] == uv4)
  {
    return;
  }
  this->uv4s_[vertex_index] = uv4;
  this->vertices_dirty_ = true;
}

void rcCustomMesh::SetUv4s(const TVec2f* uv4s)
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

void rcCustomMesh::SetTangent(T_UINT32 vertex_index, const TVec4f& tangent)
{
  NATIVE_ASSERT(this->HasTangents(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->tangents_[vertex_index] == tangent)
  {
    return;
  }
  this->tangents_[vertex_index] = tangent;
  this->vertices_dirty_ = true;
}

void rcCustomMesh::SetTangents(const TVec4f* tangents)
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

void rcCustomMesh::SetColor(T_UINT32 vertex_index, const TColor& color)
{
  NATIVE_ASSERT(this->HasColors(), "頂点フォーマットで定義されていない属性が呼び出されました");
  if (this->colors_[vertex_index] == color)
  {
    return;
  }
  this->colors_[vertex_index] = color;
  this->vertices_dirty_ = true;
}

void rcCustomMesh::SetColors(const TColor* colors)
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

void rcCustomMesh::SetIndex(T_UINT8 submesh_index, T_UINT32 index_index, T_UINT32 index)
{
  NATIVE_ASSERT(submesh_index < this->submesh_count_, "インデックス指定がサブメッシュの最大個数を超過しました。");
  if (this->indices_[submesh_index][index_index] == index)
  {
    return;
  }
  this->indices_[submesh_index][index_index] = index;
  this->indices_dirties_[submesh_index] = true;
}

void rcCustomMesh::SetIndices(T_UINT8 submesh_index, T_UINT32* indices)
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
