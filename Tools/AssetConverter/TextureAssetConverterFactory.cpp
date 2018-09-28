#include "TextureAssetConverterFactory.h"

#include "TextureAssetEntity.h"
#include "TextureAssetImporter.h"
#include "TextureAssetExporter.h"
#include "AssetProgramGenerator.h"
#include "AssetConverter.h"

// =================================================================
// Methods
// =================================================================
IAssetConverter* TextureAssetConverterFactory::Create() const
{
  TextureAssetImporter* importer = new TextureAssetImporter(this->target_extensions_);
  TextureAssetExporter* exporter = new TextureAssetExporter();
  AssetProgramGenerator<TextureAssetEntity>* program_generator = new AssetProgramGenerator<TextureAssetEntity>();
  program_generator->AddAsset("Texture", "TextureAsset");
  return new AssetConverter<TextureAssetEntity>(importer, nullptr, exporter, program_generator);
}
