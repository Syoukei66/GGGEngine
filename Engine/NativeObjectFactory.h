#pragma once

#include "NativeSound.h"
#include "NativeShader.h"
#include "NativeVertexBuffer.h"
#include "NativeIndexBuffer.h"

namespace NativeObjectFactory
{

INativeVertexBuffer* CreateVertexBuffer(T_UINT16 vertex_count, T_UINT16 polygon_count, T_UINT32 vertex_size);
INativeIndexBuffer* CreateIndexBuffer(T_UINT32 indexes_count);

INativeSound* CreateSound(const char* path);

INativeShader* CreateShader(const char* path);

};