#pragma once

#include "NativeTexture.h"
#include "NativeRenderTexture.h"
#include "NativeSound.h"
#include "NativeMatrixStack.h"
#include "NativeModel.h"
#include "NativeShader.h"
#include "NativeVertexBuffer.h"
#include "NativeIndexBuffer.h"

namespace NativeObjectFactory
{

INativeMatrixStack* CreateMatrixStack();

INativeVertexBuffer* CreateVertexBuffer(T_UINT16 vertex_count, T_UINT16 polygon_count, T_UINT32 vertex_size);
INativeIndexBuffer* CreateIndexBuffer(T_UINT32 indexes_count);

INativeTexture* CreateTexture(const char* path);
INativeRenderTexture* CreateRenderTexture(T_UINT16 width, T_UINT16 height, INativeRenderTexture::Format format);

INativeSound* CreateSound(const char* path);

INativeModel* CreateModel(const char* directory_path, const char* name, const char* extension);

INativeShader* CreateShader(const char* path);

};