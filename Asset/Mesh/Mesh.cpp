#include "Mesh.h"

// =================================================================
// GGG Statement
// =================================================================
void rcMesh::Init(const MeshData& data)
{
  this->read_only_ = true;
  this->format_ = data.vertex_format_;
  this->vertex_count_ = data.vertex_count_;
  this->primitive_type_ = Vertex::PRIMITIVE_TRIANGLES;
  this->submesh_count_ = data.submesh_count_;

  //Vertex Buffer
  this->vertex_buffer_ = rcVertexBuffer::Create(data.vertex_count_, data.vertex_format_);
  unsigned char* p;
  this->vertex_buffer_->Lock((void**)&p);
  GG_ASSERT(data.vertex_size_ == Vertex::CalcVertexSize(data.vertex_format_), "MeshData���쐬�������ƒ��_�f�[�^�̃T�C�Y���قȂ��Ă��܂�");
  const T_UINT64 byte_count = data.vertex_count_ * data.vertex_size_;
  for (T_UINT64 i = 0; i < byte_count; ++i)
  {
    p[i] = data.data_[i];
  }
  this->vertex_buffer_->Unlock();

  this->polygon_count_ = 0;
  //Index Buffers
  this->index_buffers_ = new SharedRef<rcIndexBuffer>[data.submesh_count_]();
  for (T_UINT32 i = 0, ii = 0; i < data.submesh_count_; ++i)
  {
    T_UINT32* index_data;
    this->index_buffers_[i] = rcIndexBuffer::Create(data.submesh_index_counts_[i], data.submesh_polygon_counts_[i]);
    this->index_buffers_[i]->Lock((void**)&index_data);
    for (T_UINT32 j = 0; j < data.submesh_index_counts_[i]; ++j)
    {
      index_data[j] = data.indices_[ii + j];
    }
    this->index_buffers_[i]->Unlock();
    ii += data.submesh_index_counts_[i];
    this->polygon_count_ += data.submesh_polygon_counts_[i];
  }
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcMesh::~rcMesh()
{
  this->Clear();
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
    this->vertex_buffer_ = nullptr;
  }
}

void rcMesh::ClearIndices(bool clear_buffer)
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
    delete[] this->index_buffers_;
    this->index_buffers_ = nullptr;
    this->submesh_count_ = 0;
  }
}

UniqueRef<rcMesh> rcMesh::Clone(bool read_only)
{
  UniqueRef<rcMesh> clone = rcMesh::Create();

  clone->orginal_ = this;
  clone->CreateVertices(this->vertex_count_, this->format_, this->primitive_type_);
  clone->CreateIndices(this->submesh_count_, this->index_counts_);
  if (this->HasVertices()) clone->SetVertices(this->vertices_);
  if (this->HasNormals()) clone->SetNormals(this->normals_);
  if (this->HasUvs()) clone->SetUvs(this->uvs_);
  if (this->HasUv2s()) clone->SetUv2s(this->uv2s_);
  if (this->HasUv3s()) clone->SetUv3s(this->uv3s_);
  if (this->HasUv4s()) clone->SetUv4s(this->uv4s_);
  if (this->HasTangents()) clone->SetTangents(this->tangents_);
  if (this->HasColors()) clone->SetColors(this->colors_);
  clone->CommitChanges(read_only);
  return clone;
}

void rcMesh::CreateVertices(T_UINT32 vertex_count, T_UINT32 polygon_count, T_UINT32 format, Vertex::PrimitiveType primitive_type)
{
  this->ClearVertices(true);

  this->vertex_count_ = vertex_count;
  this->polygon_count_ = polygon_count;
  this->format_ = format;
  this->primitive_type_ = primitive_type;

  using namespace Vertex;

  if (format & V_ATTR_POSITION) this->vertices_ = new TVec3f[vertex_count]{};
  if (format & V_ATTR_NORMAL) this->normals_ = new TVec3f[vertex_count]{};
  if (format & V_ATTR_UV) this->uvs_ = new TVec2f[vertex_count]{};
  if (format & V_ATTR_UV2) this->uv2s_ = new TVec2f[vertex_count]{};
  if (format & V_ATTR_UV3) this->uv3s_ = new TVec2f[vertex_count]{};
  if (format & V_ATTR_UV4) this->uv4s_ = new TVec2f[vertex_count]{};
  if (format & V_ATTR_TANGENT) this->tangents_ = new TVec4f[vertex_count]{};
  if (format & V_ATTR_COLOR) this->colors_ = new TColor[vertex_count]{};
  this->vertex_buffer_ = rcVertexBuffer::Create(
    vertex_count,
    polygon_count
  );
  this->vertices_dirty_ = true;
}

void rcMesh::CreateIndices(T_UINT8 submesh_count, T_UINT32* index_counts, T_UINT32* polygon_counts)
{
  GG_ASSERT(polygon_counts || this->polygon_count_ > 0, "�|���S�������s��ł�");
  this->ClearIndices(true);
  this->submesh_count_ = submesh_count;
  this->index_counts_ = new T_UINT32[submesh_count]{};
  this->indices_ = new T_UINT32*[submesh_count] {};
  this->indices_dirties_ = new bool[submesh_count] {};
  this->index_buffers_ = new SharedRef<rcIndexBuffer>[submesh_count] {};
  for (T_UINT8 i = 0; i < submesh_count; ++i)
  {
    this->index_counts_[i] = index_counts[i];
    this->indices_[i] = new T_UINT32[index_counts[i]]{};
    this->index_buffers_[i] = rcIndexBuffer::Create(index_counts[i], polygon_counts ? polygon_counts[i] : this->polygon_count_);
    this->indices_dirties_[i] = true;
  }
}

void rcMesh::CommitChanges(bool read_only)
{
  using namespace Vertex;
  
  this->read_only_ = read_only;

  if (this->vertices_dirty_)
  {
    void* dest;
    this->vertex_buffer_->Lock(&dest);
    unsigned char* p = (unsigned char*)dest;
    for (T_UINT32 i = 0; i < this->vertex_count_; ++i)
    {
      if (this->format_ & V_ATTR_POSITION) SetVertexPosition(this->vertices_[i], &p);
      if (this->format_ & V_ATTR_NORMAL) SetVertexNormal(this->normals_[i], &p);
      if (this->format_ & V_ATTR_UV) SetVertexUv(this->uvs_[i], &p);
      if (this->format_ & V_ATTR_UV2) SetVertexUv2(this->uv2s_[i], &p);
      if (this->format_ & V_ATTR_UV3) SetVertexUv3(this->uv3s_[i], &p);
      if (this->format_ & V_ATTR_UV4) SetVertexUv4(this->uv4s_[i], &p);
      if (this->format_ & V_ATTR_TANGENT) SetVertexTangent(this->tangents_[i], &p);
      if (this->format_ & V_ATTR_COLOR) SetVertexColor(this->colors_[i], &p);
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
  if (this->read_only_)
  {
    this->ClearVertices(false);
    this->ClearIndices(false);
  }
}

void rcMesh::RecalculateNormals(bool save_face_normals)
{
  GG_ASSERT(this->primitive_type_ == Vertex::PRIMITIVE_TRIANGLES, "�܂��ł��Ă܂���I");

  GG_ASSERT(this->format_ & Vertex::V_ATTR_NORMAL, "�t�H�[�}�b�g�ɖ@����񂪊܂܂�Ă��܂���");

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
      this->face_normals_[s] = TVec3f::Cross(vv1, vv2).Normalized();
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

void rcMesh::RecalculateTangents()
{
  GG_ASSERT(this->primitive_type_ == Vertex::PRIMITIVE_TRIANGLES, "�܂��ł��Ă܂���I");

  GG_ASSERT(this->format_ & Vertex::V_ATTR_NORMAL, "�t�H�[�}�b�g�ɖ@����񂪊܂܂�Ă��܂���");
  GG_ASSERT(this->format_ & Vertex::V_ATTR_TANGENT, "�t�H�[�}�b�g��tangent�x�N�g����񂪊܂܂�Ă��܂���");

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
  this->vertex_buffer_->SetStreamSource();
}

void rcMesh::DrawSubset(T_UINT8 index) const
{
  GG_ASSERT(index < this->submesh_count_, "�C���f�b�N�X�w�肪�T�u���b�V���̍ő���𒴉߂��܂����B");
  this->index_buffers_[index]->SetIndices();
  this->vertex_buffer_->DrawIndexedPrimitive(this->index_buffers_[index], this->primitive_type_);
}

// =================================================================
// Setter / Getter
// =================================================================
size_t rcMesh::GetMemorySize() const
{
  size_t ret = sizeof(rcMesh);
  using namespace Vertex;
  ret += this->vertex_count_ * CalcVertexSize(this->format_);
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

size_t rcMesh::GetVideoMemorySize() const
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

void rcMesh::SetVertex(T_UINT32 vertex_index, const TVec3f& vertex)
{
  GG_ASSERT(this->HasVertices(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
  if (this->vertices_[vertex_index] == vertex)
  {
    return;
  }
  this->vertices_[vertex_index] = vertex;
  this->vertices_dirty_ = true;
}

void rcMesh::SetVertices(const TVec3f* vertices)
{
  GG_ASSERT(this->HasVertices(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
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
  GG_ASSERT(this->HasNormals(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
  if (this->normals_[vertex_index] == normal)
  {
    return;
  }
  this->normals_[vertex_index] = normal;
  this->vertices_dirty_ = true;
}

void rcMesh::SetNormals(const TVec3f* normals)
{
  GG_ASSERT(this->HasNormals(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
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
  GG_ASSERT(this->HasUvs(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
  if (this->uvs_[vertex_index] == uv)
  {
    return;
  }
  this->uvs_[vertex_index] = uv;
  this->vertices_dirty_ = true;
}

void rcMesh::SetUvs(const TVec2f* uvs)
{
  GG_ASSERT(this->HasUvs(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
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
  GG_ASSERT(this->HasUv2s(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
  if (this->uv2s_[vertex_index] == uv2)
  {
    return;
  }
  this->uv2s_[vertex_index] = uv2;
  this->vertices_dirty_ = true;
}

void rcMesh::SetUv2s(const TVec2f* uv2s)
{
  GG_ASSERT(this->HasUv2s(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
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
  GG_ASSERT(this->HasUv3s(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
  if (this->uv3s_[vertex_index] == uv3)
  {
    return;
  }
  this->uv3s_[vertex_index] = uv3;
  this->vertices_dirty_ = true;
}

void rcMesh::SetUv3s(const TVec2f* uv3s)
{
  GG_ASSERT(this->HasUv3s(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
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
  GG_ASSERT(this->HasUv4s(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
  if (this->uv4s_[vertex_index] == uv4)
  {
    return;
  }
  this->uv4s_[vertex_index] = uv4;
  this->vertices_dirty_ = true;
}

void rcMesh::SetUv4s(const TVec2f* uv4s)
{
  GG_ASSERT(this->HasUv4s(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
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
  GG_ASSERT(this->HasTangents(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
  if (this->tangents_[vertex_index] == tangent)
  {
    return;
  }
  this->tangents_[vertex_index] = tangent;
  this->vertices_dirty_ = true;
}

void rcMesh::SetTangents(const TVec4f* tangents)
{
  GG_ASSERT(this->HasTangents(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
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
  GG_ASSERT(this->HasColors(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
  if (this->colors_[vertex_index] == color)
  {
    return;
  }
  this->colors_[vertex_index] = color;
  this->vertices_dirty_ = true;
}

void rcMesh::SetColors(const TColor* colors)
{
  GG_ASSERT(this->HasColors(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
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
  GG_ASSERT(submesh_index < this->submesh_count_, "�C���f�b�N�X�w�肪�T�u���b�V���̍ő���𒴉߂��܂����B");
  if (this->indices_[submesh_index][index_index] == index)
  {
    return;
  }
  this->indices_[submesh_index][index_index] = index;
  this->indices_dirties_[submesh_index] = true;
}

void rcMesh::SetIndices(T_UINT8 submesh_index, T_UINT32* indices)
{
  GG_ASSERT(submesh_index < this->submesh_count_, "�C���f�b�N�X�w�肪�T�u���b�V���̍ő���𒴉߂��܂����B");
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
