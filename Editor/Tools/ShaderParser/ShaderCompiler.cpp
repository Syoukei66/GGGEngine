#include "ShaderCompiler.h"
#include "ShaderToken.h"

ShaderCompiler::ShaderCompiler(const std::string& str)
  : parser_(str)
{
}

void ShaderCompiler::Compile(HLSLCompiler* compiler, ShaderData* dest)
{
  bool grab = false;
  while (this->parser_.CheckNextToken() != TokenType::kEOF)
  {
    std::string token = "";
    if (!this->parser_.ParseIdentifier(&token))
    {
      // エラー
      break;
    }
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
      this->CompilePass(compiler, dest, grab);
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

bool ShaderCompiler::CompileName(ShaderData* dest)
{
  return this->parser_.ParseText(&dest->name_);
}

bool ShaderCompiler::CompileProperty(ShaderData* dest)
{
  std::string property_id = "";
  std::string property_name = "";
  std::string property_type = "";
  if (!this->parser_.ParseIdentifier(&property_id)) return false;
  if (!this->parser_.GetToken(TokenType::kParenBegin)) return false;
  if (!this->parser_.ParseText(&property_name)) return false;
  if (!this->parser_.GetToken(TokenType::kComma)) return false;
  if (!this->parser_.ParseSpecialIdentifier(&property_type)) return false;
  using namespace GGGShaderParser;
  if (property_type == "Range")
  {
    ScalaPropertyData data;
    if (!this->parser_.GetToken(TokenType::kParenBegin)) return false;
    if (!this->parser_.ParseFloat(&data.min_value_)) return false;
    if (!this->parser_.GetToken(TokenType::kComma)) return false;
    if (!this->parser_.ParseFloat(&data.max_value_)) return false;
    if (!this->parser_.GetToken(TokenType::kParenEnd)) return false;
    if (!this->parser_.GetToken(TokenType::kParenEnd)) return false;
    if (!this->parser_.GetToken(TokenType::kEqual)) return false;
    if (!this->parser_.ParseFloat(&data.init_value_)) return false;
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.variable_type_ = static_cast<T_FIXED_UINT8>(Shader::VariableType::kFloat);
    dest->scala_properties_.emplace_back(data);
    return true;
  }
  if (property_type == "Float")
  {
    ScalaPropertyData data;
    if (!this->parser_.GetToken(TokenType::kParenEnd)) return false;
    if (!this->parser_.GetToken(TokenType::kEqual)) return false;
    if (!this->parser_.ParseFloat(&data.init_value_)) return false;
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.variable_type_ = static_cast<T_FIXED_UINT8>(Shader::VariableType::kFloat);
    data.min_value_ = Limit::T_FLOAT_MIN;
    data.max_value_ = Limit::T_FLOAT_MAX;
    dest->scala_properties_.emplace_back(data);
    return true;
  }
  if (property_type == "Int")
  {
    ScalaPropertyData data;
    if (!this->parser_.GetToken(TokenType::kParenEnd)) return false;
    if (!this->parser_.GetToken(TokenType::kEqual)) return false;
    if (!this->parser_.ParseInt(&data.init_value_)) return false;
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.variable_type_ = static_cast<T_FIXED_UINT8>(Shader::VariableType::kInt);
    data.min_value_ = (T_FLOAT)Limit::T_INT32_MIN;
    data.max_value_ = (T_FLOAT)Limit::T_INT32_MAX;
    dest->scala_properties_.emplace_back(data);
    return true;
  }
  if (property_type == "Vector")
  {
    VectorPropertyData data;
    if (!this->parser_.GetToken(TokenType::kParenEnd)) return false;
    if (!this->parser_.GetToken(TokenType::kEqual)) return false;
    if (!this->parser_.GetToken(TokenType::kBlockBegin)) return false;
    // {}の場合はすべて0、　数値が入ってた場合は数値を読み取る
    if (this->parser_.CheckNextToken() != TokenType::kBlockEnd)
    {
      if (!this->parser_.ParseFloat(&data.init_value0_)) return false;
      if (!this->parser_.GetToken  (TokenType::kComma)) return false;
      if (!this->parser_.ParseFloat(&data.init_value1_)) return false;
      if (!this->parser_.GetToken  (TokenType::kComma)) return false;
      if (!this->parser_.ParseFloat(&data.init_value2_)) return false;
      if (!this->parser_.GetToken  (TokenType::kComma)) return false;
      if (!this->parser_.ParseFloat(&data.init_value3_)) return false;
      if (!this->parser_.GetToken  (TokenType::kBlockEnd)) return false;
    }
    else
    {
      this->parser_.EatToken();
    }
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.variable_type_ = static_cast<T_FIXED_UINT8>(Shader::VariableType::kFloat);
    dest->vector_properties_.emplace_back(data);
    return true;
  }
  if (property_type == "Color")
  {
    ColorPropertyData data;
    if (!this->parser_.GetToken(TokenType::kParenEnd)) return false;
    if (!this->parser_.GetToken(TokenType::kEqual)) return false;
    if (!this->parser_.GetToken(TokenType::kBlockBegin)) return false;
    // {}の場合はすべて1、　数値が入ってた場合は数値を読み取る
    if (this->parser_.CheckNextToken() != TokenType::kBlockEnd)
    {
      if (!this->parser_.ParseFloat(&data.init_r_)) return false;
      if (!this->parser_.GetToken(TokenType::kComma)) return false;
      if (!this->parser_.ParseFloat(&data.init_g_)) return false;
      if (!this->parser_.GetToken(TokenType::kComma)) return false;
      if (!this->parser_.ParseFloat(&data.init_b_)) return false;
      if (!this->parser_.GetToken(TokenType::kComma)) return false;
      if (!this->parser_.ParseFloat(&data.init_a_)) return false;
      if (!this->parser_.GetToken(TokenType::kBlockEnd)) return false;
    }
    else
    {
      this->parser_.EatToken();
    }
    data.name_ = property_id;
    data.display_name_ = property_name;
    dest->color_properties_.emplace_back(data);
    return true;
  }
  if (property_type == "2D")
  {
    std::string init_tex;
    if (!this->parser_.GetToken(TokenType::kParenEnd)) return false;
    if (!this->parser_.GetToken(TokenType::kEqual)) return false;
    if (!this->parser_.ParseText(&init_tex)) return false;
    SamplerPropertyData data;
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.sampler_type_ = static_cast<T_FIXED_UINT8>(Shader::SamplerType::kSampler2D);
    data.default_texture_ = ParseDefaultTextureType(init_tex);
    dest->sampler_properties_.emplace_back(data);
    return true;
  }
  return false;
}

bool ShaderCompiler::CompileProperties(ShaderData* dest)
{
  if (!this->parser_.GetToken(TokenType::kBlockBegin)) return false;
  while (this->parser_.CheckNextToken() != TokenType::kBlockEnd)
  {
    if (!CompileProperty(dest))
    {
      return false;
    }
  }
  if (!this->parser_.GetToken(TokenType::kBlockEnd)) return false;
  return true;
}

bool ShaderCompiler::CompileTag(ShaderData* dest)
{
  std::string tag_type = "";
  std::string tag_value = "";
  if (!this->parser_.ParseIdentifier(&tag_type)) return false;
  if (!this->parser_.ParseIdentifier(&tag_value)) return false;
  using namespace GGGShaderParser;
  if (tag_type == "Queue")
  {
    dest->queue_ = ParseRenderQueue(tag_value);
    return true;
  }
  if (tag_type == "RenderType")
  {
    dest->render_type_ = ParseRenderType(tag_value);
    return true;
  }
  return false;
}

bool ShaderCompiler::CompileTags(ShaderData* dest)
{
  if (!this->parser_.GetToken(TokenType::kBlockBegin)) return false;
  while (this->parser_.CheckNextToken() != TokenType::kBlockEnd)
  {
    if (!CompileTag(dest))
    {
      return false;
    }
  }
  this->parser_.EatToken();
  return true;
}

bool ShaderCompiler::CompileStencilData(StencilStateData * dest)
{
  using namespace GGGShaderParser;
  std::string tag = "";
  if (!this->parser_.ParseIdentifier(&tag)) return false;
  if (tag == "Ref")
  {
    T_FLOAT value = 0.0f;
    if (!this->parser_.ParseInt(&value)) return false;
    dest->stencil_ref_ = (T_FIXED_UINT8)value;
    return true;
  }
  if (tag == "ReadMask")
  {
    T_FLOAT value = 0.0f;
    if (!this->parser_.ParseInt(&value)) return false;
    dest->stencil_read_mask_ = (T_FIXED_UINT8)value;
    return true;
  }
  if (tag == "WriteMask")
  {
    T_FLOAT value = 0.0f;
    if (!this->parser_.ParseInt(&value)) return false;
    dest->stencil_write_mask_ = (T_FIXED_UINT8)value;
    return true;
  }
  std::string value = "";
  if (!this->parser_.ParseIdentifier(&value)) return false;
  if (tag == "Comp")
  {
    dest->stencil_comp_front_ = dest->stencil_comp_back_ = ParseComparasionFunc(value);
    return true;
  }
  if (tag == "Pass")
  {
    dest->stencil_pass_front_ = dest->stencil_pass_back_ = ParseStencilOperation(value);
    return true;
  }
  if (tag == "Fail")
  {
    dest->stencil_fail_front_ = dest->stencil_fail_back_ = ParseStencilOperation(value);
    return true;
  }
  if (tag == "ZFail")
  {
    dest->stencil_zfail_front_ = dest->stencil_zfail_back_ = ParseStencilOperation(value);
    return true;
  }
  // Front
  if (tag == "CompFront")
  {
    dest->stencil_comp_front_ = ParseComparasionFunc(value);
    return true;
  }
  if (tag == "PassFront")
  {
    dest->stencil_pass_front_ = ParseStencilOperation(value);
    return true;
  }
  if (tag == "FailFront")
  {
    dest->stencil_fail_front_ = ParseStencilOperation(value);
    return true;
  }
  if (tag == "ZFailFront")
  {
    dest->stencil_zfail_front_ = ParseStencilOperation(value);
    return true;
  }
  // Back
  if (tag == "CompBack")
  {
    dest->stencil_comp_back_ = ParseComparasionFunc(value);
    return true;
  }
  if (tag == "PassBack")
  {
    dest->stencil_pass_back_ = ParseStencilOperation(value);
    return true;
  }
  if (tag == "FailBack")
  {
    dest->stencil_fail_back_ = ParseStencilOperation(value);
    return true;
  }
  if (tag == "ZFailBack")
  {
    dest->stencil_zfail_back_ = ParseStencilOperation(value);
    return true;
  }
  return false;
}

bool ShaderCompiler::CompilePassData(HLSLCompiler * compiler, const ShaderData & data, PassData * dest)
{
  std::string identifier = "";
  if (!this->parser_.ParseIdentifier(&identifier)) return false;

  using namespace GGGShaderParser;
  if (identifier == "LightMode")
  {
    std::string value = "";
    if (!this->parser_.ParseIdentifier(&value)) return false;
    dest->light_mode_ = ParseLightMode(value);
    return true;
  }
  if (identifier == "Cull")
  {
    std::string value = "";
    if (!this->parser_.ParseIdentifier(&value)) return false;
    dest->render_state_data_.cull_mode_ = ParseCullMode(value);
    return true;
  }
  if (identifier == "ZWrite")
  {
    std::string value = "";
    if (!this->parser_.ParseIdentifier(&value)) return false;
    dest->render_state_data_.z_write_ = ParseZWrite(value);
    return true;
  }
  if (identifier == "ZTest")
  {
    std::string value = "";
    if (!this->parser_.ParseIdentifier(&value)) return false;
    dest->render_state_data_.z_test_ = ParseComparasionFunc(value);
    return true;
  }
  if (identifier == "Blend")
  {
    T_INT8 state_index = -1;
    // レンダーターゲット指定があった場合
    if (this->parser_.CheckNextToken() == TokenType::kNumber)
    {
      T_FLOAT value = 0.0f;
      if (!this->parser_.ParseInt(&value)) return false;
      state_index = (T_INT8)value;
    }
    std::string value = "";
    if (!this->parser_.ParseIdentifier(&value)) return false;
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
      return true;
    }
    T_INT32 src_factor = ParseBlendFactor(value);
    if (!this->parser_.ParseIdentifier(&value)) return false;
    T_INT32 dst_factor = ParseBlendFactor(value);
    T_INT32 asrc_factor = src_factor;
    T_INT32 adst_factor = dst_factor;
    // アルファのFactor指定があった場合
    if (this->parser_.CheckNextToken() == TokenType::kComma)
    {
      this->parser_.EatToken();
      if (!this->parser_.ParseIdentifier(&value)) return false;
      asrc_factor = ParseBlendFactor(value);
      if (!this->parser_.ParseIdentifier(&value)) return false;
      adst_factor = ParseBlendFactor(value);
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
    return true;
  }
  if (identifier == "BlendOp")
  {
    T_INT8 state_index = -1;
    // レンダーターゲット指定があった場合
    if (this->parser_.CheckNextToken() == TokenType::kNumber)
    {
      T_FLOAT value = 0.0f;
      if (!this->parser_.ParseInt(&value)) return false;
      state_index = (T_INT8)value;
    }
    std::string value = "";
    if (!this->parser_.ParseIdentifier(&value)) return false;
    T_INT32 color_op = ParseBlendOp(value);
    T_INT32 alpha_op = color_op;
    // アルファのFactor指定があった場合
    if (this->parser_.CheckNextToken() == TokenType::kComma)
    {
      this->parser_.EatToken();
      if (!this->parser_.ParseIdentifier(&value)) return false;
      alpha_op = ParseBlendOp(value);
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
    return true;
  }
  if (identifier == "Stencil")
  {
    dest->render_state_data_.stencil_state_data_.enabled_ = true;
    if (!this->parser_.GetToken(TokenType::kBlockBegin)) return false;
    while (this->parser_.CheckNextToken() != TokenType::kBlockEnd)
    {
      if (!CompileStencilData(&dest->render_state_data_.stencil_state_data_))
      {
        return false;
      }
    }
    this->parser_.EatToken();
    return true;
  }
  if (identifier == "CODE_BEGIN")
  {
    std::string program = "";
    this->parser_.GetText("CODE_END", &program);
    compiler->ConvertHLSL(data, &program);
    compiler->CompileVertexShader(program, &dest->vs_byte_code_);
    compiler->CompilePixelShader(program, &dest->ps_byte_code_);
    return true;
  }
  return false;
}

bool ShaderCompiler::CompilePass(HLSLCompiler * compiler, ShaderData * dest, bool grab)
{
  if (!this->parser_.GetToken(TokenType::kBlockBegin)) return false;
  PassData pass_data = PassData();
  while (this->parser_.CheckNextToken() != TokenType::kBlockEnd)
  {
    if (!CompilePassData(compiler, *dest, &pass_data))
    {
      return false;
    }
  }
  this->parser_.EatToken();
  pass_data.grab_ = grab;
  dest->passes_.emplace_back(pass_data);
  return true;
}

bool ShaderCompiler::CompileGrabPass(ShaderData * dest)
{
  if (!this->parser_.GetToken(TokenType::kBlockBegin)) return false;
  while (this->parser_.CheckNextToken() != TokenType::kBlockEnd)
  {
    this->parser_.EatToken();
  }
  this->parser_.EatToken();
  return true;
}
