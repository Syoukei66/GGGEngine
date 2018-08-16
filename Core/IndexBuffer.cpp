#include "IndexBuffer.h"
#include "NativeProcess.h"

// =================================================================
// Constructor / Destructor
// =================================================================
rcIndexBuffer* rcIndexBuffer::Create(T_UINT32 vertex_count)
{
  rcIndexBuffer* ret = NativeProcess::Resource::CreateIndexBuffer(vertex_count);
  ret->Resource::Init();
  return ret;
}
