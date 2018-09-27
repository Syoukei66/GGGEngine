#pragma once

#include <vector>
#include <string>

#include "AssetConverterFactory.h"

#include "Cereal/types/polymorphic.hpp"
#include "Cereal/types/base_class.hpp"
#include "Cereal/types/vector.hpp"
#include "Cereal/types/string.hpp"

class FileAssetConverterFactory : public AssetConverterFactory
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  FileAssetConverterFactory() = default;

  // =================================================================
  // Serializer
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::make_nvp("TargetExtensions", this->target_extensions_));
  }

  // =================================================================
  // Data Members
  // =================================================================
protected:
  std::vector<std::string> target_extensions_;

};
CEREAL_CLASS_VERSION(FileAssetConverterFactory, 1);