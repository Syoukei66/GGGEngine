#pragma once

class rcRenderBuffer;
class rcTexture;
class rcRenderTexture;
class rcShader;
class rcSound;
class rcVertexBuffer;
class rcIndexBuffer;

/*!
 * @brief ネイティブ側に処理を移譲
 * プラットフォーム毎に実装しなくてはいけない
 */
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
void PackColor4u8(T_FIXED_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a);
void SetRenderTarget(const SharedRef<rcRenderBuffer>& color_buffer, const SharedRef<rcRenderBuffer>& depth_stencil_buffer, bool clear);
void ResetRenderTarget();
} // namespace Graphics

namespace Resource
{
UniqueRef<rcTexture> TextureLoad(const char* path);
void DeleteTexture(rcTexture* texture);
void GetTextureSize(const rcTexture* texture, T_UINT16* width_dest, T_UINT16* height_dest);

UniqueRef<rcRenderBuffer> CreateColorBuffer(const SharedRef<const rcTexture>& texture);
UniqueRef<rcRenderBuffer> CreateDepthStencilBuffer(T_UINT16 width, T_UINT16 height, ::Graphics::PixelFormat format);
void DeleteRenderBuffer(rcRenderBuffer* render_buffer);

UniqueRef<rcRenderTexture> CreateRenderTexture(T_UINT16 width, T_UINT16 height, ::Graphics::PixelFormat format, ::Graphics::PixelFormat depth_format);

UniqueRef<rcShader> ShaderLoad(const char* path);
UniqueRef<rcSound> SoundLoad(const char* path);
UniqueRef<rcVertexBuffer> CreateVertexBuffer(T_UINT32 vertex_count, T_UINT32 format);
UniqueRef<rcIndexBuffer> CreateIndexBuffer(T_UINT32 indexes_count, T_UINT32 polygon_count);
} // namespace GGAssetObject

} // namespace NativeProcess
