#pragma once

#include <string>
#include "../Asset/StaticModelData.h"
#include "FileResource.h"
#include "StaticModelResource.h"

class StaticModelAsset : public FileResource<StaticModelResource>
{
public:
  static StaticModelAsset* DynamicLoad(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  StaticModelAsset(const char* path);

  // =================================================================
  // Methods
  // =================================================================
  virtual StaticModelResource* NativeLoadProcess(const std::string& path) override;
 
};