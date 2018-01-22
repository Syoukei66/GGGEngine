#include "NativeVertexBuffer.h"
#include "NativeObjectFactory.h"

INativeVertexBuffer* INativeVertexBuffer::Create(T_UINT16 vertex_count, T_UINT16 polygon_count, Vertex::VertexType vertex_type)
{
  return NativeObjectFactory::CreateVertexBuffer(vertex_count, polygon_count, vertex_type);
}
