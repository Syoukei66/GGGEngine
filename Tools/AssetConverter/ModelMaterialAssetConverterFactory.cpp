#include "ModelMaterialAssetConverterFactory.h"

#include "ModelMaterialAssetEntity.h"
#include "ModelMaterialAssetExporter.h"
#include "AssetConverter.h"

// =================================================================
// Methods
// =================================================================
IAssetConverter* ModelMaterialAssetConverterFactory::Create() const
{
  ModelMaterialAssetExporter* exporter = new ModelMaterialAssetExporter();
  AssetProgramGenerator<ModelMaterialAssetEntity>* program_generator = new AssetProgramGenerator<ModelMaterialAssetEntity>(1, 0);
  program_generator->AddAsset("ModelMaterial", "rcMaterial");
  return new AssetConverter<ModelMaterialAssetEntity>(nullptr, nullptr, exporter, program_generator);
}
