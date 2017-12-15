#define _CRT_SECURE_NO_WARNINGS
#include "TexturePaletteManager.h"
#include "NativeMethod.h"
#include "Director.h"

// =================================================================
// Constructor / Destructor
// =================================================================
TexturePaletteManager::TexturePaletteManager()
  : ResourcePool("TexturePalette")
  , paths_()
  , dynamic_texture_palette_(new TexturePalette())
{}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
ITexturePalette* TexturePaletteManager::PreLoadProcess(const T_UINT8& key)
{
  ITexturePalette* ret = NativeMethod::Texture().TexturePalette_Create(this->paths_[key].c_str());
  return ret;
}

ITexturePalette* TexturePaletteManager::LoadProcess(const T_UINT8& key, ITexturePalette* value)
{
  NativeMethod::Texture().TexturePalette_Load(value);
  return value;
}

void TexturePaletteManager::PreUnloadProcess(const T_UINT8& key, ITexturePalette* value)
{
}

void TexturePaletteManager::UnloadProcess(const T_UINT8& key, ITexturePalette* value)
{
  NativeMethod::Texture().TexturePalette_Unload(value);
  delete value;
}

// =================================================================
// Methods
// =================================================================
void TexturePaletteManager::RegisterPath(T_UINT8 id, const char* path)
{
  this->paths_[id] = path;
}

const Texture* TexturePaletteManager::DynamicLoad(const char* path)
{
  if (!this->dynamic_texture_palette_)
  {
    this->dynamic_texture_palette_ = new TexturePalette();
  }
  Texture* tex = this->dynamic_texture_palette_->GetTextureByPath(path);
  if (tex)
  {
    return tex;
  }
  T_UINT8 id = this->dynamic_texture_palette_->LoadImmediately(path);
  return (Texture*)this->dynamic_texture_palette_->GetTexture(id);
}

void TexturePaletteManager::DynamicUnload(const char* path)
{
  if (!this->dynamic_texture_palette_)
  {
    return;
  }
  Texture* native_texture = this->dynamic_texture_palette_->GetTextureByPath(path);
  native_texture->Unload();
  this->dynamic_texture_palette_->UnregisterPath(path);
}

const Texture* TexturePaletteManager::GetDynamicTexture(const char* path) const
{
  return this->dynamic_texture_palette_->GetTextureByPath(path);
}