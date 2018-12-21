#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

/*!
 * @brief ブレンドステートデータ
 */
struct BlendStateData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(BlendStateData)
  {
    archive(blend_color_src_factor_);
    archive(blend_color_dst_factor_);
    archive(blend_color_op_);
    archive(blend_alpha_src_factor_);
    archive(blend_alpha_dst_factor_);
    archive(blend_alpha_op_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  BlendStateData()
    : blend_color_src_factor_(static_cast<T_FIXED_UINT8>(Shader::BlendFactor::kOne))
    , blend_color_dst_factor_(static_cast<T_FIXED_UINT8>(Shader::BlendFactor::kZero))
    , blend_color_op_(static_cast<T_FIXED_UINT8>(Shader::BlendOp::kAdd))
    , blend_alpha_src_factor_(static_cast<T_FIXED_UINT8>(Shader::BlendFactor::kOne))
    , blend_alpha_dst_factor_(static_cast<T_FIXED_UINT8>(Shader::BlendFactor::kZero))
    , blend_alpha_op_(static_cast<T_FIXED_UINT8>(Shader::BlendOp::kAdd))
  {}

  // =================================================================
  // Data Members
  // =================================================================
public:
  T_FIXED_UINT8 blend_color_src_factor_; // BlendFactor
  T_FIXED_UINT8 blend_color_dst_factor_; // BlendFactor
  T_FIXED_UINT8 blend_color_op_;         // BlendOp
  T_FIXED_UINT8 blend_alpha_src_factor_; // BlendFactor
  T_FIXED_UINT8 blend_alpha_dst_factor_; // BlendFactor
  T_FIXED_UINT8 blend_alpha_op_;         // BlendOp
};

/*!
 * @brief ステンシルステートデータ
 */
struct StencilStateData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(StencilStateData)
  {
    archive(stencil_ref_);
    archive(stencil_read_mask_);
    archive(stencil_write_mask_);
    archive(stencil_comp_front_);
    archive(stencil_pass_front_);
    archive(stencil_fail_front_);
    archive(stencil_zfail_front_);
    archive(stencil_comp_back_);
    archive(stencil_pass_back_);
    archive(stencil_fail_back_);
    archive(stencil_zfail_back_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  StencilStateData()
    : stencil_ref_(0xff)
    , stencil_read_mask_(0xff)
    , stencil_write_mask_(0xff)
    , stencil_comp_front_(static_cast<T_FIXED_UINT8>(Shader::ComparasionFunc::kAlways))
    , stencil_pass_front_(static_cast<T_FIXED_UINT8>(Shader::StencilOperation::kKeep))
    , stencil_fail_front_(static_cast<T_FIXED_UINT8>(Shader::StencilOperation::kKeep))
    , stencil_zfail_front_(static_cast<T_FIXED_UINT8>(Shader::StencilOperation::kKeep))
    , stencil_comp_back_(static_cast<T_FIXED_UINT8>(Shader::ComparasionFunc::kAlways))
    , stencil_pass_back_(static_cast<T_FIXED_UINT8>(Shader::StencilOperation::kKeep))
    , stencil_fail_back_(static_cast<T_FIXED_UINT8>(Shader::StencilOperation::kKeep))
    , stencil_zfail_back_(static_cast<T_FIXED_UINT8>(Shader::StencilOperation::kKeep))
  {}

  // =================================================================
  // Data Members
  // =================================================================
public:
  T_FIXED_UINT8 stencil_ref_;        // 0~255
  T_FIXED_UINT8 stencil_read_mask_;  // 0~255
  T_FIXED_UINT8 stencil_write_mask_; // 0~255

  T_FIXED_UINT8 stencil_comp_front_;  // ComparasionFunc
  T_FIXED_UINT8 stencil_pass_front_;  // StencilOperation
  T_FIXED_UINT8 stencil_fail_front_;  // StencilOperation
  T_FIXED_UINT8 stencil_zfail_front_; // StencilOperation

  T_FIXED_UINT8 stencil_comp_back_;  // ComparasionFunc
  T_FIXED_UINT8 stencil_pass_back_;  // StencilOperation
  T_FIXED_UINT8 stencil_fail_back_;  // StencilOperation
  T_FIXED_UINT8 stencil_zfail_back_; // StencilOperation
};

/*!
 * @brief レンダーステートデータ
 * ラスタライザステート、ブレンドステート、デプス・ステンシルステート等がまとまったデータ
 */
struct RenderStateData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(RenderStateData)
  {
    archive(cull_mode_);
    archive(z_write_);
    archive(z_test_);
    archive(blend_state_datas_);
    archive(stencil_state_data_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  RenderStateData()
    : cull_mode_(static_cast<T_FIXED_UINT8>(Shader::CullMode::kBack))
    , z_write_(static_cast<T_FIXED_UINT8>(Shader::ZWrite::kOn))
    , z_test_(static_cast<T_FIXED_UINT8>(Shader::ComparasionFunc::kLEqual))
    , blend_state_datas_()
    , stencil_state_data_()
  {}

  RenderStateData(const RenderStateData& o)
    : cull_mode_(o.cull_mode_)
    , z_write_(o.z_write_)
    , z_test_(o.z_test_)
    , blend_state_datas_(o.blend_state_datas_)
    , stencil_state_data_(o.stencil_state_data_ ? new StencilStateData(*o.stencil_state_data_) : nullptr)
  {}

  // =================================================================
  // Data Members
  // =================================================================
public:
  T_FIXED_UINT8 cull_mode_; // CullMode
  T_FIXED_UINT8 z_write_;   // ZWrite
  T_FIXED_UINT8 z_test_;    // ComparasionFunc

  std::vector<BlendStateData> blend_state_datas_;
  std::unique_ptr<StencilStateData> stencil_state_data_;
};

/*!
 * @brief レンダーステートの基底クラス
 * プラットフォーム毎の処理を派生クラス側で定義する
 */
class rcRenderState : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcRenderState);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcRenderState> Create(const RenderStateData& data);

  // =================================================================
  // Method 
  // =================================================================
public:
  virtual void SetState() const = 0;

};