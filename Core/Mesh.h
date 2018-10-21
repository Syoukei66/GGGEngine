#pragma once

#include "NativeType.h"
#include "Resource.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Color.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "MeshData.h"

#include "GraphicsConstants.h"

class rcMesh : public Resource
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueResource<rcMesh> CreateFromFile(const char* path);
  static UniqueResource<rcMesh> Create();
  static UniqueResource<rcMesh> Create(const MeshData* data);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcMesh();
  virtual ~rcMesh();

  // =================================================================
  // Methods
  // =================================================================
public:
  void Clear();
  void ClearVertices(bool clear_buffer);
  void ClearIndices(bool clear_buffer);

  UniqueResource<rcMesh> Clone(bool read_only);

  void CreateVertices(T_UINT32 vertex_count, T_UINT32 polygon_count, T_UINT32 format, Graphics::PrimitiveType primitive_type = Graphics::PRIMITIVE_TRIANGLES);
  inline void CreateVerticesWithIndex(T_UINT32 vertex_count, T_UINT32 index_count, T_UINT32 format, Graphics::PrimitiveType primitive_type = Graphics::PRIMITIVE_TRIANGLES)
  {
    CreateVertices(vertex_count, Graphics::PRIMITIVE_SURF_NUM(primitive_type, index_count), format, primitive_type);
  }
  inline void CreateIndices(T_UINT32 index_count)
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
  // setter/getter
  // =================================================================
public:
  inline virtual const char* GetResourceName() override
  {
    return "Mesh";
  }

  virtual size_t GetMemorySize() const override;
  virtual size_t GetVideoMemorySize() const override;

  inline void SetPrimitiveType(Graphics::PrimitiveType type)
  {
    this->primitive_type_ = type;
  }

  inline T_UINT32 GetFaceCount() const
  {
    return this->polygon_count_;
  }
  inline const TVec3f& GetFaceNormal(T_UINT32 index) const
  {
    return this->face_normals_[index];
  }

  //Vertex Buffer
  void SetVertex(T_UINT32 vertex_index, const TVec3f& vertex);
  void SetVertices(const TVec3f* vertices);
  inline const TVec3f& GetVertex(T_UINT32 vertex_index) const
  {
    NATIVE_ASSERT(this->HasVertices(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
    return this->vertices_[vertex_index];
  }
  inline const TVec3f* GetVertices() const
  {
    NATIVE_ASSERT(this->HasVertices(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
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
    NATIVE_ASSERT(this->HasNormals(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
    return this->normals_[vertex_index];
  }
  inline const TVec3f* GetNormals() const
  {
    NATIVE_ASSERT(this->HasNormals(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
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
    NATIVE_ASSERT(this->HasUvs(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
    return this->uvs_[vertex_index];
  }
  inline const TVec2f* GetUvs() const
  {
    NATIVE_ASSERT(this->HasUvs(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
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
    NATIVE_ASSERT(this->HasUv2s(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
    return this->uv2s_[vertex_index];
  }
  inline const TVec2f* GetUv2s() const
  {
    NATIVE_ASSERT(this->HasUv2s(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
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
    NATIVE_ASSERT(this->HasUv3s(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
    return this->uv3s_[vertex_index];
  }
  inline const TVec2f* GetUv3s() const
  {
    NATIVE_ASSERT(this->HasUv3s(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
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
    NATIVE_ASSERT(this->HasUv4s(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
    return this->uv4s_[vertex_index];
  }
  inline const TVec2f* GetUv4s() const
  {
    NATIVE_ASSERT(this->HasUv4s(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
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
    NATIVE_ASSERT(this->HasTangents(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
    return this->tangents_[vertex_index];
  }
  inline const TVec4f* GetTangents() const
  {
    NATIVE_ASSERT(this->HasTangents(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
    return this->tangents_;
  }
  inline bool HasTangents() const
  {
    return this->tangents_;
  }

  void SetColor(T_UINT32 vertex_index, const TColor& tangent);
  void SetColors(const TColor* colors);
  inline const TColor& GetColor(T_UINT32 vertex_index) const
  {
    NATIVE_ASSERT(this->HasColors(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
    return this->colors_[vertex_index];
  }
  inline const TColor* GetColors() const
  {
    NATIVE_ASSERT(this->HasColors(), "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
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

  //Index Buffer
  void SetIndex(T_UINT8 submesh_index, T_UINT32 index_index, T_UINT32 index);
  void SetIndices(T_UINT8 submesh_index, T_UINT32* indices);
  inline T_UINT32 GetIndex(T_UINT8 submesh_index, T_UINT32 index_index) const
  {
    NATIVE_ASSERT(submesh_index < this->submesh_count_, "�C���f�b�N�X�w�肪�T�u���b�V���̍ő���𒴉߂��܂����B");
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
    NATIVE_ASSERT(submesh_index < this->submesh_count_, "�C���f�b�N�X�w�肪�T�u���b�V���̍ő���𒴉߂��܂����B");
    return this->indices_[submesh_index];
  }
  inline T_UINT32 GetIndexCount(T_UINT8 submesh_index = 0) const
  {
    NATIVE_ASSERT(submesh_index < this->submesh_count_, "�C���f�b�N�X�w�肪�T�u���b�V���̍ő���𒴉߂��܂����B");
    return this->index_counts_[submesh_index];
  }

  inline Graphics::PrimitiveType GetPrimitiveType() const
  {
    return this->primitive_type_;
  }
  inline SharedRef<rcVertexBuffer> GetVertexBuffer()
  {
    return this->vertex_buffer_;
  }
  inline SharedRef<const rcVertexBuffer> GetVertexBuffer() const
  {
    return this->vertex_buffer_;
  }
  inline SharedRef<rcIndexBuffer> GetIndexBuffer(T_UINT8 submesh_index = 0)
  {
    NATIVE_ASSERT(submesh_index < this->submesh_count_, "�C���f�b�N�X�w�肪�T�u���b�V���̍ő���𒴉߂��܂����B");
    return this->index_buffers_[submesh_index];
  }
  inline SharedRef<const rcIndexBuffer> GetIndexBuffer(T_UINT8 submesh_index = 0) const
  {
    NATIVE_ASSERT(submesh_index < this->submesh_count_, "�C���f�b�N�X�w�肪�T�u���b�V���̍ő���𒴉߂��܂����B");
    return this->index_buffers_[submesh_index];
  }
  inline T_UINT8 GetSubmeshCount() const
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
  //w�͖@���}�b�v�̃~���[�����O�Ɏg�p(Unity���Q�l)
  TVec4f* tangents_;
  TColor* colors_;
  //bindPoses
  //boneWeights
  //bounds
  bool vertices_dirty_;

  T_UINT32* index_counts_;
  T_UINT32** indices_;
  bool* indices_dirties_;

  Graphics::PrimitiveType primitive_type_;
  SharedRef<rcVertexBuffer> vertex_buffer_;

  T_UINT8 submesh_count_;
  SharedRef<rcIndexBuffer>* index_buffers_;

};
