#include "TextureAssetConverterFactory.h"

#include "TextureAssetEntity.h"
#include "TextureAssetImporter.h"
#include "TextureAssetExporter.h"
#include <ProgramGenerator/AssetProgramGenerator.h>
#include <Converter/AssetConverter.h>

// =================================================================
// Methods
// =================================================================
IAssetConverter* TextureAssetConverterFactory::Create(AssetConverterContext* context) const
{
  TextureAssetImporter* importer = new TextureAssetImporter(this->target_extensions_);
  TextureAssetExporter* exporter = new TextureAssetExporter();
  AssetProgramGenerator<TextureAssetEntity>* program_generator = new AssetProgramGenerator<TextureAssetEntity>(1, 0);
  program_generator->AddAsset("Texture", "rcTexture");
  return new AssetConverter<TextureAssetEntity>(importer, nullptr, exporter, program_generator);
}
