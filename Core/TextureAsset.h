#pragma once

#include "Asset.h"
#include "Texture.h"

class TextureAsset : public Asset<TextureAsset, rcTexture>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  TextureAsset(const std::string& path)
    : Asset(path)
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