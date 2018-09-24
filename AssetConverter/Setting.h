#pragma once

#include <string>

#include "Cereal\cereal.hpp"
#include "Cereal\types\string.hpp"
#include "Cereal\types\common.hpp"

#include "../Core/NativeType.h"

#include "RawAssetConverterFactory.h"
#include "AssetInfo.h"

struct Setting
{
  Setting() = default;

  static Setting* Create();

  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::make_nvp("EngineName", this->engine_name));
    ar(cereal::make_nvp("InputPath", this->input_path));
    ar(cereal::make_nvp("OutputPath", this->output_path));
    ar(cereal::make_nvp("ProjectPath", this->project_path));
    ar(cereal::make_nvp("UniqueIdTablePath", this->unique_id_table_path));
    ar(cereal::make_nvp("RawAssetConverter", this->raw_asset_converter_factory));
  }

  std::string engine_name;
  std::string input_path;
  std::string output_path;
  std::string project_path;
  std::string unique_id_table_path;

  RawAssetConverterFactory raw_asset_converter_factory;

};
CEREAL_CLASS_VERSION(Setting, 1);