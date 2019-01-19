#pragma once

class AssetConverter;

/*!
 * @brief AssetDataContainer�ŕK�v�ȃe���v���[�g������
 * �����Ă�������悤�ɂ��邽�߂̃C���^�[�t�F�[�X
 */
class IAssetDataContainer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  virtual ~IAssetDataContainer() = default;
};

/*!
 * @brief AssetEntity���Ǘ�����ϊ���Asset�̃L���b�V���f�[�^�̗e��
 * �^�̃`�F�b�N��f�X�g���N�^�̋N���Ȃǂ��s����悤�ɂȂ��Ă���
 */
template <class AssetData_>
class AssetDataContainer : public IAssetDataContainer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
   * @brief �R���X�g���N�^
   * @param data �f�[�^
   */
  AssetDataContainer(AssetData_* data)
    : data_(data)
  {
  }

  virtual ~AssetDataContainer()
  {
    delete this->data_;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  AssetData_* GetData()
  {
    return this->data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetData_* data_;

};
