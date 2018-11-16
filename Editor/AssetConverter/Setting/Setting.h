#pragma once

#include <string>

#include <Cereal/cereal.hpp>
#include <Cereal/types/string.hpp>
#include <Cereal/types/common.hpp>
#include <Cereal/access.hpp>

#include <Entity/File/Texture/TextureAssetConverterFactory.h>
#include <Entity/File/Model/StaticModelAssetConverterFactory.h>
#include <Entity/File/Model/Mesh/ModelMeshAssetConverterFactory.h>
#include <Entity/File/Model/Material/ModelMaterialAssetConverterFactory.h>
#include <Entity/Default/Mesh/DefaultMeshAssetConverterFactory.h>
#include <Entity/AssetInfo.h>

struct Setting
{
  Setting() = default;

  static Setting* Create();

  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::make_nvp("TextureAssetConverter", this->texture_asset_converter_factory));
    ar(cereal::make_nvp("ModelAssetConverter", this->model_asset_converter_factory));
    ar(cereal::make_nvp("ModelMeshAssetConverter", this->model_mesh_asset_converter_factory));
    ar(cereal::make_nvp("ModelMaterialAssetConverter", this->model_material_asset_converter_factory));
    ar(cereal::make_nvp("DefaultMeshAssetConverter", this->default_mesh_asset_converter_factory));
  }

  TextureAssetConverterFactory texture_asset_converter_factory;
  StaticModelAssetConverterFactory model_asset_converter_factory;
  ModelMeshAssetConverterFactory model_mesh_asset_converter_factory;
  ModelMaterialAssetConverterFactory model_material_asset_converter_factory;
  DefaultMeshAssetConverterFactory default_mesh_asset_converter_factory;

};
CEREAL_CLASS_VERSION(Setting, 1);
CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(FileAssetConverterFactory, cereal::specialization::member_serialize)
