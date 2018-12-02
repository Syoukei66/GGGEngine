#pragma once

#if GG_GRAPHICS_API_DX11

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

  virtual bool ImGuiNewFrame() override;

protected:
  virtual bool PreDraw() override;
  virtual bool PostDraw() override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE ID3D11Device* GetDevice() const
  {
    return this->device_;
  }
  GG_INLINE ID3D11DeviceContext* GetImmediateContext() const
  {
    return this->immediate_context_;
  }

private:
  ID3D11Device* device_;
  ID3D11DeviceContext* immediate_context_;
  IDXGISwapChain* swap_chain_;
  ID3D11RenderTargetView* render_target_view_;
  D3D_DRIVER_TYPE driver_type_;
  D3D_FEATURE_LEVEL feature_level_;

};

#endif