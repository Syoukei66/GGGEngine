#include "DefaultMaterialAssetEntityFactory.h"

#include <Entity/Default/DefaultAsset.h>
#include <Entity/AssetEntity.h>
#include <Converter/AssetConverterContext.h>

void DefaultMaterialAssetEntityFactory::Create(AssetConverter* converter, AssetConverterContext* context)
{
  using namespace DefaultAsset;
  using namespace DefaultUniqueID;
  MaterialData* lambert = new MaterialData();
  lambert->shader_unique_id_ = SHADER_GOURAUD;
  MaterialData* unlit = new MaterialData();
  unlit->shader_unique_id_ = SHADER_FLAT;
  MaterialData* white = new MaterialData();
  white->shader_unique_id_ = SHADER_NO_SHADING;
  
  //IAssetDataContainer* container = new AssetDataContainer<MaterialData>(lambert);
  AssetEntity::Create(AssetMetaData::Create(MATERIAL_PATH_LAMBERT, converter, context), lambert);
  //context->AddEntity(AssetEntity::Create(AssetMetaData::Create(MATERIAL_PATH_LAMBERT, converter, context), lambert));
  //context->AddEntity(AssetEntity::Create(AssetMetaData::Create(MATERIAL_PATH_UNLIT, converter, context), unlit));
  //context->AddEntity(AssetEntity::Create(AssetMetaData::Create(MATERIAL_PATH_WHITE, converter, context), white));
}
