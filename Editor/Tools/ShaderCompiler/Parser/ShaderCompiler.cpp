#include "ShaderCompiler.h"
#include "ShaderToken.h"

ShaderCompiler::ShaderCompiler(const std::string& str, const std::string& directory_path)
  : parser_(str)
  , compiler_(directory_path)
{
}

void ShaderCompiler::Compile(ShaderData* dest)
{
  bool grab = false;
  while (this->parser_.CheckNextToken() != TokenType::kEOF)
  {
    const std::string token = this->parser_.ParseIdentifier();
    if (token == "Properties")
    {
      this->CompileProperties(dest);
      continue;
    }
    if (token == "Shader")
    {
      this->CompileName(dest);
      continue;
    }
    if (token == "Tags")
    {
      this->CompileTags(dest);
      continue;
    }
    if (token == "Pass")
    {
      this->CompilePass(&this->compiler_, dest, grab);
      grab = false;
      continue;
    }
    if (token == "GrabPass")
    {
      this->CompileGrabPass(dest);
      grab = true;
      continue;
    }
  }
}

void ShaderCompiler::CompileName(ShaderData* dest)
{
  dest->name_ = this->parser_.ParseText();
}

void ShaderCompiler::CompileProperty(ShaderData* dest)
{
  const std::string property_id = this->parser_.ParseIdentifier();
  this->parser_.GetToken(TokenType::kParenBegin);
  const std::string property_name = this->parser_.ParseText();
  this->parser_.GetToken(TokenType::kComma);
  const std::string property_type = this->parser_.ParseSpecialIdentifier();
  using namespace GGGShaderParser;
  if (property_type == "Range")
  {
    ScalaPropertyData data;
    this->parser_.GetToken(TokenType::kParenBegin);
    data.min_value_ = this->parser_.ParseFloat();
    this->parser_.GetToken(TokenType::kComma);
    data.max_value_ = this->parser_.ParseFloat();
    this->parser_.GetToken(TokenType::kParenEnd);
    this->parser_.GetToken(TokenType::kParenEnd);
    this->parser_.GetToken(TokenType::kEqual);
    data.init_value_ = this->parser_.ParseFloat();
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.variable_type_ = static_cast<T_FIXED_UINT8>(Shader::VariableType::kFloat);
    dest->scala_properties_.emplace_back(data);
    return;
  }
  if (property_type == "Float")
  {
    ScalaPropertyData data;
    this->parser_.GetToken(TokenType::kParenEnd);
    this->parser_.GetToken(TokenType::kEqual);
    data.init_value_ = this->parser_.ParseFloat();
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.variable_type_ = static_cast<T_FIXED_UINT8>(Shader::VariableType::kFloat);
    data.min_value_ = Limit::T_FLOAT_MIN;
    data.max_value_ = Limit::T_FLOAT_MAX;
    dest->scala_properties_.emplace_back(data);
    return;
  }
  if (property_type == "Int")
  {
    ScalaPropertyData data;
    this->parser_.GetToken(TokenType::kParenEnd);
    this->parser_.GetToken(TokenType::kEqual);
    data.init_value_ = this->parser_.ParseInt();
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.variable_type_ = static_cast<T_FIXED_UINT8>(Shader::VariableType::kInt);
    data.min_value_ = (T_FLOAT)Limit::T_INT32_MIN;
    data.max_value_ = (T_FLOAT)Limit::T_INT32_MAX;
    dest->scala_properties_.emplace_back(data);
    return;
  }
  if (property_type == "Vector")
  {
    VectorPropertyData data;
    this->parser_.GetToken(TokenType::kParenEnd);
    this->parser_.GetToken(TokenType::kEqual);
    this->parser_.GetToken(TokenType::kBlockBegin);
    // {}の場合はすべて0、　数値が入ってた場合は数値を読み取る
    if (this->parser_.CheckNextToken() != TokenType::kBlockEnd)
    {
      data.init_value0_ = this->parser_.ParseFloat();
      this->parser_.GetToken  (TokenType::kComma);
      data.init_value1_ = this->parser_.ParseFloat();
      this->parser_.GetToken  (TokenType::kComma);
      data.init_value2_ = this->parser_.ParseFloat();
      this->parser_.GetToken  (TokenType::kComma);
      data.init_value3_ = this->parser_.ParseFloat();
      this->parser_.GetToken  (TokenType::kBlockEnd);
    }
    else
    {
      this->parser_.EatToken();
    }
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.variable_type_ = static_cast<T_FIXED_UINT8>(Shader::VariableType::kFloat);
    dest->vector_properties_.emplace_back(data);
    return;
  }
  if (property_type == "Color")
  {
    ColorPropertyData data;
    this->parser_.GetToken(TokenType::kParenEnd);
    this->parser_.GetToken(TokenType::kEqual);
    this->parser_.GetToken(TokenType::kBlockBegin);
    // {}の場合はすべて1、　数値が入ってた場合は数値を読み取る
    if (this->parser_.CheckNextToken() != TokenType::kBlockEnd)
    {
      data.init_r_ = this->parser_.ParseFloat();
      this->parser_.GetToken(TokenType::kComma);
      data.init_g_ = this->parser_.ParseFloat();
      this->parser_.GetToken(TokenType::kComma);
      data.init_b_ = this->parser_.ParseFloat();
      this->parser_.GetToken(TokenType::kComma);
      data.init_a_ = this->parser_.ParseFloat();
      this->parser_.GetToken(TokenType::kBlockEnd);
    }
    else
    {
      this->parser_.EatToken();
    }
    data.name_ = property_id;
    data.display_name_ = property_name;
    dest->color_properties_.emplace_back(data);
    return;
  }
  if (property_type == "2D")
  {
    this->parser_.GetToken(TokenType::kParenEnd);
    this->parser_.GetToken(TokenType::kEqual);
    const std::string init_tex = this->parser_.ParseText();
    SamplerPropertyData data;
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.sampler_type_ = static_cast<T_FIXED_UINT8>(Shader::SamplerType::kSampler2D);
    data.default_texture_ = this->parser_.ParseDefaultTextureType(init_tex);
    dest->sampler_properties_.emplace_back(data);
    return;
  }
  this->parser_.ThrowIdentifierError("Property Type指定", property_type);
}

void ShaderCompiler::CompileProperties(ShaderData* dest)
{
  this->parser_.GetToken(TokenType::kBlockBegin);
  while (this->parser_.CheckNextToken() != TokenType::kBlockEnd)
  {
    this->CompileProperty(dest);
  }
  this->parser_.GetToken(TokenType::kBlockEnd);
}

void ShaderCompiler::CompileTag(ShaderData* dest)
{
  const std::string tag_type = this->parser_.ParseIdentifier();
  using namespace GGGShaderParser;
  if (tag_type == "Queue")
  {
    dest->queue_ = this->parser_.ParseRenderQueue();
    return;
  }
  if (tag_type == "RenderType")
  {
    dest->render_type_ = this->parser_.ParseRenderType();
    return;
  }
  this->parser_.ThrowIdentifierError("Tagトークン", tag_type);
}

void ShaderCompiler::CompileTags(ShaderData* dest)
{
  this->parser_.GetToken(TokenType::kBlockBegin);
  while (this->parser_.CheckNextToken() != TokenType::kBlockEnd)
  {
    this->CompileTag(dest);
  }
  this->parser_.EatToken();
}

void ShaderCompiler::CompileStencilData(StencilStateData * dest)
{
  using namespace GGGShaderParser;
  const std::string tag = this->parser_.ParseIdentifier();
  if (tag == "Ref")
  {
    dest->stencil_ref_ = (T_FIXED_UINT8)this->parser_.ParseInt();
    return;
  }
  if (tag == "ReadMask")
  {
    dest->stencil_read_mask_ = this->parser_.ParseInt();
    return;
  }
  if (tag == "WriteMask")
  {
    dest->stencil_write_mask_ = this->parser_.ParseInt();
    return;
  }
  if (tag == "Comp")
  {
    dest->stencil_comp_front_ = dest->stencil_comp_back_ = this->parser_.ParseComparasionFunc();
    return;
  }
  if (tag == "Pass")
  {
    dest->stencil_pass_front_ = dest->stencil_pass_back_ = this->parser_.ParseStencilOperation();
    return;
  }
  if (tag == "Fail")
  {
    dest->stencil_fail_front_ = dest->stencil_fail_back_ = this->parser_.ParseStencilOperation();
    return;
  }
  if (tag == "ZFail")
  {
    dest->stencil_zfail_front_ = dest->stencil_zfail_back_ = this->parser_.ParseStencilOperation();
    return;
  }
  // Front
  if (tag == "CompFront")
  {
    dest->stencil_comp_front_ = this->parser_.ParseComparasionFunc();
    return;
  }
  if (tag == "PassFront")
  {
    dest->stencil_pass_front_ = this->parser_.ParseStencilOperation();
    return;
  }
  if (tag == "FailFront")
  {
    dest->stencil_fail_front_ = this->parser_.ParseStencilOperation();
    return;
  }
  if (tag == "ZFailFront")
  {
    dest->stencil_zfail_front_ = this->parser_.ParseStencilOperation();
    return;
  }
  // Back
  if (tag == "CompBack")
  {
    dest->stencil_comp_back_ = this->parser_.ParseComparasionFunc();
    return;
  }
  if (tag == "PassBack")
  {
    dest->stencil_pass_back_ = this->parser_.ParseStencilOperation();
    return;
  }
  if (tag == "FailBack")
  {
    dest->stencil_fail_back_ = this->parser_.ParseStencilOperation();
    return;
  }
  if (tag == "ZFailBack")
  {
    dest->stencil_zfail_back_ = this->parser_.ParseStencilOperation();
    return;
  }
  this->parser_.ThrowIdentifierError("Stencilトークン", tag);
}

void ShaderCompiler::CompilePassData(HLSLCompiler * compiler, const ShaderData & data, PassData * dest)
{
  const std::string identifier = this->parser_.ParseIdentifier();
  using namespace GGGShaderParser;
  if (identifier == "LightMode")
  {
    dest->light_mode_ = this->parser_.ParseLightMode();
    return;
  }
  if (identifier == "Cull")
  {
    dest->render_state_data_.cull_mode_ = this->parser_.ParseCullMode();
    return;
  }
  if (identifier == "ZWrite")
  {
    dest->render_state_data_.z_write_ = this->parser_.ParseZWrite();
    return;
  }
  if (identifier == "ZTest")
  {
    dest->render_state_data_.z_test_ = this->parser_.ParseComparasionFunc();
    return;
  }
  if (identifier == "Blend")
  {
    T_INT8 state_index = -1;
    // レンダーターゲット指定があった場合
    if (this->parser_.CheckNextToken() == TokenType::kNumber)
    {
      state_index = (T_INT8)this->parser_.ParseInt();
    }
    const std::string value = this->parser_.ParseIdentifier();
    // ブレンドステートを無効にする
    if (value == "Off")
    {
      const T_UINT8 render_target_count = (T_UINT8)dest->render_state_data_.blend_state_datas_.size();
      for (T_UINT8 i = 0; i < render_target_count; ++i)
      {
        if (state_index != -1 && i != state_index)
        {
          continue;
        }
        dest->render_state_data_.blend_state_datas_[i].enabled_ = false;
      }
      return;
    }
    T_INT32 src_factor = this->parser_.ParseBlendFactor(value);
    T_INT32 dst_factor = this->parser_.ParseBlendFactor();
    T_INT32 asrc_factor = src_factor;
    T_INT32 adst_factor = dst_factor;
    // アルファのFactor指定があった場合
    if (this->parser_.CheckNextToken() == TokenType::kComma)
    {
      this->parser_.EatToken();
      asrc_factor = this->parser_.ParseBlendFactor();
      adst_factor = this->parser_.ParseBlendFactor();
    }
    // ブレンドステートを設定していく
    const T_UINT8 render_target_count = (T_UINT8)dest->render_state_data_.blend_state_datas_.size();
    for (T_UINT8 i = 0; i < render_target_count; ++i)
    {
      if (state_index != -1 && i != state_index)
      {
        continue;
      }
      dest->render_state_data_.blend_state_datas_[i].enabled_ = true;
      dest->render_state_data_.blend_state_datas_[i].blend_color_src_factor_ = src_factor;
      dest->render_state_data_.blend_state_datas_[i].blend_color_dst_factor_ = dst_factor;
      dest->render_state_data_.blend_state_datas_[i].blend_alpha_src_factor_ = asrc_factor;
      dest->render_state_data_.blend_state_datas_[i].blend_alpha_dst_factor_ = adst_factor;
    }
    return;
  }
  if (identifier == "BlendOp")
  {
    T_INT8 state_index = -1;
    // レンダーターゲット指定があった場合
    if (this->parser_.CheckNextToken() == TokenType::kNumber)
    {
      state_index = (T_INT8)this->parser_.ParseInt();
    }
    T_INT32 color_op = this->parser_.ParseBlendOp();
    T_INT32 alpha_op = color_op;
    // アルファのFactor指定があった場合
    if (this->parser_.CheckNextToken() == TokenType::kComma)
    {
      this->parser_.EatToken();
      alpha_op = this->parser_.ParseBlendOp();
    }
    // ブレンドステートを設定していく
    const T_UINT8 render_target_count = (T_UINT8)dest->render_state_data_.blend_state_datas_.size();
    for (T_UINT8 i = 0; i < render_target_count; ++i)
    {
      if (state_index != -1 && i != state_index)
      {
        continue;
      }
      dest->render_state_data_.blend_state_datas_[i].blend_color_op_ = color_op;
      dest->render_state_data_.blend_state_datas_[i].blend_alpha_op_ = alpha_op;
    }
    return;
  }
  if (identifier == "Stencil")
  {
    dest->render_state_data_.stencil_state_data_.enabled_ = true;
    this->parser_.GetToken(TokenType::kBlockBegin);
    while (this->parser_.CheckNextToken() != TokenType::kBlockEnd)
    {
      this->CompileStencilData(&dest->render_state_data_.stencil_state_data_);
    }
    this->parser_.EatToken();
    return;
  }
  if (identifier == "CODE_BEGIN")
  {
    std::string program = this->parser_.GetText("CODE_END");
    compiler->ConvertHLSL(data, &program);
    try
    {
      compiler->CompileVertexShader(program, &dest->vs_byte_code_);
      compiler->CompilePixelShader(program, &dest->ps_byte_code_);
    }
    catch (HLSLCompileException e)
    {
      this->parser_.ThrowError(e.message);
    }
    return;
  }
  this->parser_.ThrowIdentifierError("Passトークン", identifier);
}

void ShaderCompiler::CompilePass(HLSLCompiler* compiler, ShaderData* dest, bool grab)
{
  this->parser_.GetToken(TokenType::kBlockBegin);
  PassData pass_data = PassData();
  while (this->parser_.CheckNextToken() != TokenType::kBlockEnd)
  {
    this->CompilePassData(compiler, *dest, &pass_data);
  }
  this->parser_.EatToken();
  pass_data.grab_ = grab;
  dest->passes_.emplace_back(pass_data);
}

void ShaderCompiler::CompileGrabPass(ShaderData* dest)
{
  this->parser_.GetToken(TokenType::kBlockBegin);
  while (this->parser_.CheckNextToken() != TokenType::kBlockEnd)
  {
    this->parser_.EatToken();
  }
  this->parser_.EatToken();
}
