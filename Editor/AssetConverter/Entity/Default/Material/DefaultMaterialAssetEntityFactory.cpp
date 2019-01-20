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
  AssetMetaData* lambert_meta = AssetMetaData::Create(MATERIAL_PATH_LAMBERT, converter, context);
  lambert_meta->GetConverterSetting()->AddSubAsset(lambert->shader_unique_id_);
  context->AddEntity(AssetEntity::Create(lambert_meta, lambert));

  MaterialData* unlit = new MaterialData();
  unlit->shader_unique_id_ = SHADER_FLAT;
  AssetMetaData* unlit_meta = AssetMetaData::Create(MATERIAL_PATH_UNLIT, converter, context);
  unlit_meta->GetConverterSetting()->AddSubAsset(unlit->shader_unique_id_);
  context->AddEntity(AssetEntity::Create(unlit_meta, unlit));
    
  MaterialData* white = new MaterialData();
  white->shader_unique_id_ = SHADER_NO_SHADING;
  AssetMetaData* white_meta = AssetMetaData::Create(MATERIAL_PATH_WHITE, converter, context);
  white_meta->GetConverterSetting()->AddSubAsset(white->shader_unique_id_);
  context->AddEntity(AssetEntity::Create(white_meta, white));

}
