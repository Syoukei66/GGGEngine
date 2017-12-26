#pragma once

#include <string>
#include <map>

#include "ITexture.h"

class ITexturePalette
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ITexturePalette()
    : textures_()
  {}
  virtual ~ITexturePalette() {}

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual T_UINT8 RegisterPath(const char* path) = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline T_UINT32 GetSize()
  {
    return (T_UINT32)this->textures_.size();
  }
  inline ITexture* GetTexture(T_UINT8 id)
  {
    return this->textures_[id];
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  std::map<T_UINT8, ITexture*> textures_;

};
