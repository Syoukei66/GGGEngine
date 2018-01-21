#include "NativeVertexBuffer.h"
#include "NativeObjectFactory.h"

INativeVertexBuffer* INativeVertexBuffer::Create(T_UINT16 vertex_count, Vertex::VertexType vertex_type)
{
  return NativeObjectFactory::CreateVertexBuffer(vertex_count, vertex_type);
}
