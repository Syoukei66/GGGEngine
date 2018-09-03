#pragma once

#include "Asset.h"
#include "CustomMaterial.h"

class MaterialAsset : public Asset<MaterialAsset, rcCustomMaterial>
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
  rcCustomMaterial* LoadProcess(const std::string& path) override
  {
    MaterialData* data = MaterialData::Deserealize(path);
    rcCustomMaterial* ret = rcCustomMaterial::Create(*data);
    delete data;
    return ret;
  }

};
