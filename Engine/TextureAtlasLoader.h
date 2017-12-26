#pragma once

#include <string>
#include "TextureAtlas.h"

class TextureAtlasLoader
{
public:
  TextureAtlas* Load(const char* directory_path, const char* atlas_file_name);

protected:
  const std::string GetText(char** p);
  const std::string GetDataText(char** p);
  const std::string TexturePath(char** p);
  const TSize TextureSize(char** p);
  const std::string TextureFormat(char** p);
  const std::string TextureFilter(char** p);
  const std::string TextureRepeat(char** p);

  const TSize StrToTSize(const std::string& str);
  const TVec2 StrToTVec2(const std::string& str);

private:
  
};
