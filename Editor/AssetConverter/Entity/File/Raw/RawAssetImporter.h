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
  SharedRef<Entity_> ImportProcess(AssetMetaData* meta, AssetConverterContext* context) override
  {
    return Entity_::Create(meta);
  }

};
