#pragma once

#include "AssetConverterFactory.h"

class ModelMaterialAssetConverterFactory : public AssetConverterFactory
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelMaterialAssetConverterFactory() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  IAssetConverter* Create() const override;

  // =================================================================
  // Serializer
  // =================================================================
public:

  // =================================================================
  // Data Members
  // =================================================================
private:

};
