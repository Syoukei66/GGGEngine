#pragma once

/*!
 * @brief AssetDataCache�ŕK�v�ȃe���v���[�g������
 * �����Ă�������悤�ɂ��邽�߂̃C���^�[�t�F�[�X
 */
class IAssetDataCache
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  virtual ~IAssetDataCache() = default;
};

/*!
 * @brief AssetEntity���Ǘ�����ϊ���Asset�̃L���b�V���f�[�^�̗e��
 * �^�̃`�F�b�N��f�X�g���N�^�̋N���Ȃǂ��s����悤�ɂȂ��Ă���
 */
template <typename AssetData_>
class AssetDataCache : public IAssetDataCache
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetDataCache(AssetData_* data)
    : data_(data)
  {}

  virtual ~AssetDataCache()
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
