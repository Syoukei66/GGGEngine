#pragma once

#include <Entity/AssetEntity.h>

template <class Asset_>
class RawAssetEntity : public AssetEntity
{
  // =================================================================
  // Methods from AssetEntity
  // =================================================================
public:
  virtual void RegisterAssetManager(T_UINT32 uid, const std::string& extension) const override
  {
    AssetManager::AddAsset<Asset_>(uid, extension, Asset_::CreateFromFile(this->GetMetaData()->GetInputPath().c_str()));
  }

};