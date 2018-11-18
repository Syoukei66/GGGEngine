#pragma once

#include <Entity/AssetEntity.h>

template <class Data_, class Asset_>
class FileAssetEntity : public AssetEntity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_INIT_FUNC_2(FileAssetEntity, AssetMetaData* meta, Data_* data)
  {
    this->data_ = data;
    return AssetEntity::Init(meta);
  }
  GG_DESTRUCT_FUNC(FileAssetEntity)
  {
    delete this->data_;
    return true;
  }

  // =================================================================
  // Methods from AssetEntity
  // =================================================================
public:
  virtual void RegisterAssetManager(T_UINT32 uid, const std::string& extension) const override
  {
    AssetManager::AddAsset<Asset_>(uid, extension, Asset_::Create(*this->data_));
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline Data_* GetData()
  {
    return this->data_;
  }

  inline const Data_* GetData() const
  {
    return this->data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
protected:
  Data_* data_;

};