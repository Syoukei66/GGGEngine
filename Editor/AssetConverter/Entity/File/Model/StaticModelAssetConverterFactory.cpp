#include "StaticModelAssetConverterFactory.h"

#include "StaticModelAssetEntity.h"
#include "StaticModelAssetImporter.h"
#include <Entity/FileAssetExporter.h>
#include <ProgramGenerator/AssetProgramGenerator.h>
#include <Converter/AssetConverter.h>

// =================================================================
// Methods
// =================================================================
IAssetConverter* StaticModelAssetConverterFactory::Create(AssetConverterContext* context) const
{
  StaticModelAssetImporter* importer = new StaticModelAssetImporter(this->target_extensions_);
  AssetProgramGenerator<StaticModelAssetEntity>* program_generator = new AssetProgramGenerator<StaticModelAssetEntity>(1, 1);
  program_generator->AddAsset("StaticModel", "rcStaticModel");
  return new AssetConverter<StaticModelAssetEntity>(importer, new FileAssetExporter<StaticModelAssetEntity>(), program_generator);
}
