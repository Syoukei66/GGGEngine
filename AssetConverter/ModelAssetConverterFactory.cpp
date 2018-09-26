#include "ModelAssetConverterFactory.h"

#include "ModelAssetEntity.h"
#include "ModelAssetImporter.h"
#include "ModelAssetEditor.h"
#include "ModelAssetExporter.h"
#include "AssetProgramGenerator.h"
#include "AssetConverter.h"

// =================================================================
// Methods
// =================================================================
IAssetConverter* ModelAssetConverterFactory::Create() const
{
  ModelAssetImporter* importer = new ModelAssetImporter(this->GetTargetExtensions());
  ModelAssetEditor* editor = new ModelAssetEditor();
  ModelAssetExporter* exporter = new ModelAssetExporter();
  AssetProgramGenerator<ModelAssetEntity>* program_generator = new AssetProgramGenerator<ModelAssetEntity>();
  return new AssetConverter<ModelAssetEntity>(importer, editor, exporter, program_generator);
}
