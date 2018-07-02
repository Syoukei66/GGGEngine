#include "NativeIndexBuffer.h"
#include "NativeProcess.h"

INativeIndexBuffer* INativeIndexBuffer::Create(T_UINT16 vertex_count)
{
  return NativeProcess::Factory::CreateIndexBuffer(vertex_count);
}
