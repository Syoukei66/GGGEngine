#include "IndexBuffer.h"

// =================================================================
// Factory Method
// =================================================================
UniqueRef<rcIndexBuffer> rcIndexBuffer::Create(T_UINT32 vertex_count, T_UINT32 polygon_count)
{
  return Application::GetPlatform()->GetGraphicsAPI()->CreateIndexBuffer(vertex_count, polygon_count);
}
