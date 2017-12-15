#pragma once

#include "ITexturePalette.h"
#include "StaticTexture.h"

//Wii�Ȃǂ̂悤��Texture�P�̂̓ǂݍ��݂��ł��Ȃ����p
//TexturePalette���番��
class StaticTexturePalette : public ITexturePalette
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  StaticTexturePalette();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  inline T_UINT8 RegisterPath(const char* path) override
  {
    T_UINT8 id = this->paths_.size();
    this->paths_[id] = path;
    return id;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  const ITexture* GetTexture(const char* path)
  {
    for (std::map<T_UINT8, std::string>::iterator itr = this->paths_.begin(); itr != this->paths_.end(); ++itr)
    {
      if (itr->second.compare(path))
      {
        continue;
      }
      return this->textures_[itr->first];
    }
    return nullptr;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  std::map<T_UINT8, std::string> paths_;
};