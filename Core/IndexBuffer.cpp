#include "IndexBuffer.h"
#include "NativeProcess.h"

// =================================================================
// Factory Method
// =================================================================
UniqueResource<rcIndexBuffer> rcIndexBuffer::Create(T_UINT32 vertex_count)
{
  UniqueResource<rcIndexBuffer> ret = NativeProcess::Resource::CreateIndexBuffer(vertex_count);
  ret->Resource::Init();
  return ret;
}
