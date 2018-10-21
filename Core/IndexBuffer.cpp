#include "IndexBuffer.h"
#include "NativeProcess.h"

// =================================================================
// Factory Method
// =================================================================
UniqueResource<rcIndexBuffer> rcIndexBuffer::Create(T_UINT32 vertex_count, T_UINT32 polygon_count)
{
  UniqueResource<rcIndexBuffer> ret = NativeProcess::Resource::CreateIndexBuffer(vertex_count, polygon_count);
  ret->Resource::Init();
  return ret;
}
