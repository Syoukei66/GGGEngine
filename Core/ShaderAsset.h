#pragma once

#include "Asset.h"
#include "Shader.h"

class ShaderAsset : public Asset<ShaderAsset, rcShader>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  ShaderAsset(const std::string& path)
    : Asset(path)
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