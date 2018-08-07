#pragma once

#include <string>

#include "NativeType.h"
#include "RenderBuffer.h"

#include "NativeSound.h"
#include "NativeShader.h"
#include "NativeVertexBuffer.h"
#include "NativeIndexBuffer.h"

namespace NativeProcess
{

namespace Time
{
#ifdef _DEBUG
void FPS_Init();
void FPS_PreUpdate();
void FPS_PostUpdate();
T_FLOAT FPS_GetValue();
#endif
} // namespace Time

namespace IO
{
const std::string TextFile_Read(const char* path);
void TextFile_Write(const char* path, const std::string& str);
} // namespace IO

namespace Graphics
{
void ViewportClear();
void SetViewport(T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h, T_FLOAT minZ, T_FLOAT maxZ);
void PackColor4u8(T_PACKED_COLOR_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a);
void SetRenderTarget(RenderBuffer* color_buffer, RenderBuffer* depth_buffer, bool clear);
void ResetRenderTarget();
} // namespace Graphics

namespace Resource
{
void* TextureLoad(const std::string& path);
void* CreateTexture(T_UINT16 width, T_UINT16 height, ::Graphics::TextureFormat format);
void DeleteTexture(void* native_obj);
void GetTextureSize(const std::string& path, T_UINT16* width_dest, T_UINT16* height_dest);
void GetTextureSize(void* native_obj, T_UINT16* width_dest, T_UINT16* height_dest);

void* CreateColorBuffer(Texture* texture);
void* CreateDepthBuffer(T_UINT16 width, T_UINT16 height, ::Graphics::TextureFormat format);
void DeleteRenderBuffer(void* native_obj);
} // namespace Resource

namespace Factory
{
INativeVertexBuffer* CreateVertexBuffer(T_UINT16 vertex_count, T_UINT16 polygon_count, T_UINT32 format);
INativeIndexBuffer* CreateIndexBuffer(T_UINT32 indexes_count);
INativeSound* CreateSound(const char* path);
INativeShader* CreateShader(const char* path);
} // namespace Factory

} // namespace NativeProcess
