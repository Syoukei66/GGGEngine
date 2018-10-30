#include "IndexBuffer.h"
#include <Core/Native/NativeProcess.h>

// =================================================================
// Factory Method
// =================================================================
UniqueRef<rcIndexBuffer> rcIndexBuffer::Create(T_UINT32 vertex_count, T_UINT32 polygon_count)
{
  return NativeProcess::Resource::CreateIndexBuffer(vertex_count, polygon_count);
}
