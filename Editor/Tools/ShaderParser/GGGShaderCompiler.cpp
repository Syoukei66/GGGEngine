#include "stdafx.h"
#include "GGGShaderCompiler.h"
#include "ShaderToken.h"

#define ASSERT_EOF(Method) GG_ASSERT_NO_ENTRY(Method ": �\������EOF")
#define ASSERT_TOKEN(Method) GG_ASSERT_NO_ENTRY(Method ": �\�����ʃg�[�N��")
#define ASSERT_PARSE(Method, Message) GG_ASSERT_NO_ENTRY(Method ": " Message)

enum class TokenType : T_UINT8
{
  kNoExcepted,
  kEOF,
  kSpace,
  kEnter,
  kBlockBegin,
  kBlockEnd,
  kParenBegin,
  kParenEnd,
  kTextParen,
  kComma,
  kEqual,
  kSlash,
  kIdentifier
};

TokenType GetSeparator(const char c)
{
  if (c == '\0')
  {
    return TokenType::kEOF;
  }
  if (c == ' ' || c == '\t')
  {
    return TokenType::kSpace;
  }
  if (c == '\n')
  {
    return TokenType::kEnter;
  }
  if (c == '{')
  {
    return TokenType::kBlockBegin;
  }
  if (c == '}')
  {
    return TokenType::kBlockEnd;
  }
  if (c == '(')
  {
    return TokenType::kParenBegin;
  }
  if (c == ')')
  {
    return TokenType::kParenEnd;
  }
  if (c == '\"')
  {
    return TokenType::kTextParen;
  }
  if (c == ',')
  {
    return TokenType::kComma;
  }
  if (c == '=')
  {
    return TokenType::kEqual;
  }
  if (c == '/')
  {
    return TokenType::kSlash;
  }
  if (
    ('a' <= c && c <= 'z') ||
    ('A' <= c && c <= 'Z') ||
    ('0' <= c && c <= '9') ||
    (c == '_')
    )
  {
    return TokenType::kIdentifier;
  }
  return TokenType::kNoExcepted;
}

/*!
 * @brief �g�[�N�����󂯎��
 * @param p ���݂̕����|�C���^
 * @param token �g�[�N�����󂯎��
 * @return ���̃g�[�N���̏��
 */
TokenType NextToken(const char** p, std::string* token = nullptr)
{
  // �󔒂��X�L�b�v
  TokenType separator;
  while ((separator = GetSeparator(**p)) == TokenType::kSpace)
  {
    ++(*p);
  }
  // ��؂�L�����o�Ă���܂ł��g�[�N����
  while ((separator = GetSeparator(**p)) == TokenType::kIdentifier)
  {
    if (token)
    {
      (*token) += (**p);
    }
    ++(*p);
  }
  return separator;
}

/*!
 * @brief �g�[�N�����擾���邪�A�����|�C���^��ω������Ȃ�
 * @param p ���݂̕����|�C���^
 * @param token �g�[�N�����󂯎��
 * @return ���̃g�[�N���̏��
 */
TokenType CheckNextToken(const char** p, std::string* token = nullptr)
{
  const char* const buf = (*p);
  TokenType ret = NextToken(p, token);
  (*p) = buf;
  return ret;
}

/*!
 * @brief �^���w�肵�ăg�[�N�����擾����B�g�[�N�����w�肵���^�ƈ������G���[
 * @param p ���݂̕����|�C���^
 * @param type �g�[�N���̌^
 * @param token �g�[�N�����󂯎��
 * @return type�ŗ^�����g�[�N���̌^���Ⴄ�ꍇfalse
 */
bool GetToken(const char** p, TokenType type, std::string* token = nullptr)
{
  if (NextToken(p, token) == type)
  {
    return true;
  }
  ASSERT_TOKEN(GetToken);
  return false;
}

/*!
 * @brief Property�̃p�[�X
 * @return false�Ȃ玸�s
 */
bool ParseProperty(const char** p, ShaderData* dest)
{
  std::string property_id = "";
  std::string property_name = "";
  std::string property_type = "";
  if (!GetToken(p, TokenType::kIdentifier, &property_id)) return false;
  if (!GetToken(p, TokenType::kParenBegin)) return false;
  if (!GetToken(p, TokenType::kTextParen)) return false;
  if (!GetToken(p, TokenType::kIdentifier, &property_name)) return false;
  if (!GetToken(p, TokenType::kTextParen)) return false;
  if (!GetToken(p, TokenType::kComma)) return false;
  if (!GetToken(p, TokenType::kIdentifier, &property_type)) return false;
  using namespace GGGShaderParser;
  if (property_type == "Range")
  {
    std::string min = "";
    std::string max = "";
    std::string init = "";
    if (!GetToken(p, TokenType::kParenBegin)) return false;
    if (!GetToken(p, TokenType::kIdentifier, &min)) return false;
    if (!GetToken(p, TokenType::kComma)) return false;
    if (!GetToken(p, TokenType::kIdentifier, &max)) return false;
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    if (!GetToken(p, TokenType::kEqual)) return false;
    if (!GetToken(p, TokenType::kIdentifier, &init)) return false;
    ScalaPropertyData data;
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.variable_type_ = static_cast<T_FIXED_UINT8>(Shader::VariableType::kFloat);
    char* err;
    data.min_value_ = (T_FLOAT)std::strtod(min.c_str(), &err);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "�ŏ��l�������ł�");
      return false;
    }
    data.max_value_ = (T_FLOAT)std::strtod(max.c_str(), &err);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "�ő�l�������ł�");
      return false;
    }
    data.init_value_ = (T_FLOAT)std::strtod(init.c_str(), &err);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "�����l�������ł�");
      return false;
    }
    dest->scala_properties_.emplace_back(data);
    return true;
  }
  if (property_type == "Float")
  {
    std::string init = "";
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    if (!GetToken(p, TokenType::kEqual)) return false;
    if (!GetToken(p, TokenType::kIdentifier, &init)) return false;
    ScalaPropertyData data;
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.variable_type_ = static_cast<T_FIXED_UINT8>(Shader::VariableType::kFloat);
    char* err;
    data.min_value_ = Limit::T_FLOAT_MIN;
    data.max_value_ = Limit::T_FLOAT_MAX;
    data.init_value_ = std::strtof(init.c_str(), &err);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "�����l�������ł�");
      return false;
    }
    dest->scala_properties_.emplace_back(data);
    return true;
  }
  if (property_type == "Int")
  {
    std::string init = "";
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    if (!GetToken(p, TokenType::kEqual)) return false;
    if (!GetToken(p, TokenType::kIdentifier, &init)) return false;
    ScalaPropertyData data;
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.variable_type_ = static_cast<T_FIXED_UINT8>(Shader::VariableType::kInt);
    char* err;
    data.min_value_ = Limit::T_INT32_MIN;
    data.max_value_ = Limit::T_INT32_MAX;
    data.init_value_ = (T_FLOAT)std::strtol(init.c_str(), &err, 10);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "�����l�������ł�");
      return false;
    }
    dest->scala_properties_.emplace_back(data);
    return true;
  }
  if (property_type == "Vector")
  {
    std::string init_0 = "";
    std::string init_1 = "";
    std::string init_2 = "";
    std::string init_3 = "";
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    if (!GetToken(p, TokenType::kEqual)) return false;
    if (!GetToken(p, TokenType::kParenBegin)) return false;
    if (!GetToken(p, TokenType::kIdentifier, &init_0)) return false;
    if (!GetToken(p, TokenType::kComma)) return false;
    if (!GetToken(p, TokenType::kIdentifier, &init_1)) return false;
    if (!GetToken(p, TokenType::kComma)) return false;
    if (!GetToken(p, TokenType::kIdentifier, &init_2)) return false;
    if (!GetToken(p, TokenType::kComma)) return false;
    if (!GetToken(p, TokenType::kIdentifier, &init_3)) return false;
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    VectorPropertyData data;
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.variable_type_ = static_cast<T_FIXED_UINT8>(Shader::VariableType::kFloat);
    char* err;
    data.init_value0_ = std::strtof(init_0.c_str(), &err);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "1�Ԗڂ̏����l�������ł�");
      return false;
    }
    data.init_value1_ = std::strtof(init_1.c_str(), &err);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "2�Ԗڂ̏����l�������ł�");
      return false;
    }
    data.init_value2_ = std::strtof(init_2.c_str(), &err);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "3�Ԗڂ̏����l�������ł�");
      return false;
    }
    data.init_value3_ = std::strtof(init_3.c_str(), &err);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "4�Ԗڂ̏����l�������ł�");
      return false;
    }
    dest->vector_properties_.emplace_back(data);
    return true;
  }
  if (property_type == "Color")
  {
    std::string init_r = "";
    std::string init_g = "";
    std::string init_b = "";
    std::string init_a = "";
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    if (!GetToken(p, TokenType::kEqual)) return false;
    if (!GetToken(p, TokenType::kParenBegin)) return false;
    if (!GetToken(p, TokenType::kIdentifier, &init_r)) return false;
    if (!GetToken(p, TokenType::kComma)) return false;
    if (!GetToken(p, TokenType::kIdentifier, &init_g)) return false;
    if (!GetToken(p, TokenType::kComma)) return false;
    if (!GetToken(p, TokenType::kIdentifier, &init_b)) return false;
    if (!GetToken(p, TokenType::kComma)) return false;
    if (!GetToken(p, TokenType::kIdentifier, &init_a)) return false;
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    ColorPropertyData data;
    data.name_ = property_id;
    data.display_name_ = property_name;
    char* err;
    data.init_r_ = std::strtof(init_r.c_str(), &err);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "R�̏����l�������ł�");
      return false;
    }
    data.init_g_ = std::strtof(init_g.c_str(), &err);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "G�̏����l�������ł�");
      return false;
    }
    data.init_b_ = std::strtof(init_b.c_str(), &err);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "B�̏����l�������ł�");
      return false;
    }
    data.init_a_ = std::strtof(init_a.c_str(), &err);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "A�̏����l�������ł�");
      return false;
    }
    dest->color_properties_.emplace_back(data);
    return true;
  }
  if (property_type == "2D")
  {
    SamplerPropertyData data;
    std::string init_tex = "";
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    if (!GetToken(p, TokenType::kEqual)) return false;
    if (!GetToken(p, TokenType::kIdentifier, &init_tex)) return false;
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.sampler_type_ = static_cast<T_FIXED_UINT8>(Shader::SamplerType::kSampler2D);
    data.default_texture_ = ParseDefaultTextureType(init_tex);
    dest->sampler_properties_.emplace_back(data);
    return true;
  }
  return false;
}

/*!
 * @brief Properties�̃p�[�X
 * @return false�Ȃ玸�s
 */
bool ParseProperties(const char** p, ShaderData* dest)
{
  if (!GetToken(p, TokenType::kBlockBegin)) return false;
  while (NextToken(p) != TokenType::kBlockEnd)
  {
    if (!ParseProperty(p, dest))
    {
      return false;
    }
    GetToken(p, TokenType::kEnter);
  }
  return true;
}

/*!
 * @brief Tag�̃p�[�X
 * @return false�Ȃ玸�s
 */
bool ParseTag(const char** p, ShaderData* dest)
{
  std::string tag_type = "";
  std::string tag_value = "";
  if (!GetToken(p, TokenType::kIdentifier, &tag_type)) return false;
  if (!GetToken(p, TokenType::kIdentifier, &tag_value)) return false;
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

/*!
 * @brief Tags�̃p�[�X
 * @return false�Ȃ玸�s
 */
bool ParseTags(const char** p, ShaderData* dest)
{
  if (!GetToken(p, TokenType::kBlockBegin)) return false;
  while (NextToken(p) != TokenType::kBlockEnd)
  {
    if (!ParseTag(p, dest))
    {
      return false;
    }
    GetToken(p, TokenType::kEnter);
  }
  return true;
}

/*!
 * @brief Stencil�u���b�N�̃p�[�X
 * @return false�Ȃ玸�s
 */
bool ParseStencilData(const char** p, StencilStateData* dest)
{
  using namespace GGGShaderParser;
  std::string tag = "";
  std::string value = "";
  if (!GetToken(p, TokenType::kIdentifier, &tag)) return false;
  if (!GetToken(p, TokenType::kIdentifier, &value)) return false;
  if (tag == "Ref")
  {
    char* err;
    dest->stencil_ref_ = (T_FIXED_UINT8)std::strtol(value.c_str(), &err, 10);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "Stencil Ref�Ɏw�肵�����l�������ł�");
      return false;
    }
    return true;
  }
  if (tag == "ReadMask")
  {
    char* err;
    dest->stencil_read_mask_ = (T_FIXED_UINT8)std::strtol(value.c_str(), &err, 10);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "Stencil Ref�Ɏw�肵�����l�������ł�");
      return false;
    }
    return true;
  }
  if (tag == "WriteMask")
  {
    char* err;
    dest->stencil_write_mask_ = (T_FIXED_UINT8)std::strtol(value.c_str(), &err, 10);
    if (*err)
    {
      ASSERT_PARSE(ParseProperty, "Stencil Ref�Ɏw�肵�����l�������ł�");
      return false;
    }
    return true;
  }
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

/*!
 * @brief Pass�ɋL�q����Ă���v�f�̃p�[�X
 * @return false�Ȃ玸�s
 */
bool ParsePassData(const char** p, IHLSLCompiler* compiler, const ShaderData& data, PassData* dest)
{
  std::string identifier = "";
  if (!GetToken(p, TokenType::kIdentifier, &identifier)) return false;

  using namespace GGGShaderParser;
  if (identifier == "LightMode")
  {
    std::string value = "";
    if (!GetToken(p, TokenType::kIdentifier, &value)) return false;
    dest->light_mode_ = ParseLightMode(value);
    return true;
  }
  if (identifier == "Cull")
  {
    std::string value = "";
    if (!GetToken(p, TokenType::kIdentifier, &value)) return false;
    dest->render_state_data_.cull_mode_ = ParseCullMode(value);
    return true;
  }
  if (identifier == "ZWrite")
  {
    std::string value = "";
    if (!GetToken(p, TokenType::kIdentifier, &value)) return false;
    dest->render_state_data_.z_write_ = ParseZWrite(value);
    return true;
  }
  if (identifier == "ZTest")
  {
    std::string value = "";
    if (!GetToken(p, TokenType::kIdentifier, &value)) return false;
    dest->render_state_data_.z_test_ = ParseComparasionFunc(value);
    return true;
  }
  if (identifier == "Blend")
  {
    std::string value = "";
    if (!GetToken(p, TokenType::kIdentifier, &value)) return false;
    T_INT8 state_index = -1;
    T_INT32 src_factor = ParseBlendFactor(value);
    // �����_�[�^�[�Q�b�g�w�肪�������ꍇ
    if (src_factor == -1)
    {
      char* err;
      state_index = (T_INT8)std::strtol(value.c_str(), &err, 10);
      if (*err)
      {
        ASSERT_PARSE(ParseProperty, "�����_�[�^�[�Q�b�g�ԍ��������ł�");
        return false;
      }
      if (!GetToken(p, TokenType::kIdentifier, &value)) return false;
      src_factor = ParseBlendFactor(value);
    }
    if (!GetToken(p, TokenType::kIdentifier, &value)) return false;
    T_INT32 dst_factor = ParseBlendFactor(value);
    T_INT32 asrc_factor = src_factor;
    T_INT32 adst_factor = dst_factor;
    // �A���t�@��Factor�w�肪�������ꍇ
    if (CheckNextToken(p) == TokenType::kComma)
    {
      if (!GetToken(p, TokenType::kIdentifier, &value)) return false;
      asrc_factor = ParseBlendFactor(value);
      if (!GetToken(p, TokenType::kIdentifier, &value)) return false;
      adst_factor = ParseBlendFactor(value);
    }
    // �u�����h�X�e�[�g��ݒ肵�Ă���
    const T_UINT8 render_target_count = (T_UINT8)dest->render_state_data_.blend_state_datas_.size();
    for (T_UINT8 i = 0; i < render_target_count; ++i)
    {
      if (state_index != -1 && i != state_index)
      {
        continue;
      }
      dest->render_state_data_.blend_state_datas_[i].blend_color_src_factor_ = src_factor;
      dest->render_state_data_.blend_state_datas_[i].blend_color_dst_factor_ = dst_factor;
      dest->render_state_data_.blend_state_datas_[i].blend_alpha_src_factor_ = asrc_factor;
      dest->render_state_data_.blend_state_datas_[i].blend_alpha_dst_factor_ = adst_factor;
    }
  }
  if (identifier == "BlendOp")
  {
    std::string value = "";
    if (!GetToken(p, TokenType::kIdentifier, &value)) return false;
    T_INT8 state_index = -1;
    T_INT32 color_op = ParseBlendOp(value);
    // �����_�[�^�[�Q�b�g�w�肪�������ꍇ
    if (color_op == -1)
    {
      char* err;
      state_index = (T_INT8)std::strtol(value.c_str(), &err, 10);
      if (*err)
      {
        ASSERT_PARSE(ParseProperty, "�����_�[�^�[�Q�b�g�ԍ��������ł�");
        return false;
      }
      if (!GetToken(p, TokenType::kIdentifier, &value)) return false;
      color_op = ParseBlendOp(value);
    }
    T_INT32 alpha_op = color_op;
    // �A���t�@��Factor�w�肪�������ꍇ
    if (CheckNextToken(p) == TokenType::kComma)
    {
      if (!GetToken(p, TokenType::kIdentifier, &value)) return false;
      alpha_op = ParseBlendOp(value);
    }
    // �u�����h�X�e�[�g��ݒ肵�Ă���
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
  }
  if (identifier == "Stencil")
  {
    if (!GetToken(p, TokenType::kBlockBegin)) return false;
    while (NextToken(p) != TokenType::kBlockEnd)
    {
      if (!ParseStencilData(p, &dest->render_state_data_.stencil_state_data_))
      {
        return false;
      }
      GetToken(p, TokenType::kEnter);
    }
  }
  if (identifier == "CODE_BEGIN")
  {
    std::string end_simbol = "CODE_END";
    std::string program = "";
    while (program.find(end_simbol) != std::string::npos)
    {
      program += (**p);
      ++(*p);
    }
    program.replace(program.length() - end_simbol.length(), end_simbol.length(), "");
    compiler->ConvertHLSL(data, &program);
    compiler->CompileVertexShader(program, &dest->vs_byte_code_);
    compiler->CompilePixelShader(program, &dest->ps_byte_code_);
  }
}

/*!
 * @brief Pass�̃p�[�X
 * @return false�Ȃ玸�s
 */
bool ParsePass(const char** p, IHLSLCompiler* compiler, ShaderData* dest, bool grab)
{
  if (!GetToken(p, TokenType::kBlockBegin)) return false;
  PassData pass_data = PassData();
  while (NextToken(p) != TokenType::kBlockEnd)
  {
    if (!ParsePassData(p, compiler, *dest, &pass_data))
    {
      return false;
    }
    GetToken(p, TokenType::kEnter);
  }
  pass_data.grab_ = grab;
  dest->passes_.emplace_back(pass_data);
  return true;
}

/*!
 * @brief GrabPass�̃p�[�X
 * @return false�Ȃ玸�s
 */
bool ParseGrabPass(const char** p, ShaderData* dest)
{
  if (!GetToken(p, TokenType::kBlockBegin)) return false;
  while (NextToken(p) != TokenType::kBlockEnd);
  return true;
}

void GGGShaderCompiler::Parse(const std::string& str, IHLSLCompiler* compiler, ShaderData* dest)
{
  const char* p = str.c_str();
  std::string token = "";
  
  bool grab = false;
  TokenType type;
  while ((type = NextToken(&p, &token)) != TokenType::kEOF)
  {
    if (token == "Properties")
    {
      ParseProperties(&p, dest);
      continue;
    }
    if (token == "Tags")
    {
      ParseTags(&p, dest);
      continue;
    }
    if (token == "Pass")
    {
      ParsePass(&p, compiler, dest, grab);
      grab = false;
      continue;
    }
    if (token == "GrabPass")
    {
      ParseGrabPass(&p, dest);
      grab = true;
      continue;
    }
  }

}
