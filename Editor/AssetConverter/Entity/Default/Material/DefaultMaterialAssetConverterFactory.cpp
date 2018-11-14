#include "DefaultMaterialAssetConverterFactory.h"

#include "DefaultMaterialAssetEntity.h"
#include "DefaultMaterialAssetExporter.h"
#include <Entity/Default/DefaultAsset.h>
#include <Converter/AssetConverter.h>

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
  MaterialData* unlit = new MaterialData();
  unlit->shader_unique_id_ = SHADER_FLAT;
  MaterialData* white = new MaterialData();
  white->shader_unique_id_ = SHADER_NO_SHADING;
  MaterialData* stencil_shadow = new MaterialData();
  stencil_shadow->shader_unique_id_ = SHADER_STENCIL_SHADOW;
  ret->AddEntity(DefaultMaterialAssetEntity::Create(AssetInfo::Create(MATERIAL_PATH_LAMBERT, context), lambert));
  ret->AddEntity(DefaultMaterialAssetEntity::Create(AssetInfo::Create(MATERIAL_PATH_UNLIT, context), unlit));
  ret->AddEntity(DefaultMaterialAssetEntity::Create(AssetInfo::Create(MATERIAL_PATH_WHITE, context), white));
  ret->AddEntity(DefaultMaterialAssetEntity::Create(AssetInfo::Create(MATERIAL_PATH_STENCIL_SHADOW, context), stencil_shadow));
  return ret;
}
