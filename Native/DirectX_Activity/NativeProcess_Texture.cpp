#define _CRT_SECURE_NO_WARNINGS
#include "NativeProcess_Texture.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include <iostream>
#include <string>
#include "../../Engine/Texture.h"
#include "../../Engine/CSVTokenizer.h"
#include "../../Engine/Director.h"
#include "../../Engine/TexturePalette.h"

ITexturePalette* NativeProcess_Texture::TexturePalette_Create(const char* path) const
{
  LP_DEVICE device = Director::GetInstance()->GetDevice();
  char file_path[256] = {};
  Director::GetInstance()->GetEngineOption()->asset_path.GetTexturePath(path, file_path);
  strcat(file_path, ".palette");
  std::ifstream ifs(file_path);
  if (ifs.fail())
  {
    return nullptr;
  }
  char str[256] = {};
  TexturePalette* palette = new TexturePalette();
  T_UINT32 line_index = 0;
  while (ifs.getline(str, 256 - 1))
  {
    CSVTokenizer tokenizer;
    tokenizer.Prepare(line_index, str);
    tokenizer.NextToken();
    const char* path = tokenizer.NextToken()->GetString();
    char texture_path[256] = {};
    Director::GetInstance()->GetEngineOption()->asset_path.GetTexturePath(path, texture_path);

    palette->RegisterPath(path);
    line_index++;
  }
  return palette;
}

void NativeProcess_Texture::TexturePalette_Load(ITexturePalette* ipalette) const
{
  TexturePalette* palette = (TexturePalette*)ipalette;
  palette->Load();
}

void NativeProcess_Texture::TexturePalette_Unload(ITexturePalette* ipalette) const
{
  TexturePalette* palette = (TexturePalette*)ipalette;
  palette->Unload();
}
