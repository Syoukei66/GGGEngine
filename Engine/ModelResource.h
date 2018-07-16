#pragma once

#include <string>
#include "FileResource.h"
#include "ModelData.h"

class ModelResource : public FileResource<ModelData>
{
public:
  static ModelResource* DynamicLoad(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelResource(const char* path);

  // =================================================================
  // Methods
  // =================================================================
  virtual ModelData* NativeLoadProcess(const std::string& path) override;
 
};