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
  }

  T_UINT32 unique_id;
  std::string time_stamp;
  std::unordered_set<std::string> references;
};
CEREAL_CLASS_VERSION(AssetMetaData, 2);