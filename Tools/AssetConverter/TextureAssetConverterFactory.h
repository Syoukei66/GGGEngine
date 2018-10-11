#pragma once

#include "FileAssetConverterFactory.h"

class TextureAssetConverterFactory : public FileAssetConverterFactory
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureAssetConverterFactory() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  IAssetConverter* Create(AssetConverterContext* context) const override;

  // =================================================================
  // Serializer
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::make_nvp("base", cereal::base_class<FileAssetConverterFactory>(this)));
  }

  // =================================================================
  // Data Members
  // =================================================================
private:

};
CEREAL_CLASS_VERSION(TextureAssetConverterFactory, 1);