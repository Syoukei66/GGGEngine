#ifndef HAL_DIRECTX_ACTIVITY_NATIVE_NATIVEPROCESS_TEXTURE_H_
#define HAL_DIRECTX_ACTIVITY_NATIVE_NATIVEPROCESS_TEXTURE_H_

#include "../../Engine/INativeProcess_Texture.h"

class NativeProcess_Texture : public INativeProcess_Texture
{
public:
  virtual ITexturePalette* TexturePalette_Create(const char* path) const override;
  virtual void TexturePalette_Load(ITexturePalette* path) const override;
  virtual void TexturePalette_Unload(ITexturePalette* palette) const override;

};

#endif//HAL_DIRECTX_ACTIVITY_NATIVE_NATIVEPROCESS_TEXTURE_H_