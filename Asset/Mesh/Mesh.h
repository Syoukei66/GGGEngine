#pragma once

#include <Core/Application/Platform/API/_Resource/VertexBuffer.h>
#include <Core/Application/Platform/API/_Resource/VertexDeclaration.h>
#include <Core/Application/Platform/API/_Resource/IndexBuffer.h>

/*!
 * @brief �ÓI�ȃ��b�V���̃f�[�^
 * �f�[�^�͂��̂܂܃o�b�t�@�Ɋi�[�ł���悤�ɂȂ��Ă���
 * Mesh���ɒ��_�̐������̃f�[�^���c��Ȃ��̂ŁADecompose���Ăяo���K�v������
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

class rcDynamicMesh;

/*!
 * @brief �Q�[����ɕ\�������I�u�W�F�N�g�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@���Ǘ�����N���X�B
 */
class rcMesh : public GGAssetObject
{
  friend rcDynamicMesh;

  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcMesh);
  GG_ASSET(rcMesh, StaticMeshData);
  GG_CREATE_FUNC(rcMesh);

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief ���_�E�C���f�b�N�X�����o�b�t�@����擾���A�ҏW�\�ȃ��b�V���𐶐�����B
   */
  SharedRef<rcDynamicMesh> CloneDynamic() const;

  /*!
   * @brief ���_�E�C���f�b�N�X�����o�b�t�@����擾���A�ҏW�\�ȃ��b�V���𐶐�����B
   * �o�b�t�@�̃R�s�[���s���Ȃ�����R�X�g�����o�b�t�@�̏��L�����ړ�����ׁA
   * ���̃��\�b�h�g�p�ケ�̃��b�V���͎g�p�s�ɂȂ�B
   */
  SharedRef<rcDynamicMesh> MoveDynamic();

  void SetStreamSource() const;
  void DrawSubset(T_UINT8 index) const;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual size_t GetMemorySize() const override;
  virtual size_t GetVideoMemorySize() const override;

  GG_INLINE Vertex::PrimitiveType GetPrimitiveType() const
  {
    return this->primitive_type_;
  }
  GG_INLINE SharedRef<const rcVertexBuffer> GetVertexBuffer() const
  {
    return this->vertex_buffer_;
  }
  GG_INLINE SharedRef<const rcIndexBuffer> GetIndexBuffer(T_UINT8 submesh_index = 0) const
  {
    GG_ASSERT(submesh_index < this->submesh_count_, "�C���f�b�N�X�w�肪�T�u���b�V���̍ő���𒴉߂��܂����B");
    return this->submesh_index_buffers_[submesh_index];
  }
  GG_INLINE T_UINT8 GetSubmeshCount() const
  {
    return this->submesh_count_;
  }
  GG_INLINE const Bounds& GetBounds() const
  {
    return this->bounds_;
  }
  GG_INLINE SharedRef<const rcVertexDeclaration> GetVertexDeclaration() const
  {
    return this->vertex_declaration_;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  Bounds bounds_;

  Vertex::PrimitiveType primitive_type_;

  T_UINT32 vertex_count_;
  T_UINT32 submesh_count_;

  SharedRef<rcVertexDeclaration> vertex_declaration_;
  SharedRef<rcVertexBuffer> vertex_buffer_;
  std::vector<SharedRef<rcIndexBuffer>> submesh_index_buffers_;

};
