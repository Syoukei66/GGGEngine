#include "VertexBuffer.h"
#include "NativeProcess.h"

// =================================================================
// Factory Method
// =================================================================
UniqueResource<rcVertexBuffer> rcVertexBuffer::Create(T_UINT32 vertex_count, T_UINT32 format)
{
  UniqueResource<rcVertexBuffer> ret = NativeProcess::Resource::CreateVertexBuffer(vertex_count, format);
  ret->Resource::Init();
  return ret;
}
