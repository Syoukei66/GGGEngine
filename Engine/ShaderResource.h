#pragma once

#include "NativeShader.h"
#include "FileResource.h"

class ShaderResource : public FileResource<INativeShader>
{
public:
  static ShaderResource* DynamicLoad(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ShaderResource(const char* path);

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual INativeShader* NativeLoadProcess(const std::string& path) override;

};