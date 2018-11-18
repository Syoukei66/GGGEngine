#include "ModelMeshAssetConverterFactory.h"

#include "ModelMeshAssetEntity.h"
#include <Entity/File/FileAssetExporter.h>
#include <Converter/AssetConverter.h>

// =================================================================
// Methods
// =================================================================
IAssetConverter* ModelMeshAssetConverterFactory::Create(AssetConverterContext* context) const
{
  AssetProgramGenerator<ModelMeshAssetEntity>* program_generator = new AssetProgramGenerator<ModelMeshAssetEntity>(1, 1);
  program_generator->AddAsset("ModelMesh", "rcMesh");
  return new AssetConverter<ModelMeshAssetEntity>(nullptr, new FileAssetExporter<ModelMeshAssetEntity>(), program_generator);
}
