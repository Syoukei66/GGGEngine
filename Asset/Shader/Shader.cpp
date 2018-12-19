#include "Shader.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(rcShader, const ShaderData& data)
{
  using namespace Shader;
  this->name_ = data.name_;
  switch (static_cast<RenderQueue>(data.queue_))
  {
  case RenderQueue::kBackGround:
    this->queue_ = Graphics::RenderQueue::RQ_BACKGROUND;
    break;
  case RenderQueue::kGeometry:
    this->queue_ = Graphics::RenderQueue::RQ_GEOMETRY;
    break;
  case RenderQueue::kAlphaTest:
    this->queue_ = Graphics::RenderQueue::RQ_ALPHA_TEST;
    break;
  case RenderQueue::kTransparent:
    this->queue_ = Graphics::RenderQueue::RQ_TRANSPARENT;
    break;
  case RenderQueue::kOverlay:
    this->queue_ = Graphics::RenderQueue::RQ_OVERLAY;
    break;
  }
  this->render_type_ = static_cast<RenderType>(data.queue_);
  this->scala_properties_ = data.scala_properties_;
  this->vector_properties_ = data.vector_properties_;
  this->color_properties_ = data.color_properties_;
  this->sampler_properties_ = data.sampler_properties_;
  for (const PassData& pass_data : data.passes_)
  {
    Pass* pass = &this->passes_[pass_data.light_mode_];
    pass->grab_ = pass_data.grab_;
    pass->light_mode_ = pass_data.light_mode_;
    pass->render_state = rcRenderState::Create(pass_data.render_state_data_);
    pass->vertex_shader = rcVertexShader::Create(pass_data.vs_byte_code_);
    pass->pixel_shader = rcPixelShader::Create(pass_data.ps_byte_code_);
  }

  return true;
}

// =================================================================
// Method 
// =================================================================
bool rcShader::BeginPass(T_UINT8 path_id, const SharedRef<const rcVertexDeclaration>& declaration) const
{
  const auto& pair = this->passes_.find(path_id);
  if (pair == this->passes_.end())
  {
    return false;
  }
  const Pass& pass = pair->second;
  pass.render_state->SetState();
  pass.vertex_shader->SetInputLayout(declaration);
  pass.vertex_shader->SetShader();
  pass.pixel_shader->SetShader();
  return true;
}