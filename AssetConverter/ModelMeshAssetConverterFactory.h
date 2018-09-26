#pragma once

#include "AssetConverterFactory.h"

class ModelMeshAssetConverterFactory : public AssetConverterFactory
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelMeshAssetConverterFactory() = default;

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