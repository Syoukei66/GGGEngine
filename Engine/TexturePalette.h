#ifndef HAL_ENGINE_RESOURCE_TEXTUREMANAGER_H_
#define HAL_ENGINE_RESOURCE_TEXTUREMANAGER_H_

#include "ITexturePalette.h"
#include "Texture.h"

class TexturePalette : public ITexturePalette
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TexturePalette();
  ~TexturePalette();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  T_UINT8 RegisterPath(const char* path) override;

  // =================================================================
  // Methods
  // =================================================================
public:
  T_UINT8 LoadImmediately(const char* path);
  void UnregisterPath(const char* path);

  void Load();
  void Unload();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  Texture* GetTextureByPath(const char* path);

};

#endif//HAL_ENGINE_RESOURCE_TEXTUREMANAGER_H_
