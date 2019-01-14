#pragma once

#include <Entity/File/FileAssetConverter.h>
#include "TextureAssetImporter.h"

class TextureAssetConverter : public FileAssetConverter<rcTexture, TextureData>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureAssetConverter(const std::string& id, const std::string& class_name, const std::vector<std::string>& extensions, T_UINT32 skip_head, T_UINT32 skip_tail)
    : FileAssetConverter(id, new TextureAssetImporter({extensions}), class_name, skip_head, skip_tail)
  {}
};
