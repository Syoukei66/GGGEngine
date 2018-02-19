#pragma once

#include "NativeModel.h"
#include "FileResource.h"

class ModelData : public FileResource<INativeModel>
{
public:
  static ModelData* DynamicLoad(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelData(const char* path);

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual INativeModel* NativeLoadProcess(const std::string& path) override;

};
