#pragma once

#if GG_GRAPHICS_API_DX11

#include <dxgiformat.h>
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
  virtual void ViewportClear(const SharedRef<Activity>& activity, const TColor& color) override;
  virtual void SetViewport(T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h, T_FLOAT minZ, T_FLOAT maxZ) override;
  virtual void PackColor4u8(T_FIXED_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a) override;
  virtual void UnpackColor4u8(T_FIXED_UINT32 color, T_UINT8* r, T_UINT8* g, T_UINT8* b, T_UINT8* a) override;
  //virtual void SetRenderTarget(const SharedRef<rcRenderBuffer>& color_buffer, const SharedRef<rcRenderBuffer>& depth_stencil_buffer, bool clear) override;
  virtual void SetRenderTarget(const SharedRef<Activity>& activity) override;
  virtual void ResetRenderTarget() override;

  virtual void DrawIndexedPrimitive(Vertex::PrimitiveType primitive_type, const SharedRef<const rcIndexBuffer>& index_buffer) override;

  virtual bool ImGuiNewFrame() override;

  virtual void CreateSubActivityResources(const SharedRef<Activity>& activity) override;

protected:
  void CreateRenderTargets(const SharedRef<Activity>& activity);

  virtual bool PreDraw(const SharedRef<Activity>& activity) override;
  virtual bool PostDraw(const SharedRef<Activity>& activity) override;

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
  
  IDXGIDevice1* dxgi_;
  IDXGIAdapter* adapter_;
  IDXGIFactory* factory_;

  DXGI_SWAP_CHAIN_DESC swap_chain_desc_;
  
  std::unordered_map<HWND, IDXGISwapChain*> swap_chains_;
  std::unordered_map<HWND, ID3D11RenderTargetView*> render_target_views_;
  std::unordered_map<HWND, ID3D11DepthStencilView*> depth_stencil_views_;

  D3D_DRIVER_TYPE driver_type_;
  D3D_FEATURE_LEVEL feature_level_;

};

#endif