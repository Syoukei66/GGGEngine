#include "ModelMaterialAssetConverterFactory.h"

#include "ModelMaterialAssetEntity.h"
#include <Entity/File/FileAssetExporter.h>
#include <Converter/AssetConverter.h>

// =================================================================
// Methods
// =================================================================
IAssetConverter* ModelMaterialAssetConverterFactory::Create(AssetConverterContext* context) const
{
  AssetProgramGenerator<ModelMaterialAssetEntity>* program_generator = new AssetProgramGenerator<ModelMaterialAssetEntity>(1, 0);
  program_generator->AddAsset("ModelMaterial", "rcMaterial");
  return new AssetConverter<ModelMaterialAssetEntity>(nullptr, new FileAssetExporter<ModelMaterialAssetEntity>(), program_generator);
}
