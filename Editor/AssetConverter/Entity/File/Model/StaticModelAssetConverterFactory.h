#pragma once

#include <Entity/File/FileAssetConverterFactory.h>

class StaticModelAssetConverterFactory : public FileAssetConverterFactory
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  StaticModelAssetConverterFactory() = default;

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
CEREAL_CLASS_VERSION(StaticModelAssetConverterFactory, 1);