#ifndef HAL_DIRECTX_ACTIVITY_NATIVE_NATIVEPROCESS_GRAPHICS_H_
#define HAL_DIRECTX_ACTIVITY_NATIVE_NATIVEPROCESS_GRAPHICS_H_

#include <INativeProcess_Graphics.h>
#include <d3d9.h>

class NativeProcess_Graphics : public INativeProcess_Graphics
{
  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Graphics_Cheat(T_UINT16 cheat_id) override;

  virtual void Graphics_Clear() override;

  virtual void Graphics_SetViewport(T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h, T_FLOAT minZ, T_FLOAT maxZ) override;

  virtual void Graphics_PackColor4u8(T_PACKED_COLOR_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a) override;

  virtual void SetRenderTarget(RenderBuffer* color_buffer, RenderBuffer* depth_buffer, bool clear) override;
  virtual void ResetRenderTarget() override;

};

#endif//HAL_DIRECTX_ACTIVITY_NATIVE_NATIVEPROCESS_GRAPHICS_H_