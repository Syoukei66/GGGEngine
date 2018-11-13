#pragma once

#include "AssetLoader.h"
#include "UniqueIdTable.h"

/*!
 * @brief AssetConverter�ŕϊ����ꂽ�A�Z�b�g���Ǘ�����N���X
 * UniqueID��^�������[�h��A���[�h��������s���Ȃ��悤�ɃL���b�V������@�\�Ȃǂ�����B
 */
class AssetManager
{
  GG_SINGLETON(AssetManager);

  friend class IAssetLoader;

  // =================================================================
  // Methods
  // =================================================================
public:
  static void Init();
  static void Init(UniqueIdTable* table);
  static void Uninit();
  static void UnloadCaches();

  /*!
   * @brief ���j�[�NID����A�Z�b�g���擾����B
   * ���j�[�NID�œo�^����Ă���A�Z�b�g�ƌ^�����̃A�Z�b�g�̌^���Ⴄ�ꍇ�̓���͖���`
   */
  template<class Asset_>
  static GG_INLINE SharedRef<Asset_> Load(T_UINT32 uid)
  {
    GG_ASSERT(uid != 0, "�����ȃA�Z�b�gID�����͂���܂���");
    if (uid > DefaultUniqueID::DEFAULT_UID_BEGIN)
    {
      return ((AssetLoader<Asset_>*)Self().loaders_.at(Self().unique_id_table_->GetDefaultAssetUniqueID(uid)))->CreateFromFile();
    }
    return ((AssetLoader<Asset_>*)Self().loaders_.at(uid))->CreateFromFile();
  }

  /*!
  * @brief �t�@�C���p�X����A�Z�b�g���擾����B
  * UniqueID�e�[�u���ɓo�^����Ă���p�X�ȊO�̃p�X���w�肳���ƃG���[
  * ���j�[�NID�œo�^����Ă���A�Z�b�g�ƌ^�����̃A�Z�b�g�̌^���Ⴄ�ꍇ�̓���͖���`
  */
  template<class Asset_>
  static GG_INLINE SharedRef<Asset_> Load(const std::string& path)
  {
    const T_UINT32 uid = Self().unique_id_table_->GetID(path);
    GG_ASSERT(uid != 0, "�����ȃt�@�C���p�X�����͂���܂���");
    return ((AssetLoader<Asset_>*)Self().loaders_.at(uid))->CreateFromFile();
  }

  /*!
  * @brief �t�@�C���p�X����AssetLoader���擾����B
  * ���j�[�NID�œo�^����Ă���A�Z�b�g�ƌ^�����̃A�Z�b�g�̌^���Ⴄ�ꍇ�̓���͖���`
  */
  template<class Asset_>
  static GG_INLINE const AssetLoader<Asset_>& GetLoader(T_UINT32 uid)
  {
    GG_ASSERT(uid != 0, "�����ȃA�Z�b�gID�����͂���܂���");
    if (uid > DefaultUniqueID::DEFAULT_UID_BEGIN)
    {
      return (const AssetLoader<Asset_>&)*Self().loaders_.at(Self().unique_id_table_->GetDefaultAssetUniqueID(uid));
    }
    return (const AssetLoader<Asset_>&)*Self().loaders_.at(uid);
  }

  /*!
  * @brief �t�@�C���p�X����AssetLoader���擾����B
  * UniqueID�e�[�u���ɓo�^����Ă���p�X�ȊO�̃p�X���w�肳���ƃG���[
  * ���j�[�NID�œo�^����Ă���A�Z�b�g�ƌ^�����̃A�Z�b�g�̌^���Ⴄ�ꍇ�̓���͖���`
  */
  template<class Asset_>
  static GG_INLINE const AssetLoader<Asset_>& GetLoader(const std::string& path)
  {
    return (const AssetLoader<Asset_>&)*Self().loaders_.at(Self().unique_id_table_->GetID(path));
  }

  /*!
   * @brief AssetLoader��o�^����B
   * ���̏�����AssetConverter���������������R�[�h�ōs����ׁA
   * ���[�U�[�����g�p���鎖�͖����B
   * ���[�U�[�����g�p�����ۂ̓���͖���`
   */
  template<class Asset_>
  static GG_INLINE const AssetLoader<Asset_>& AddAsset(T_UINT32 uid, const std::string& extension)
  {
    Self().loaders_.emplace(uid, new AssetLoader<Asset_>(uid, std::to_string(uid) + "." + extension));
    return (const AssetLoader<Asset_>&)*Self().loaders_.at(uid);
  }
  
  /*!
   * @brief AssetLoader��o�^����B
   * ��������ɂ���f�[�^�����[�_�[�ɒ��ړo�^����
   * ���ɃA�Z�b�g���������ꍇ�͂��̃A�Z�b�g���㏑������
   */
  template<class Asset_>
  static GG_INLINE const AssetLoader<Asset_>& AddAsset(T_UINT32 uid, const std::string& extension, const SharedRef<Asset_>& asset)
  {
    Self().loaders_[uid] = new AssetLoader<Asset_>(uid, std::to_string(uid) + "." + extension, asset);
    return (const AssetLoader<Asset_>&)*Self().loaders_.at(uid);
  }
  // =================================================================
  // Data Members
  // =================================================================
private:
  std::unordered_map<T_UINT32, IAssetLoader*> loaders_;
  UniqueIdTable* unique_id_table_;

};
