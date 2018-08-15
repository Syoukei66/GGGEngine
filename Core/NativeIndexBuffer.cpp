#include "NativeIndexBuffer.h"
#include "NativeProcess.h"

INativeIndexBuffer* INativeIndexBuffer::Create(T_UINT32 vertex_count)
{
  return NativeProcess::Factory::CreateIndexBuffer(vertex_count);
}
