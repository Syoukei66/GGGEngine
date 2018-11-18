#include "ModelMeshAssetConverterFactory.h"

#include "ModelMeshAssetEntity.h"
#include "ModelMeshAssetExporter.h"
#include <Converter/AssetConverter.h>

// =================================================================
// Methods
// =================================================================
IAssetConverter* ModelMeshAssetConverterFactory::Create(AssetConverterContext* context) const
{
  ModelMeshAssetExporter* exporter = new ModelMeshAssetExporter();
  AssetProgramGenerator<ModelMeshAssetEntity>* program_generator = new AssetProgramGenerator<ModelMeshAssetEntity>(1, 1);
  program_generator->AddAsset("ModelMesh", "rcMesh");
  return new AssetConverter<ModelMeshAssetEntity>(nullptr, exporter, program_generator);
}
