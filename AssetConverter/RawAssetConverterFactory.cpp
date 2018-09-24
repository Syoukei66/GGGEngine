#include "RawAssetConverterFactory.h"

#include "RawAssetEntity.h"
#include "RawAssetImporter.h"
#include "RawAssetEditor.h"
#include "RawAssetExporter.h"
#include "AssetProgramGenerator.h"
#include "AssetConverter.h"

// =================================================================
// Methods
// =================================================================
IAssetConverter* RawAssetConverterFactory::Create() const
{
  RawAssetImporter* importer = new RawAssetImporter(this->GetTargetExtensions());
  RawAssetEditor* editor = new RawAssetEditor();
  RawAssetExporter* exporter = new RawAssetExporter();
  AssetProgramGenerator<RawAssetEntity>* program_generator = new AssetProgramGenerator<RawAssetEntity>();
  return new AssetConverter<RawAssetEntity>(importer, editor, exporter, program_generator);
}
