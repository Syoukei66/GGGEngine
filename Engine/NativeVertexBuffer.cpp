#include "NativeVertexBuffer.h"
#include "NativeObjectFactory.h"

INativeVertexBuffer* INativeVertexBuffer::Create(T_UINT16 vertex_count, INativeProcess_Graphics::VertexType vertex_type)
{
  return NativeObjectFactory::CreateVertexBuffer(vertex_count, vertex_type);
}
