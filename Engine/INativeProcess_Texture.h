#ifndef HAL_ENGINE_NATIVE_NATIVEPROCESS_TEXTURE_H_
#define HAL_ENGINE_NATIVE_NATIVEPROCESS_TEXTURE_H_

#include "NativeType.h"
#include "Geometry.h"
#include "ITexturePalette.h"

class INativeProcess_Texture
{
  // =================================================================
  // Method
  // =================================================================
public:
  virtual ITexturePalette* TexturePalette_Create(const char* path) const = 0;
  virtual void TexturePalette_Load(ITexturePalette* ipalette) const = 0;
  virtual void TexturePalette_Unload(ITexturePalette* ipalette) const = 0;

};

#endif//HAL_ENGINE_NATIVE_NATIVEPROCESS_TEXTURE_H_
