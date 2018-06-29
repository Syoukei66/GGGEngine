#ifndef HAL_ENGINE_NATIVE_NATIVEPROCESS_GRAPHICS_H_
#define HAL_ENGINE_NATIVE_NATIVEPROCESS_GRAPHICS_H_

#include "NativeType.h"
#include "GameObjectRenderState.h"
#include "Material.h"

#include "NativeTexture.h"
#include "NativeRenderTexture.h"

class INativeProcess_Graphics
{
  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Graphics_Cheat(T_UINT16 cheat_id) = 0;

  virtual void Graphics_Clear() = 0;

  virtual void Graphics_SetViewport(T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h, T_FLOAT minZ, T_FLOAT maxZ) = 0;

  virtual void Graphics_PackColor4u8(T_PACKED_COLOR_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a) = 0;

  virtual void Blit(INativeTexture* source, INativeRenderTexture* dest) = 0;
  virtual void Blit(INativeTexture* source, INativeRenderTexture* dest, Material* mat, T_UINT8 pass = -1) = 0;
  virtual void Blit(INativeTexture* source, Material* mat, T_UINT8 pass = -1) = 0;

};

#endif//HAL_ENGINE_NATIVE_NATIVEPROCESS_GRAPHICS_H_
