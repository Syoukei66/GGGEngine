#pragma once

#include <string>

#include <Cereal/cereal.hpp>
#include <Cereal/types/string.hpp>
#include <Cereal/types/common.hpp>
#include <Cereal/access.hpp>
#include <Entity/Default/Mesh/DefaultMeshAssetConverterFactory.h>
#include <Entity/AssetMetaData.h>

struct Setting
{
  Setting() = default;

  static Setting* Create();

  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::make_nvp("DefaultMeshAssetConverter", this->default_mesh_asset_converter_factory));
  }

  DefaultMeshAssetConverterFactory default_mesh_asset_converter_factory;

};
CEREAL_CLASS_VERSION(Setting, 1);
