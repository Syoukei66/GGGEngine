#include "NativeIndexBuffer.h"
#include "NativeObjectFactory.h"

INativeIndexBuffer* INativeIndexBuffer::Create(T_UINT16 vertex_count)
{
  return NativeObjectFactory::CreateIndexBuffer(vertex_count);
}
