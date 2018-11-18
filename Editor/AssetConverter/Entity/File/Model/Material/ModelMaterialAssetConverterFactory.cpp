#include "ModelMaterialAssetConverterFactory.h"

#include "ModelMaterialAssetEntity.h"
#include "ModelMaterialAssetExporter.h"
#include <Converter/AssetConverter.h>

// =================================================================
// Methods
// =================================================================
IAssetConverter* ModelMaterialAssetConverterFactory::Create(AssetConverterContext* context) const
{
  ModelMaterialAssetExporter* exporter = new ModelMaterialAssetExporter();
  AssetProgramGenerator<ModelMaterialAssetEntity>* program_generator = new AssetProgramGenerator<ModelMaterialAssetEntity>(1, 0);
  program_generator->AddAsset("ModelMaterial", "rcMaterial");
  return new AssetConverter<ModelMaterialAssetEntity>(nullptr, exporter, program_generator);
}
