#pragma once
#include <string>
#include <unordered_set>
#include "../Core/NativeType.h"

#include "Cereal\cereal.hpp"
#include "Cereal\archives\json.hpp"
#include "Cereal\types\string.hpp"
#include "Cereal\types\unordered_set.hpp"
#include "Cereal\types\utility.hpp"

//=============================================================================
// ConverterProperty
//=============================================================================
//CEREAL_REGISTER_TYPE(T)ÇégÇ¡Çƒîhê∂ÉNÉâÉXÇìoò^
//https://qiita.com/Egliss/items/cc281f724ebe7d05ff67
struct ConverterProperty
{
  ConverterProperty() = default;

  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
  }
};
CEREAL_CLASS_VERSION(ConverterProperty, 1);

//=============================================================================
// Asset
//=============================================================================
struct AssetMetaData
{
  AssetMetaData() = default;

  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(CEREAL_NVP(unique_id));
    ar(CEREAL_NVP(time_stamp));
    ar(CEREAL_NVP(references));
    //ar(CEREAL_NVP(properties));
  }

  T_UINT32 unique_id;
  std::string time_stamp;
  std::unordered_set<std::string> references;
  //std::unordered_map<T_UINT32, std::shared_ptr<ConverterProperty>> properties;
};
CEREAL_CLASS_VERSION(AssetMetaData, 2);