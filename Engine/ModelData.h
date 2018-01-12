#pragma once

#include <string>
#include "NativeModel.h"
#include "FileResource.h"

class ModelData : public FileResource<INativeModel>
{
public:
  static const ModelData* DynamicLoad(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelData(const char* path);

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual INativeModel* NativeLoadProcess(const std::string & path) override;

};
