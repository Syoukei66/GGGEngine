#ifndef HAL_DIRECTX_ACTIVITY_NATIVE_NATIVEPROCESS_GRAPHICS_H_
#define HAL_DIRECTX_ACTIVITY_NATIVE_NATIVEPROCESS_GRAPHICS_H_

#include "../../Engine/INativeProcess_Graphics.h"
#include <d3d9.h>

class NativeProcess_Graphics : public INativeProcess_Graphics
{
  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Graphics_Cheat(T_UINT16 cheat_id) override;

  virtual void Graphics_SetTransformView(LP_MATRIX_4x4 mat) override;
  virtual void Graphics_SetTransformProjection(LP_MATRIX_4x4 mat) override;
  virtual void Graphics_SetTransformWorld(LP_MATRIX_4x4 mat) override;

  virtual void Graphics_SetViewport(T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h, T_FLOAT minZ, T_FLOAT maxZ);

  virtual void Graphics_SetBlendMode(BlendFunction::BlendMode src, BlendFunction::BlendMode dst) override;

  virtual void Graphics_SetTexture(const ITexture* texture) override;
  virtual void Graphics_SetMaterial(const Material* material) override;
  virtual void Graphics_SetLightingEnabled(bool enabled) override;

  virtual void Graphics_PackColor4u8(T_PACKED_COLOR_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a) override;

  virtual void Graphics_DrawPrimitive(GameObjectRenderState* state, PrimitiveType type, const Vertex* vertexes, T_UINT16 vertexes_count) override;
  virtual void Graphics_DrawIndexedPrimitive(GameObjectRenderState* state, PrimitiveType type, const Vertex* vertexes, T_UINT16 vertexes_count, const T_UINT16* indexes) override;

  virtual void Graphics_DrawSprite(GameObjectRenderState* state, PrimitiveType type, const SpriteVertex* vertexes, T_UINT16 vertexes_count) override;
  virtual void Graphics_DrawIndexedSprite(GameObjectRenderState* state, PrimitiveType type, const SpriteVertex* vertexes, T_UINT16 vertexes_count, const T_UINT16* indexes) override;

  virtual void Graphics_DrawVertexes(GameObjectRenderState* state, PrimitiveType primitive_type, VertexType vertex_type, const void* vertexes, T_UINT16 vertexes_count) override;
  virtual void Graphics_DrawIndexedVertexes(GameObjectRenderState* state, PrimitiveType primitive_type, VertexType vertex_type, const void* vertexes, T_UINT16 vertexes_count, const T_UINT16* indexes) override;

  virtual T_UINT16 Graphics_CreateLight(LP_LIGHT* light) override;
  virtual void Graphics_DeleteLight(T_UINT16 light_id, LP_LIGHT light) override;
  virtual void Graphics_SetLight(T_UINT16 light_id, LP_LIGHT light) override;

  virtual void Graphics_SetLightEnable(T_UINT16 light_id, LP_LIGHT light, bool enable) override;
  virtual void Graphics_SetLightDirection(T_UINT16 light_id, LP_LIGHT light, const TVec3f& direction) override;

  virtual void Graphics_SetLightDiffuse(T_UINT16 light_id, LP_LIGHT light, const Color& color) override;
  virtual void Graphics_SetAmbient(const Color& color) override;

  // =================================================================
  // DataMembers
  // =================================================================
private:
  LPDIRECT3DTEXTURE9 texture_;
  const D3DMATERIAL9* material_;
  
};

#endif//HAL_DIRECTX_ACTIVITY_NATIVE_NATIVEPROCESS_GRAPHICS_H_