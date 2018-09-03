#pragma once
#include "StaticModelConverter.h"

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>

#include "../Asset/CerealStaticModelIO.h"

#include "AssimpStaticModelImporter.h"
#include "StaticModelConverterTest.h"

#include "Logger.h"

StaticModelConverter::StaticModelConverter()
  : importer_(new Assimp::Importer())
{
  this->GetNamespaceGenerator().AddAsset("StaticModel", "StaticModelAsset");
}

StaticModelConverter::~StaticModelConverter()
{
  delete this->importer_;
}

void StaticModelConverter::GetIncludePaths(std::set<std::string>* dest) const
{
}

bool StaticModelConverter::IsTarget(const std::string& extension) const
{
  return this->importer_->IsExtensionSupported(extension.c_str());
}

void StaticModelConverter::ConvertProcess(AssetInfo* info) const
{
  //一部のファイルでメモリリークが発生
  const aiScene* scene = this->importer_->ReadFile(
    info->full_path,
    aiProcess_GenNormals |
    aiProcess_CalcTangentSpace |
    aiProcess_Triangulate |
    aiProcess_JoinIdenticalVertices |
    aiProcess_SortByPType |
    aiProcess_MakeLeftHanded |
    aiProcess_LimitBoneWeights |
    aiProcess_ImproveCacheLocality |
    aiProcess_SplitByBoneCount |
    aiProcess_PreTransformVertices
  );

  StaticModelData* data = ModelImporter::Assimp::ImportStaticModel(info, scene);
  using namespace ModelIO;
  using namespace StaticModel;
  this->ExportProcess<StaticModelData, StaticModelConverterTest>(info, data, Import, Export);
  delete data;

  Logger::ConvertAssetLog(info);
}
