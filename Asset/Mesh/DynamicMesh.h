#pragma once

#include "Mesh.h"

/*!
 * @brief ���I�ȃ��b�V���̃f�[�^
 * �f�[�^�͒��_�̊e�����Ɋi�[�����B
 * ���[�h�����CPU���ɂ����f�[�^�����݂��Ȃ��̂ŁA
 * GPU�֓]�������ۂɎg�p�ł���悤�ɂ���ɂ�CommitChanges���Ăяo���K�v������
 */
struct DynamicMeshData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(DynamicMeshData)
  {
    archive(vertex_format_);
    archive(polygon_count_);

    archive(vertex_count_);
    archive(vertices_);
    archive(normals_);
    archive(uvs_);
    archive(uv2s_);
    archive(uv3s_);
    archive(uv4s_);
    archive(tangents_);
    archive(colors_);

    archive(submesh_count_);
    archive(submesh_indices_);
    archive(submesh_polygon_counts_);

    archive(bounds_);
  }

  // =================================================================
  // Data Member
  // =================================================================
public:
  T_UINT32 vertex_format_;
  T_UINT32 polygon_count_;

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

  // IndexBuffer Params
  T_UINT32 submesh_count_;
  std::vector<std::vector<T_UINT32>> submesh_indices_;
  std::vector<T_UINT32> submesh_polygon_counts_;

  Bounds bounds_;
};

/*!
 * @brief Mesh�̋@�\�ɉ����A���b�V���̕ҏW�@�\��
 * �p�����[�^�[�ւ̃A�N�Z�X�@�\�����������b�V��
 * Mesh�ƈႢ�A�������_�ł̓o�b�t�@�ւ̃f�[�^�]�����s���Ă��Ȃ��ׁA
 * CommitChanges���Ăяo���܂Ń����_���Ŏg�p�ł��Ȃ�
 */
class rcDynamicMesh : public rcMesh
{
  friend class rcMesh;

  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcDynamicMesh);
  GG_ASSET(rcDynamicMesh, DynamicMeshData);
  GG_CREATE_FUNC(rcDynamicMesh) { return rcMesh::Init(); }
  GG_DESTRUCT_FUNC(rcDynamicMesh);

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief ���_���A�C���f�b�N�X���A�o�b�t�@���̑S�Ẵf�[�^���폜����
   */
  void Clear();

  /*!
   * @brief ���_����S�č폜����
   */
  void ClearVertices();

  /*!
   * @brief �C���f�b�N�X����S�č폜����
   */
  void ClearIndices();

  /*!
   * @brief ���_�o�b�t�@���폜����
   */
  void ClearVertexBuffer();

  /*!
   * @brief ���_�����폜����
   */
  void ClearVertexDeclaration();

  /*!
   * @brief �C���f�b�N�X�o�b�t�@��S�č폜����
   */
  void ClearIndexBuffers();

  /*!
   * @brief Mesh���̒��_�A�C���f�b�N�X����ÓI�ȃ��b�V���f�[�^�Ƃ��ăf�[�^������
   */
  void ConvertToData(StaticMeshData* dest) const;

  /*!
   * @brief Mesh���̒��_�A�C���f�b�N�X���𓮓I�ȃ��b�V���f�[�^�Ƃ��ăf�[�^������
   */
  void ConvertToData(DynamicMeshData* dest) const;

  /*!
   * @brief DynamicMesh�𕡐�����
   * �o�b�t�@�ւ̃A�N�Z�X����Ȃ���rcMesh::CloneDynamic����R�X�g
   */
  UniqueRef<rcDynamicMesh> Clone() const;

  /*!
   * @brief ���_�E�C���f�b�N�X�����R�~�b�g�����ҏW�s�̃��b�V���𐶐�����B
   */
  UniqueRef<rcMesh> CloneStatic() const;

  /*!
   * @brief ���_�E�C���f�b�N�X�����R�~�b�g�����ҏW�s�̃��b�V���𐶐�����B
   * �o�b�t�@�̃R�s�[���s���Ȃ�����R�X�g�����o�b�t�@�̏��L�����ړ�����ׁA
   * ���̃��\�b�h�g�p�ケ�̃��b�V���͎g�p�s�ɂȂ�B
   */
  UniqueRef<rcMesh> MoveStatic();

  /*!
   * @brief ���̃��b�V�������̃��b�V���̃T�u���b�V���Ƃ��Ēǉ�����
   */
  void Append(const SharedRef<const rcDynamicMesh>& other);

  /*!
   * @brief ���_���X�g���쐬����B
   * @param vertex_count ���_��
   * @param format ���_�t�H�[�}�b�g
   * @param primitive_type �v���~�e�B�u�̎��
   */
  void CreateVertices(T_UINT32 vertex_count, T_UINT32 format, Vertex::PrimitiveType primitive_type = Vertex::PrimitiveType::TRIANGLES);

  /*!
   * @brief ���_���X�g�ɐV���Ȓ��_���X�g��ǉ�����
   * @param vertex_count ���_��
   * @param format ���_�t�H�[�}�b�g
   * @param primitive_type �v���~�e�B�u�̎��
   */
  void AddVertices(T_UINT32 vertex_count, T_UINT32 format, Vertex::PrimitiveType primitive_type = Vertex::PrimitiveType::TRIANGLES);

  /*!
   * @brief �C���f�b�N�X���X�g��ǉ����A�T�u���b�V�����쐬����B
   * �K�����_���쐬������Ăяo���悤�ɁB
   * @param index_count �C���f�b�N�X��
   * @param polygon_count �|���S����
   */
  T_UINT32 AddIndices(T_UINT32 index_count, T_UINT32 polygon_count);

  /*!
   * @brief �C���f�b�N�X�o�b�t�@��ǉ����A�T�u���b�V�����쐬����B
   * �|���S�������C���f�b�N�X���ƃv���~�e�B�u�̎�ނ��玩���Ōv�Z����B
   * �K�����_�o�b�t�@���쐬������Ăяo���悤�ɁB
   * @param index_count �C���f�b�N�X��
   */
  GG_INLINE T_UINT32 AddIndices(T_UINT32 index_count)
  {
    return this->AddIndices(index_count, Vertex::PRIMITIVE_SURF_NUM(this->primitive_type_, index_count));
  }

  /*!
   * @brief ���_�A�C���f�b�N�X�����m�肵�AGPU�ɓ]������
   */
  void CommitChanges();

  /*!
   * @brief �@�����Čv�Z����
   * @param save_face_normals �ʖ@������ێ����Ă������ǂ���
   */
  void RecalculateNormals(bool save_face_normals = false);

  /*!
   * @brief �^���W�F���g�x�N�g�����Čv�Z����
   */
  void RecalculateTangents();

  /*!
   * @brief �o�E���f�B���O�{�b�N�X���Čv�Z����
   */
  void RecalculateBounds();

  // =================================================================
  // Setter / Getter
  // =================================================================
private:
  GG_INLINE void VertexAssert(bool has) const
  {
    GG_ASSERT(has, "���_�t�H�[�}�b�g�Œ�`����Ă��Ȃ��������Ăяo����܂���");
  }

public:
  GG_INLINE SharedRef<rcVertexBuffer> GetVertexBuffer()
  {
    return this->vertex_buffer_;
  }
  GG_INLINE SharedRef<rcIndexBuffer> GetIndexBuffer(T_UINT8 submesh_index = 0)
  {
    GG_ASSERT(submesh_index < this->submesh_count_, "�C���f�b�N�X�w�肪�T�u���b�V���̍ő���𒴉߂��܂����B");
    return this->submesh_index_buffers_[submesh_index];
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
    GG_ASSERT(submesh_index < this->submesh_count_, "�C���f�b�N�X�w�肪�T�u���b�V���̍ő���𒴉߂��܂����B");
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
    GG_ASSERT(submesh_index < this->submesh_count_, "�C���f�b�N�X�w�肪�T�u���b�V���̍ő���𒴉߂��܂����B");
    return this->submesh_indices_[submesh_index].data();
  }
  GG_INLINE T_UINT32 GetIndexCount(T_UINT8 submesh_index = 0) const
  {
    GG_ASSERT(submesh_index < this->submesh_count_, "�C���f�b�N�X�w�肪�T�u���b�V���̍ő���𒴉߂��܂����B");
    return this->submesh_index_buffers_[submesh_index]->GetVertexCount();
  }

  virtual size_t GetMemorySize() const override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT32 polygon_count_;
  std::vector<TVec3f> face_normals_;

  // VertexBuffer Params
  T_UINT32 vertex_format_;
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

  // IndexBuffer Params
  std::vector<std::vector<T_UINT32>> submesh_indices_;
  std::vector<T_UINT32> submesh_polygon_counts_;
  std::vector<bool> submesh_indices_dirties_;

};