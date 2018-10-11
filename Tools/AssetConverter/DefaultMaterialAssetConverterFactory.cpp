#include "DefaultMaterialAssetConverterFactory.h"

#include "DefaultMaterialAssetEntity.h"
#include "DefaultMaterialAssetExporter.h"
#include "DefaultAsset.h"
#include "AssetConverter.h"

IAssetConverter* DefaultMaterialAssetConverterFactory::Create(AssetConverterContext* context)
{
  DefaultMaterialAssetExporter* exporter = new DefaultMaterialAssetExporter();
  AssetProgramGenerator<DefaultMaterialAssetEntity>* program_generator = new AssetProgramGenerator<DefaultMaterialAssetEntity>(2, 0);
  program_generator->AddAsset("DefaultMaterial", "rcMaterial");
  AssetConverter<DefaultMaterialAssetEntity>* ret = new AssetConverter<DefaultMaterialAssetEntity>(nullptr, nullptr, exporter, program_generator);

  using namespace DefaultAsset;
  using namespace DefaultUniqueID;
  MaterialData* lambert = new MaterialData();
  lambert->shader_unique_id_ = SHADER_GOURAUD;
  MaterialData* sprite = new MaterialData();
  sprite->shader_unique_id_ = SHADER_SPRITE;
  MaterialData* white = new MaterialData();
  white->shader_unique_id_ = SHADER_NO_SHADING;
  ret->AddEntity(new DefaultMaterialAssetEntity(AssetInfo::Create(MATERIAL_PATH_LAMBERT, context), lambert));
  ret->AddEntity(new DefaultMaterialAssetEntity(AssetInfo::Create(MATERIAL_PATH_SPRITE, context), sprite));
  ret->AddEntity(new DefaultMaterialAssetEntity(AssetInfo::Create(MATERIAL_PATH_WHITE, context), white));
  return ret;
}
