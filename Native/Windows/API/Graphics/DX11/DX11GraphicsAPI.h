#pragma once

#include <d3d11.h>

class DX11GraphicsAPI : public GraphicsAPI
{
public:
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(DX11GraphicsAPI);
  GG_CREATE_FUNC(DX11GraphicsAPI);
  GG_DESTRUCT_FUNC(DX11GraphicsAPI);

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void ViewportClear(const TColor& color) override;
  virtual void SetViewport(T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h, T_FLOAT minZ, T_FLOAT maxZ) override;
  virtual void PackColor4u8(T_FIXED_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a) override;
  virtual void UnpackColor4u8(T_FIXED_UINT32 color, T_UINT8* r, T_UINT8* g, T_UINT8* b, T_UINT8* a) override;
  virtual void SetRenderTarget(const SharedRef<rcRenderBuffer>& color_buffer, const SharedRef<rcRenderBuffer>& depth_stencil_buffer, bool clear) override;
  virtual void ResetRenderTarget() override;
  virtual void DrawStencilBuffer() override;

  virtual void DrawIndexedPrimitive(Vertex::PrimitiveType primitive_type, const SharedRef<const rcIndexBuffer>& index_buffer) override;

  virtual UniqueRef<rcTexture> TextureLoad(const char* path) override;
  virtual void DeleteTexture(rcTexture* texture) override;
  virtual void GetTextureSize(const rcTexture* texture, T_UINT16* width_dest, T_UINT16 * height_dest) override;
  virtual UniqueRef<rcRenderBuffer> CreateColorBuffer(const SharedRef<const rcTexture>& texture) override;
  virtual UniqueRef<rcRenderBuffer> CreateDepthStencilBuffer(T_UINT16 width, T_UINT16 height, ::Graphics::PixelFormat format) override;
  virtual void DeleteRenderBuffer(rcRenderBuffer* render_buffer) override;
  virtual UniqueRef<rcRenderTexture> CreateRenderTexture(T_UINT16 width, T_UINT16 height, ::Graphics::PixelFormat format, ::Graphics::PixelFormat depth_format) override;
  virtual UniqueRef<rcShader> ShaderLoad(const char* path) override;
  virtual UniqueRef<rcVertexBuffer> CreateVertexBuffer(T_UINT32 size) override;
  virtual UniqueRef<rcIndexBuffer> CreateIndexBuffer(T_UINT32 vertex_count, T_UINT32 polygon_count, Vertex::IndexFormat format) override;
  virtual UniqueRef<rcVertexDeclaration> CreateVertexDeclaration(T_UINT32 format) override;

  virtual bool ImGuiNewFrame() override;
  virtual bool ImGuiEndFrame() override;

protected:
  virtual bool PreDraw() override;
  virtual bool PostDraw() override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE LPDIRECT3DDEVICE9 GetDevice() const
  {
    return this->d3d_device_;
  }

private:
  LPDIRECT3D9 d3d_;
  LPDIRECT3DDEVICE9 d3d_device_;

};