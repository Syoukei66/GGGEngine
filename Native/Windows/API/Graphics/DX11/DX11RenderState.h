#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>
#include <Core/Application/Platform/API/_Resource/RenderState/RenderState.h>

class DX11RenderState : public rcRenderState
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DX11RenderState(const RenderStateData& data);
  ~DX11RenderState();

  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void SetState() const override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  ID3D11RasterizerState* rasterizer_state_;
  ID3D11BlendState* blend_state_;
  ID3D11DepthStencilState* depth_stencil_state_;

  T_UINT8 stencil_ref_;

};

UniqueRef<rcRenderState> rcRenderState::Create(const RenderStateData& data)
{
  return UniqueRef<rcRenderState>(new DX11RenderState(data));
}

#endif
