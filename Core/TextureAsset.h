#pragma once

#include "Asset.h"
#include "Texture.h"

class TextureAsset : public BaseAsset<TextureAsset, rcTexture>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  TextureAsset(const std::string& path)
    : BaseAsset(path)
  {}

  // =================================================================
  // Methods
  // =================================================================
protected:
  rcTexture* LoadProcess(const std::string& path) override
  {
    return rcTexture::CreateFromFile(path.c_str());
  }

};