#include "..\..\NativeObjectFactory.h"

#include "NativeIndexBuffer.h"
#include "NativeVertexBuffer.h"
#include "NativeTexture.h"
#include "NativeRenderTexture.h"
#include "NativeShader.h"
#include "NativeSound.h"

INativeVertexBuffer* NativeObjectFactory::CreateVertexBuffer(T_UINT16 vertex_count, T_UINT16 polygon_count, T_UINT32 format)
{
  return new NativeVertexBuffer(vertex_count, polygon_count, format);
}

INativeIndexBuffer* NativeObjectFactory::CreateIndexBuffer(T_UINT32 indexes_count)
{
  return new NativeIndexBuffer(indexes_count);
}

INativeTexture* NativeObjectFactory::CreateTexture(const char* path)
{
  return new NativeTexture(path);
}

INativeRenderTexture* NativeObjectFactory::CreateRenderTexture(T_UINT16 width, T_UINT16 height, INativeRenderTexture::Format format)
{
  return new NativeRenderTexture(width, height, format);
}

INativeSound* NativeObjectFactory::CreateSound(const char* path)
{
  return new NativeSound(path);
}

INativeShader* NativeObjectFactory::CreateShader(const char* path)
{
  return new NativeShader(path);
}
