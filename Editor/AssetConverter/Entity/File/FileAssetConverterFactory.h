#pragma once

#include <string>

#include "FileAssetExporter.h"
#include <ProgramGenerator/AssetProgramGenerator.h>
#include <Converter/AssetConverter.h>

namespace FileAssetConverterFactory
{

template<class Entity_>
IAssetConverter* Create(AssetImporter<Entity_>* importer, const std::string& asset_name, const std::string& class_name, T_UINT32 skip_head, T_UINT32 skip_tail)
{
  FileAssetExporter<Entity_>* exporter = new FileAssetExporter<Entity_>();
  AssetProgramGenerator<Entity_>* program_generator = new AssetProgramGenerator<Entity_>(skip_head, skip_tail);
  program_generator->AddAsset(asset_name, class_name);
  return new AssetConverter<Entity_>(importer, exporter, program_generator);
}

}
