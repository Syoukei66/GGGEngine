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

LP_NATIVE_INSTANCE NativeProcess_Texture::Texture_Load(const char* path) const
{
  LP_DEVICE device = Director::GetInstance()->GetDevice();
  LPDIRECT3DTEXTURE9 dest = nullptr;
  HRESULT hr = D3DXCreateTextureFromFile(
    (LPDIRECT3DDEVICE9)device,
    path,
    &dest);

  if (FAILED(hr))
  {
    MessageBox(NULL, "テクスチャのロードに失敗しました", "お知らせ", MB_OK);
  }
  return (LP_NATIVE_INSTANCE)dest;
}

void NativeProcess_Texture::Texture_Unload(LP_NATIVE_INSTANCE texture) const
{
  LPDIRECT3DTEXTURE9 tex = (LPDIRECT3DTEXTURE9)texture;
  if (tex)
  {
    tex->Release();
  }
}

void NativeProcess_Texture::Texture_GetSize(LP_NATIVE_INSTANCE texture, TSize* size) const
{
  D3DSURFACE_DESC desc;
  LPDIRECT3DTEXTURE9 tex = (LPDIRECT3DTEXTURE9)texture;
  tex->GetLevelDesc(0, &desc);
  size->width = desc.Width;
  size->height = desc.Height;
}
