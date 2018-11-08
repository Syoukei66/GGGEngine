#include "ModelAssetConverterFactory.h"

#include "ModelAssetEntity.h"
#include "ModelAssetImporter.h"
#include "ModelAssetExporter.h"
#include <ProgramGenerator/AssetProgramGenerator.h>
#include <Converter/AssetConverter.h>

// =================================================================
// Methods
// =================================================================
IAssetConverter* ModelAssetConverterFactory::Create(AssetConverterContext* context) const
{
  ModelAssetImporter* importer = new ModelAssetImporter(this->target_extensions_);
  ModelAssetExporter* exporter = new ModelAssetExporter();
  AssetProgramGenerator<ModelAssetEntity>* program_generator = new AssetProgramGenerator<ModelAssetEntity>(1, 1);
  program_generator->AddAsset("Model", "rcModel");
  return new AssetConverter<ModelAssetEntity>(importer, nullptr, exporter, program_generator);
}
