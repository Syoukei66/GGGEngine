#include "ModelMeshAssetConverterFactory.h"

#include "ModelMeshAssetEntity.h"
#include "ModelMeshAssetExporter.h"
#include "AssetConverter.h"

// =================================================================
// Methods
// =================================================================
IAssetConverter* ModelMeshAssetConverterFactory::Create() const
{
  ModelMeshAssetExporter* exporter = new ModelMeshAssetExporter();
  return new AssetConverter<ModelMeshAssetEntity>(nullptr, nullptr, exporter, nullptr);
}
