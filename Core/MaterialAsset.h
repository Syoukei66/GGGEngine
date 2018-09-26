#pragma once

#include "Asset.h"
#include "Material.h"

class MaterialAsset : public Asset<MaterialAsset, rcMaterial>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  MaterialAsset(const std::string& path)
    : Asset(path)
  {}

  // =================================================================
  // Methods
  // =================================================================
protected:
  rcMaterial* LoadProcess(const std::string& path) override
  {
    MaterialData* data = MaterialData::Deserialize(path);
    rcMaterial* ret = rcMaterial::Create(data);
    delete data;
    return ret;
  }

};
