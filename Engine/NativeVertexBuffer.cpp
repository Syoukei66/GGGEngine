#include "NativeVertexBuffer.h"
#include "NativeProcess.h"

INativeVertexBuffer* INativeVertexBuffer::Create(T_UINT16 vertex_count, T_UINT16 polygon_count, T_UINT32 format)
{
  return NativeProcess::Factory::CreateVertexBuffer(vertex_count, polygon_count, format);
}
