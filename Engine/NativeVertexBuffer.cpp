#include "NativeVertexBuffer.h"
#include "NativeObjectFactory.h"

INativeVertexBuffer* INativeVertexBuffer::Create(T_UINT16 vertex_count, T_UINT16 polygon_count, T_UINT32 format)
{
  return NativeObjectFactory::CreateVertexBuffer(vertex_count, polygon_count, format);
}
