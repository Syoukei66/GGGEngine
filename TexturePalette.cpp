#include "TexturePalette.h"
#include "NativeMethod.h"
#include "Director.h"

// =================================================================
// Constructor / Destructor
// =================================================================
TexturePalette::TexturePalette()
{}

TexturePalette::~TexturePalette()
{
  for (std::map<T_UINT8, ITexture*>::iterator itr = this->textures_.begin(); itr != this->textures_.end();)
  {
    Texture* texture = (Texture*)itr->second;
    texture->Unload();
    delete texture;
    itr = this->textures_.erase(itr);
  }
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
T_UINT8 TexturePalette::RegisterPath(const char* path)
{
  T_UINT8 id = (T_UINT8)this->textures_.size();
  char full_path[256] = { '\0' };
  Director::GetInstance()->GetEngineOption()->asset_path.GetTexturePath(path, full_path);
  this->textures_[id] = new Texture(full_path);
  return id;
}

void TexturePalette::UnregisterPath(const char* path)
{
  char full_path[256] = { '\0' };
  Director::GetInstance()->GetEngineOption()->asset_path.GetTexturePath(path, full_path);
  for (std::map<T_UINT8, ITexture*>::iterator itr = this->textures_.begin(); itr != this->textures_.end(); ++itr)
  {
    Texture* texture = (Texture*)itr->second;
    if (texture->GetPath().compare(full_path))
    {
      continue;
    }
    texture->Unload();
    delete texture;
    this->textures_.erase(itr);
    return;
  }
}

// =================================================================
// Methods
// =================================================================
T_UINT8 TexturePalette::LoadImmediately(const char* path)
{
  Texture* texture = new Texture(path);
  texture->Load();

  T_UINT8 id = (T_UINT8)this->textures_.size();
  this->textures_[id] = texture;
  return id;
}

void TexturePalette::Load()
{
  for (std::map<T_UINT8, ITexture*>::iterator itr = this->textures_.begin(); itr != this->textures_.end(); ++itr)
  {
    Texture* texture = (Texture*)itr->second;
    texture->Load();
  }
}

void TexturePalette::Unload()
{
  for (std::map<T_UINT8, ITexture*>::iterator itr = this->textures_.begin(); itr != this->textures_.end(); ++itr)
  {
    Texture* texture = (Texture*)itr->second;
    texture->Unload();
  }
}

// =================================================================
// Setter / Getter
// =================================================================
Texture* TexturePalette::GetTextureByPath(const char* path)
{
  for (std::map<T_UINT8, ITexture*>::iterator itr = this->textures_.begin(); itr != this->textures_.end(); ++itr)
  {
    Texture* texture = (Texture*)itr->second;
    if (texture->GetPath().compare(path))
    {
      continue;
    }
    return texture;
  }
  return nullptr;
}

