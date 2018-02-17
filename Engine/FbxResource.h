#pragma once

#include "FbxData.h"
#include "FileResource.h"

class FbxResource : public FileResource<FbxData>
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static FbxResource* DynamicLoad(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  FbxResource(const char* path);

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual FbxData* NativeLoadProcess(const std::string& path) override;

};