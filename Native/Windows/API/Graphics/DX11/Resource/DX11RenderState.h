#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>
#include <Core/Application/Platform/API/_Resource/RenderState.h>

class DX11RenderState : public rcRenderState
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(DX11RenderState);
  GG_CREATE_FUNC_1(DX11RenderState, const RenderStateData&, data);
  GG_DESTRUCT_FUNC(DX11RenderState);

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

#endif
