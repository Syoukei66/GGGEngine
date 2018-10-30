#pragma once

#include <Entity/AssetImporter.h>

template <class Entity_>
class RawAssetImporter : public AssetImporter<Entity_>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  RawAssetImporter(const std::vector<std::string>& extensions)
    : AssetImporter<Entity_>(extensions)
  {
  }

  // =================================================================
  // Methods
  // =================================================================
protected:
  Entity_* ImportProcess(AssetInfo* info, AssetConverterContext* context) override
  {
    return new Entity_(info);
  }

};
