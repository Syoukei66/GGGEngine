#include "ModelMeshAssetConverterFactory.h"

#include "ModelMeshAssetEntity.h"
#include "ModelMeshAssetExporter.h"
#include "AssetProgramGenerator.h"
#include "AssetConverter.h"

// =================================================================
// Methods
// =================================================================
IAssetConverter* ModelMeshAssetConverterFactory::Create() const
{
  ModelMeshAssetExporter* exporter = new ModelMeshAssetExporter();
  AssetProgramGenerator<ModelMeshAssetEntity>* program_generator = new AssetProgramGenerator<ModelMeshAssetEntity>();
  return new AssetConverter<ModelMeshAssetEntity>(nullptr, nullptr, exporter, program_generator);
}
