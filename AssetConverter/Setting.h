#pragma once

#include <string>

#include "Cereal/cereal.hpp"
#include "Cereal/types/string.hpp"
#include "Cereal/types/common.hpp"
#include "Cereal/access.hpp"
#include "../Core/NativeType.h"

#include "RawAssetConverterFactory.h"
#include "ModelAssetConverterFactory.h"
#include "AssetInfo.h"

struct Setting
{
  Setting() = default;

  static Setting* Create();

  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::make_nvp("UniqueIdTablePath", this->unique_id_table_path));
    ar(cereal::make_nvp("RawAssetConverter", this->raw_asset_converter_factory));
    ar(cereal::make_nvp("ModelAssetConverter", this->model_asset_converter_factory));
  }

  std::string unique_id_table_path;

  RawAssetConverterFactory raw_asset_converter_factory;
  ModelAssetConverterFactory model_asset_converter_factory;

};
CEREAL_CLASS_VERSION(Setting, 1);
CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(RawAssetConverterFactory, cereal::specialization::member_serialize)
