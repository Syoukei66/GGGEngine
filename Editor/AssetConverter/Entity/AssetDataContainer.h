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
template <typename AssetData_>
class AssetDataContainer : public IAssetDataContainer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
   * @brief �R���X�g���N�^
   * @param data �f�[�^
   * @param converter �f�[�^���쐬����Converter
   */
  AssetDataContainer(AssetData_* data, const AssetConverter* converter)
    : data_(data)
    , converter_(converter)
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

  const AssetConverter* GetConverter()
  {
    return this->converter_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetData_* data_;
  const AssetConverter* converter_;

};
