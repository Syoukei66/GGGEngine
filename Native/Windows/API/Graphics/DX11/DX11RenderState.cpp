#include "DX11RenderState.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/WindowsApplication.h>
#include <Native/Windows/API/Graphics/DX11/DX11Constants.h>

// =================================================================
// Constructor / Destructor
// =================================================================
DX11RenderState::DX11RenderState(const RenderStateData& data)
{
  using namespace Shader;
  using namespace DX11;

  // ラスタライザステート
  const SharedRef<GraphicsAPI>& api = Application::GetPlatform()->GetGraphicsAPI();
  ID3D11Device* device = WindowsApplication::GetDX11Graphics()->GetDevice();
  D3D11_RASTERIZER_DESC rs_desc = D3D11_RASTERIZER_DESC();
  rs_desc.FillMode = D3D11_FILL_SOLID;
  rs_desc.CullMode = CULL_MODES[data.cull_mode_];
  rs_desc.FrontCounterClockwise = FALSE;
  rs_desc.DepthBias = 0;
  rs_desc.DepthBiasClamp = 0;
  rs_desc.SlopeScaledDepthBias = 0;
  rs_desc.DepthClipEnable = FALSE;
  rs_desc.ScissorEnable = FALSE;
  rs_desc.MultisampleEnable = FALSE;
  rs_desc.AntialiasedLineEnable = FALSE;
  HRESULT hr = device->CreateRasterizerState(&rs_desc, &this->rasterizer_state_);
  GG_ASSERT(SUCCEEDED(hr), "ラスタライザステートの作成に失敗しました");

  // ブレンドステート
  D3D11_BLEND_DESC blend_desc = D3D11_BLEND_DESC();
  blend_desc.AlphaToCoverageEnable = FALSE;
  blend_desc.IndependentBlendEnable = FALSE;
  const T_UINT8 render_target_count = (T_UINT8)data.blend_state_datas_.size();
  for (T_UINT8 i = 0; i < 8; ++i)
  {
    blend_desc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    // 設定されていないレンダーターゲットではブレンド無効
    if (i >= render_target_count)
    {
      blend_desc.RenderTarget[i].BlendEnable = FALSE;
      continue;
    }
    const BlendStateData& bs_data = data.blend_state_datas_[i];
    blend_desc.RenderTarget[i].BlendEnable = TRUE;

    blend_desc.RenderTarget[i].SrcBlend = BLEND_FACTORS[bs_data.blend_color_src_factor_];
    blend_desc.RenderTarget[i].DestBlend = BLEND_FACTORS[bs_data.blend_color_dst_factor_];
    blend_desc.RenderTarget[i].BlendOp = BLEND_OPERATIONS[bs_data.blend_color_op_];

    blend_desc.RenderTarget[i].SrcBlendAlpha = BLEND_FACTORS[bs_data.blend_alpha_src_factor_];
    blend_desc.RenderTarget[i].DestBlendAlpha = BLEND_FACTORS[bs_data.blend_alpha_dst_factor_];
    blend_desc.RenderTarget[i].BlendOpAlpha = BLEND_OPERATIONS[bs_data.blend_alpha_op_];
  }
  hr = device->CreateBlendState(&blend_desc, &this->blend_state_);
  GG_ASSERT(SUCCEEDED(hr), "ブレンドステートの作成に失敗しました");
  
  // デプス・ステンシルステート
  D3D11_DEPTH_STENCIL_DESC ds_desc = D3D11_DEPTH_STENCIL_DESC();
  ds_desc.DepthEnable = TRUE;
  ds_desc.DepthWriteMask = Z_WRITES[data.z_write_];
  ds_desc.DepthFunc = COMPARASION_FUNCS[data.z_test_];

  if (data.stencil_state_data_)
  {
    this->stencil_ref_ = data.stencil_state_data_->stencil_ref_;

    ds_desc.StencilReadMask = data.stencil_state_data_->stencil_read_mask_;
    ds_desc.StencilWriteMask = data.stencil_state_data_->stencil_write_mask_;
    ds_desc.StencilEnable = TRUE;

    ds_desc.FrontFace.StencilFunc = COMPARASION_FUNCS[data.stencil_state_data_->stencil_comp_front_];
    ds_desc.FrontFace.StencilPassOp = STENCIL_OPERATIONS[data.stencil_state_data_->stencil_pass_front_];
    ds_desc.FrontFace.StencilFailOp = STENCIL_OPERATIONS[data.stencil_state_data_->stencil_fail_front_];
    ds_desc.FrontFace.StencilDepthFailOp = STENCIL_OPERATIONS[data.stencil_state_data_->stencil_zfail_front_];

    ds_desc.BackFace.StencilFunc = COMPARASION_FUNCS[data.stencil_state_data_->stencil_comp_back_];
    ds_desc.BackFace.StencilPassOp = STENCIL_OPERATIONS[data.stencil_state_data_->stencil_pass_back_];
    ds_desc.BackFace.StencilFailOp = STENCIL_OPERATIONS[data.stencil_state_data_->stencil_fail_back_];
    ds_desc.BackFace.StencilDepthFailOp = STENCIL_OPERATIONS[data.stencil_state_data_->stencil_zfail_back_];
  }
  else
  {
    this->stencil_ref_ = 0;
    ds_desc.StencilEnable = FALSE;
  }

  hr = device->CreateDepthStencilState(&ds_desc, &this->depth_stencil_state_);
  GG_ASSERT(SUCCEEDED(hr), "デプス・ステンシルステートの作成に失敗しました");

}

DX11RenderState::~DX11RenderState()
{
  this->depth_stencil_state_->Release();
  this->blend_state_->Release();
  this->rasterizer_state_->Release();
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
void DX11RenderState::SetState() const
{
  ID3D11DeviceContext* context = WindowsApplication::GetDX11Graphics()->GetImmediateContext();
  context->RSSetState(this->rasterizer_state_);
  static const FLOAT blend_factor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  context->OMSetBlendState(this->blend_state_, blend_factor, 0xffffffff);
  //context->OMSetDepthStencilState(this->depth_stencil_state_, this->stencil_ref_);
}

#endif
