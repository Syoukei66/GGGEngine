#pragma once

#include "Asset.h"
#include "Shader.h"

class ShaderAsset : public BaseAsset<ShaderAsset, rcShader>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  ShaderAsset(const std::string& path)
    : BaseAsset(path)
  {}

  // =================================================================
  // Methods
  // =================================================================
protected:
  rcShader* LoadProcess(const std::string& path) override
  {
    return rcShader::CreateFromFile(path.c_str());
  }

};