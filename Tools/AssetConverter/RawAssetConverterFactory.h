#pragma once

#include <string>

#include "RawAssetImporter.h"
#include "RawAssetExporter.h"
#include "AssetProgramGenerator.h"
#include "AssetConverter.h"

namespace RawAssetConverterFactory
{

template<class Entity_, class... Args_>
IAssetConverter* Create(const std::string& asset_name, const std::string& class_name, Args_... args)
{
  RawAssetImporter<Entity_>* importer = new RawAssetImporter<Entity_>(std::initializer_list<std::string>{args...});
  RawAssetExporter<Entity_>* exporter = new RawAssetExporter<Entity_>();
  AssetProgramGenerator<Entity_>* program_generator = new AssetProgramGenerator<Entity_>(1, 0);
  program_generator->AddAsset(asset_name, class_name);
  return new AssetConverter<Entity_>(importer, nullptr, exporter, program_generator);
}

}