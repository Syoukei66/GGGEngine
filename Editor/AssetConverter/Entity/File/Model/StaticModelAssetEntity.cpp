#include "StaticModelAssetEntity.h"

#include "StaticModelAssetImporter.h"

IAssetConverter* StaticModelAssetEntity::CreateConverter()
{
  return FileAssetConverterFactory::Create<StaticModelAssetEntity>(new StaticModelAssetImporter({ "x", "fbx", "blend" }), "StaticModel", "rcStaticModel", 1, 1);
}
