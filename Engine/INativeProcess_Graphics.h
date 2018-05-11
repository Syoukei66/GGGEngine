#ifndef HAL_ENGINE_NATIVE_NATIVEPROCESS_GRAPHICS_H_
#define HAL_ENGINE_NATIVE_NATIVEPROCESS_GRAPHICS_H_

#include "NativeType.h"
#include "GameObjectRenderState.h"
#include "Vertex.h"
#include "Material.h"

#include "NativeTexture.h"
#include "NativeRenderTexture.h"
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

  static int PRIMITIVE_SURF_NUM(INativeProcess_Graphics::PrimitiveType type, int num)
  {
    if (type == PRIMITIVE_POINTS)
    {
      return num;
    }
    if (type == PRIMITIVE_LINES)
    {
      return num;
    }
    if (type == PRIMITIVE_LINESTRIP)
    {
      return num;
    }
    if (type == PRIMITIVE_TRIANGLES)
    {
      return num / 3;
    }
    if (type == PRIMITIVE_TRIANGLESTRIP)
    {
      return num - 2;
    }
    if (type == PRIMITIVE_TRIANGLEFAN)
    {
      return num - 2;
    }
    return num;
  }

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Graphics_Cheat(T_UINT16 cheat_id) = 0;

  virtual void Graphics_Clear() = 0;

  virtual void Graphics_SetViewport(T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h, T_FLOAT minZ, T_FLOAT maxZ) = 0;

  virtual void Graphics_PackColor4u8(T_PACKED_COLOR_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a) = 0;

  virtual void Graphics_DrawPrimitive(GameObjectRenderState* state, PrimitiveType type, const Vertex::VC* vertexes, T_UINT16 vertexes_count) = 0;
  virtual void Graphics_DrawIndexedPrimitive(GameObjectRenderState* state, PrimitiveType type, const Vertex::VC* vertexes, T_UINT16 vertexes_count, const T_UINT16* indexes) = 0;

  virtual void Graphics_DrawSprite(GameObjectRenderState* state, PrimitiveType type, const Vertex::VCT* vertexes, T_UINT16 vertexes_count) = 0;
  virtual void Graphics_DrawIndexedSprite(GameObjectRenderState* state, PrimitiveType type, const Vertex::VCT* vertexes, T_UINT16 vertexes_count, const T_UINT16* indexes) = 0;

  virtual void Graphics_DrawVertexes(GameObjectRenderState* state, PrimitiveType primitive_type, Vertex::VertexType vertex_type, const void* vertexes, T_UINT16 vertexes_count) = 0;
  virtual void Graphics_DrawIndexedVertexes(GameObjectRenderState* state, PrimitiveType primitive_type, Vertex::VertexType vertex_type, const void* vertexes, T_UINT16 vertexes_count, const T_UINT16* indexes) = 0;

  virtual void Blit(INativeTexture* source, INativeRenderTexture* dest) = 0;
  virtual void Blit(INativeTexture* source, INativeRenderTexture* dest, Material* mat, T_UINT8 pass = -1) = 0;
  virtual void Blit(INativeTexture* source, Material* mat, T_UINT8 pass = -1) = 0;

};

#endif//HAL_ENGINE_NATIVE_NATIVEPROCESS_GRAPHICS_H_
