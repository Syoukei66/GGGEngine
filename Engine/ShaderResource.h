#pragma once

#include "../Common/NativeShader.h"
#include "FileResource.h"

class ShaderAsset : public FileResource<INativeShader>
{
public:
  static ShaderAsset* DynamicLoad(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ShaderAsset(const char* path);

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual INativeShader* NativeLoadProcess(const std::string& path) override;

};