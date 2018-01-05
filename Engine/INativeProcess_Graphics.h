#ifndef HAL_ENGINE_NATIVE_NATIVEPROCESS_GRAPHICS_H_
#define HAL_ENGINE_NATIVE_NATIVEPROCESS_GRAPHICS_H_

#include "NativeType.h"
#include "GameObjectRenderState.h"
#include "Vertex.h"
#include "Material.h"
#include "ITexture.h"

#include "NativeTexture.h"
#include "NativeMatrix.h"

class INativeProcess_Graphics
{
public:
  enum PrimitiveType
  {
    PRIMITIVE_POINTS,
    PRIMITIVE_LINES,
    PRIMITIVE_LINESTRIP,
    PRIMITIVE_TRIANGLES,
    PRIMITIVE_TRIANGLESTRIP,
    PRIMITIVE_TRIANGLEFAN,

    PRIMITIVE_DATANUM,
  };

  enum VertexType
  {
    VERTEX_TYPE_COORD_COLOR,
    VERTEX_TYPE_COORD_COLOR_UV,
    VERTEX_TYPE_COORD_COLOR_UV_NORMAL,

    VERTEX_TYPE_DATANUM,
  };

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Graphics_Cheat(T_UINT16 cheat_id) = 0;

  virtual void Graphics_Clear() = 0;

  virtual void Graphics_SetTransformView(NativeMatrixInstance* mat) = 0;
  virtual void Graphics_SetTransformProjection(NativeMatrixInstance* mat) = 0;
  virtual void Graphics_SetTransformWorld(NativeMatrixInstance* mat) = 0;

  virtual void Graphics_SetViewport(T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h, T_FLOAT minZ, T_FLOAT maxZ) = 0;

  virtual void Graphics_SetBlendMode(BlendFunction::BlendMode src, BlendFunction::BlendMode dst) = 0;

  virtual void Graphics_SetTexture(const ITexture* texture) = 0;
  virtual void Graphics_SetMaterial(const Material* material) = 0;
  virtual void Graphics_SetLightingEnabled(bool enabled) = 0;

  virtual void Graphics_PackColor4u8(T_PACKED_COLOR_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a) = 0;

  virtual void Graphics_DrawPrimitive(GameObjectRenderState* state, PrimitiveType type, const Vertex* vertexes, T_UINT16 vertexes_count) = 0;
  virtual void Graphics_DrawIndexedPrimitive(GameObjectRenderState* state, PrimitiveType type, const Vertex* vertexes, T_UINT16 vertexes_count, const T_UINT16* indexes) = 0;

  virtual void Graphics_DrawSprite(GameObjectRenderState* state, PrimitiveType type, const SpriteVertex* vertexes, T_UINT16 vertexes_count) = 0;
  virtual void Graphics_DrawIndexedSprite(GameObjectRenderState* state, PrimitiveType type, const SpriteVertex* vertexes, T_UINT16 vertexes_count, const T_UINT16* indexes) = 0;

  virtual void Graphics_DrawVertexes(GameObjectRenderState* state, PrimitiveType primitive_type, VertexType vertex_type, const void* vertexes, T_UINT16 vertexes_count) = 0;
  virtual void Graphics_DrawIndexedVertexes(GameObjectRenderState* state, PrimitiveType primitive_type, VertexType vertex_type, const void* vertexes, T_UINT16 vertexes_count, const T_UINT16* indexes) = 0;

  virtual T_UINT16 Graphics_CreateLight(LP_LIGHT* light) = 0;
  virtual void Graphics_DeleteLight(T_UINT16 light_id, LP_LIGHT light) = 0;
  virtual void Graphics_SetLight(T_UINT16 light_id, LP_LIGHT light) = 0;

  virtual void Graphics_SetLightEnable(T_UINT16 light_id, LP_LIGHT light, bool enable) = 0;
  virtual void Graphics_SetLightDirection(T_UINT16 light_id, LP_LIGHT light, const TVec3f& direction) = 0;
  
  virtual void Graphics_SetLightDiffuse(T_UINT16 light_id, LP_LIGHT light, const Color& color) = 0;
  virtual void Graphics_SetAmbient(const Color& color) = 0;
  //virtual LP_VERTEX_BUFFER Graphics_CreateVertexBuffer(T_UINT32 size, VertexBufferMode mode) = 0;
  //virtual void Graphics_DeleteVertexBuffer(LP_VERTEX_BUFFER vb) = 0;
  //virtual void Graphics_LockVertexBuffer(LP_VERTEX_BUFFER vb, void** ppb_data) = 0;
  //virtual void Graphics_DrawVertexBuffer(LP_VERTEX_BUFFER vb) = 0;
};

#endif//HAL_ENGINE_NATIVE_NATIVEPROCESS_GRAPHICS_H_
