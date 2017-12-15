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

LP_TEXTURE NativeProcess_Texture::Texture_Load(const char* path) const
{
  LP_DEVICE device = Director::GetInstance()->GetDevice();
  LP_TEXTURE dest = NULL;
  HRESULT hr = D3DXCreateTextureFromFile(
    (LPDIRECT3DDEVICE9)device,
    path,
    (LPDIRECT3DTEXTURE9*)&dest);

  if (FAILED(hr))
  {
    MessageBox(NULL, "�e�N�X�`���̃��[�h�Ɏ��s���܂���", "���m�点", MB_OK);
  }
  return dest;
}

void NativeProcess_Texture::Texture_Unload(LP_TEXTURE texture) const
{
  LPDIRECT3DTEXTURE9 tex = (LPDIRECT3DTEXTURE9)texture;
  if (tex)
  {
    tex->Release();
  }
}

void NativeProcess_Texture::Texture_SetToDevice(LP_TEXTURE texture) const
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
  device->SetTexture(0, (LPDIRECT3DTEXTURE9)texture);
}

void NativeProcess_Texture::Texture_GetSize(LP_TEXTURE texture, TSize* size) const
{
  D3DSURFACE_DESC desc;
  LPDIRECT3DTEXTURE9 tex = (LPDIRECT3DTEXTURE9)texture;
  tex->GetLevelDesc(0, &desc);
  size->width = desc.Width;
  size->height = desc.Height;
}
