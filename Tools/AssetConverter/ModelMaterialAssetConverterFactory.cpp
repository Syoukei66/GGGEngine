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
  return new AssetConverter<ModelMaterialAssetEntity>(nullptr, nullptr, exporter, nullptr);
}
