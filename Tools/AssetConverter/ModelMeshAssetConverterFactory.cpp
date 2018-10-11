#include "ModelMeshAssetConverterFactory.h"

#include "ModelMeshAssetEntity.h"
#include "ModelMeshAssetExporter.h"
#include "AssetConverter.h"

// =================================================================
// Methods
// =================================================================
IAssetConverter* ModelMeshAssetConverterFactory::Create(AssetConverterContext* context) const
{
  ModelMeshAssetExporter* exporter = new ModelMeshAssetExporter();
  AssetProgramGenerator<ModelMeshAssetEntity>* program_generator = new AssetProgramGenerator<ModelMeshAssetEntity>(1, 1);
  program_generator->AddAsset("ModelMesh", "rcMesh");
  return new AssetConverter<ModelMeshAssetEntity>(nullptr, nullptr, exporter, program_generator);
}
