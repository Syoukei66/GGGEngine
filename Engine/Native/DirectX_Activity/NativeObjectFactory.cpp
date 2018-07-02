#include "..\..\NativeObjectFactory.h"

#include "NativeIndexBuffer.h"
#include "NativeVertexBuffer.h"
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

INativeSound* NativeObjectFactory::CreateSound(const char* path)
{
  return new NativeSound(path);
}

INativeShader* NativeObjectFactory::CreateShader(const char* path)
{
  return new NativeShader(path);
}
