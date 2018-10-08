#pragma once

#include <Cereal/cereal.hpp>

#include "AssetConverterFactory.h"

class DefaultMeshAssetConverterFactory : public AssetConverterFactory
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DefaultMeshAssetConverterFactory() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  IAssetConverter* Create() const override;

  // =================================================================
  // Serializer
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
  }

  // =================================================================
  // Data Members
  // =================================================================
private:

};
CEREAL_CLASS_VERSION(DefaultMeshAssetConverterFactory, 1);
