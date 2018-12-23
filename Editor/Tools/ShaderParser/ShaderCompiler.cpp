#include "ShaderCompiler.h"
#include "ShaderToken.h"

#define ASSERT_EOF(Method) GG_ASSERT(false, #Method ": �\������EOF")
#define ASSERT_TOKEN(Method) GG_ASSERT(false, #Method ": �\�����ʃg�[�N��")
#define ASSERT_PARSE(Method, Message) GG_ASSERT(false, #Method ": " #Message)

enum class TokenType : T_UINT8
{
  kNoExcepted,
  kEOF,
  kSpace,
  kBlockBegin,
  kBlockEnd,
  kParenBegin,
  kParenEnd,
  kTextParen,
  kComma,
  kEqual,
  kAlphabet,
  kNumber,
  kUnderBar,
  kDot,
  kPlus,
  kMinus,
};

TokenType GetSeparator(const char c)
{
  if (c == '\0')
  {
    return TokenType::kEOF;
  }
  if (c == ' ' || c == '\t' || c == '\n')
  {
    return TokenType::kSpace;
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
  if (c == '_')
  {
    return TokenType::kUnderBar;
  }
  if (c == '.')
  {
    return TokenType::kDot;
  }
  if (c == '+')
  {
    return TokenType::kPlus;
  }
  if (c == '-')
  {
    return TokenType::kMinus;
  }
  if ('0' <= c && c <= '9')
  {
    return TokenType::kNumber;
  }
  if (
    ('a' <= c && c <= 'z') ||
    ('A' <= c && c <= 'Z')
    )
  {
    return TokenType::kAlphabet;
  }
  return TokenType::kNoExcepted;
}

/*!
 * @brief �󔒂��X�L�b�v����
 * @param p ���݂̕����|�C���^
 */
void SkipSpace(const char** p)
{
  TokenType separator;
  while ((separator = GetSeparator(**p)) == TokenType::kSpace)
  {
    ++(*p);
  }
}

/*!
 * @brief ���̃g�[�N���̏����擾���邪�A�����|�C���^��ω������Ȃ�
 * @param p ���݂̕����|�C���^
 * @return ���̃g�[�N���̏��
 */
TokenType CheckNextToken(const char** p, bool skip_space = true)
{
  if (skip_space)
  {
    SkipSpace(p);
  }
  return GetSeparator(**p);
}

/*!
 * @brief �^���w�肵�ăg�[�N�����擾����B�g�[�N�����w�肵���^�ƈ������G���[
 * @param p ���݂̕����|�C���^
 * @param type �g�[�N���̌^
 * @return type�ŗ^�����g�[�N���̌^���Ⴄ�ꍇfalse
 */
bool GetToken(const char** p, TokenType type, bool skip_space = true)
{
  if (skip_space)
  {
    SkipSpace(p);
  }
  if (GetSeparator(**p) == type)
  {
    ++(*p);
    return true;
  }
  ASSERT_TOKEN(GetToken);
  return false;
}

/*!
 * @brief ���̃g�[�N���������B
 * @param p ���݂̕����|�C���^
 * @return EOF���o�������ꍇfalse
 */
bool EatToken(const char** p, bool skip_space = true)
{
  if (skip_space)
  {
    SkipSpace(p);
  }
  if (GetSeparator(**p) == TokenType::kEOF)
  {
    return false;
  }
  ++(*p);
  return true;
}

/*!
 * @brief �_�u���N�H�[�e�[�V�����ň͂܂ꂽ������̃p�[�X
 * @return false�Ȃ玸�s
 */
bool ParseText(const char** p, std::string* dest)
{
  (*dest).clear();
  if (!GetToken(p, TokenType::kTextParen))
  {
    return false;
  }
  while (CheckNextToken(p, false) !=TokenType::kTextParen)
  {
    (*dest) += **p;
    EatToken(p, false);
  }
  EatToken(p);
  return true;
}

/*!
 * @brief ���ʎq�̃p�[�X
 * @return false�Ȃ玸�s
 */
bool ParseIdentifier(const char** p, std::string* dest)
{
  (*dest).clear();
  TokenType next_token = CheckNextToken(p);
  if (next_token != TokenType::kAlphabet && next_token != TokenType::kUnderBar)
  {
    return false;
  }
  do
  {
    (*dest) += **p;
    EatToken(p, false);
    next_token = CheckNextToken(p, false);
  } while (next_token == TokenType::kAlphabet || next_token == TokenType::kUnderBar || next_token == TokenType::kNumber);
  return true;
}

/*!
 * @brief ���ꎯ�ʎq�̃p�[�X
 * �e�N�X�`���v���p�e�B�w��Ő��l����n�܂鎯�ʎq(2D, 3D)�ɑΉ�����K�v���o�Ă���
 * @return false�Ȃ玸�s
 */
bool ParseSpecialIdentifier(const char** p, std::string* dest)
{
  (*dest).clear();
  TokenType next_token = CheckNextToken(p);
  if (next_token != TokenType::kAlphabet && next_token != TokenType::kUnderBar && next_token != TokenType::kNumber)
  {
    return false;
  }
  do
  {
    (*dest) += **p;
    EatToken(p);
    next_token = CheckNextToken(p);
  } while (next_token == TokenType::kAlphabet || next_token == TokenType::kUnderBar || next_token == TokenType::kNumber);
  return true;
}

/*!
 * @brief �����l�̃p�[�X
 * @return false�Ȃ玸�s
 */
bool ParseInt(const char** p, T_FLOAT* dest)
{
  bool minus = false;
  TokenType next_token = CheckNextToken(p);
  // ���������̏���
  if (next_token == TokenType::kPlus)
  {
    EatToken(p);
    next_token = CheckNextToken(p);
  }
  else if (next_token == TokenType::kMinus)
  {
    minus = true;
    EatToken(p);
    next_token = CheckNextToken(p);
  }

  std::string str = minus ? "-" : "";
  if (next_token != TokenType::kNumber)
  {
    return false;
  }
  do
  {
    str += **p;
    EatToken(p);
  } while ((next_token = CheckNextToken(p, false)) == TokenType::kNumber);
  (*dest) = (T_FLOAT)std::strtol(str.c_str(), NULL, 10);
  return true;
}

/*!
 * @brief �����l�̃p�[�X
 * @return false�Ȃ玸�s
 */
bool ParseFloat(const char** p, T_FLOAT* dest)
{
  bool minus = false;
  TokenType next_token = CheckNextToken(p);
  // ���������̏���
  if (next_token == TokenType::kPlus)
  {
    EatToken(p);
    next_token = CheckNextToken(p);
  }
  else if (next_token == TokenType::kMinus)
  {
    minus = true;
    EatToken(p);
    next_token = CheckNextToken(p);
  }
  std::string sign = minus ? "-" : "";
  // �������̏���
  std::string integer = "";
  if (next_token == TokenType::kNumber)
  {
    do
    {
      integer += **p;
      EatToken(p);
      next_token = CheckNextToken(p);
    } while (next_token == TokenType::kNumber);
  }
  // �������̏���
  std::string fractional = "";
  if (next_token == TokenType::kDot)
  {
    EatToken(p);
    next_token = CheckNextToken(p);
    if (next_token == TokenType::kNumber)
    {
      do
      {
        fractional += **p;
        EatToken(p);
        next_token = CheckNextToken(p);
      } while (next_token == TokenType::kNumber);
    }
  }
  (*dest) = std::strtof((sign + integer + "." + fractional).c_str(), NULL);
  return true;
}

/*!
 * @brief Name�̃p�[�X
 * @return false�Ȃ玸�s
 */
bool ParseName(const char** p, ShaderData* dest)
{
  return ParseText(p, &dest->name_);
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
  if (!ParseIdentifier(p, &property_id)) return false;
  if (!GetToken(p, TokenType::kParenBegin)) return false;
  if (!ParseText(p, &property_name)) return false;
  if (!GetToken(p, TokenType::kComma)) return false;
  if (!ParseSpecialIdentifier(p, &property_type)) return false;
  using namespace GGGShaderParser;
  if (property_type == "Range")
  {
    ScalaPropertyData data;
    if (!GetToken(p, TokenType::kParenBegin)) return false;
    if (!ParseFloat(p, &data.min_value_)) return false;
    if (!GetToken(p, TokenType::kComma)) return false;
    if (!ParseFloat(p, &data.max_value_)) return false;
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    if (!GetToken(p, TokenType::kEqual)) return false;
    if (!ParseFloat(p, &data.init_value_)) return false;
    data.name_ = property_id;
    data.display_name_ = property_name;
    data.variable_type_ = static_cast<T_FIXED_UINT8>(Shader::VariableType::kFloat);
    dest->scala_properties_.emplace_back(data);
    return true;
  }
  if (property_type == "Float")
  {
    ScalaPropertyData data;
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    if (!GetToken(p, TokenType::kEqual)) return false;
    if (!ParseFloat(p, &data.init_value_)) return false;
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
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    if (!GetToken(p, TokenType::kEqual)) return false;
    if (!ParseInt(p, &data.init_value_)) return false;
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
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    if (!GetToken(p, TokenType::kEqual)) return false;
    if (!GetToken(p, TokenType::kBlockBegin)) return false;
    // {}�̏ꍇ�͂��ׂ�0�A�@���l�������Ă��ꍇ�͐��l��ǂݎ��
    if (CheckNextToken(p) != TokenType::kBlockEnd)
    {
      if (!ParseFloat(p, &data.init_value0_)) return false;
      if (!GetToken(p, TokenType::kComma)) return false;
      if (!ParseFloat(p, &data.init_value1_)) return false;
      if (!GetToken(p, TokenType::kComma)) return false;
      if (!ParseFloat(p, &data.init_value2_)) return false;
      if (!GetToken(p, TokenType::kComma)) return false;
      if (!ParseFloat(p, &data.init_value3_)) return false;
      if (!GetToken(p, TokenType::kBlockEnd)) return false;
    }
    else
    {
      EatToken(p);
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
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    if (!GetToken(p, TokenType::kEqual)) return false;
    if (!GetToken(p, TokenType::kBlockBegin)) return false;
    // {}�̏ꍇ�͂��ׂ�1�A�@���l�������Ă��ꍇ�͐��l��ǂݎ��
    if (CheckNextToken(p) != TokenType::kBlockEnd)
    {
      if (!ParseFloat(p, &data.init_r_)) return false;
      if (!GetToken(p, TokenType::kComma)) return false;
      if (!ParseFloat(p, &data.init_g_)) return false;
      if (!GetToken(p, TokenType::kComma)) return false;
      if (!ParseFloat(p, &data.init_b_)) return false;
      if (!GetToken(p, TokenType::kComma)) return false;
      if (!ParseFloat(p, &data.init_a_)) return false;
      if (!GetToken(p, TokenType::kBlockEnd)) return false;
    }
    else
    {
      EatToken(p);
    }
    data.name_ = property_id;
    data.display_name_ = property_name;
    dest->color_properties_.emplace_back(data);
    return true;
  }
  if (property_type == "2D")
  {
    std::string init_tex;
    if (!GetToken(p, TokenType::kParenEnd)) return false;
    if (!GetToken(p, TokenType::kEqual)) return false;
    if (!ParseText(p, &init_tex)) return false;
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

/*!
 * @brief Properties�̃p�[�X
 * @return false�Ȃ玸�s
 */
bool ParseProperties(const char** p, ShaderData* dest)
{
  if (!GetToken(p, TokenType::kBlockBegin)) return false;
  while (CheckNextToken(p) != TokenType::kBlockEnd)
  {
    if (!ParseProperty(p, dest))
    {
      return false;
    }
  }
  if (!GetToken(p, TokenType::kBlockEnd)) return false;
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
  if (!ParseIdentifier(p, &tag_type)) return false;
  if (!ParseIdentifier(p, &tag_value)) return false;
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
  while (CheckNextToken(p) != TokenType::kBlockEnd)
  {
    if (!ParseTag(p, dest))
    {
      return false;
    }
  }   
  EatToken(p);
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
  if (!ParseIdentifier(p, &tag)) return false;
  if (tag == "Ref")
  {
    T_FLOAT value = 0.0f;
    if (!ParseInt(p, &value)) return false;
    dest->stencil_ref_ = (T_FIXED_UINT8)value;
    return true;
  }
  if (tag == "ReadMask")
  {
    T_FLOAT value = 0.0f;
    if (!ParseInt(p, &value)) return false;
    dest->stencil_read_mask_ = (T_FIXED_UINT8)value;
    return true;
  }
  if (tag == "WriteMask")
  {
    T_FLOAT value = 0.0f;
    if (!ParseInt(p, &value)) return false;
    dest->stencil_write_mask_ = (T_FIXED_UINT8)value;
    return true;
  }
  std::string value = "";
  if (!ParseIdentifier(p, &value)) return false;
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
bool ParsePassData(const char** p, HLSLCompiler* compiler, const ShaderData& data, PassData* dest)
{
  std::string identifier = "";
  if (!ParseIdentifier(p, &identifier)) return false;

  using namespace GGGShaderParser;
  if (identifier == "LightMode")
  {
    std::string value = "";
    if (!ParseIdentifier(p, &value)) return false;
    dest->light_mode_ = ParseLightMode(value);
    return true;
  }
  if (identifier == "Cull")
  {
    std::string value = "";
    if (!ParseIdentifier(p, &value)) return false;
    dest->render_state_data_.cull_mode_ = ParseCullMode(value);
    return true;
  }
  if (identifier == "ZWrite")
  {
    std::string value = "";
    if (!ParseIdentifier(p, &value)) return false;
    dest->render_state_data_.z_write_ = ParseZWrite(value);
    return true;
  }
  if (identifier == "ZTest")
  {
    std::string value = "";
    if (!ParseIdentifier(p, &value)) return false;
    dest->render_state_data_.z_test_ = ParseComparasionFunc(value);
    return true;
  }
  if (identifier == "Blend")
  {
    T_INT8 state_index = -1;
    // �����_�[�^�[�Q�b�g�w�肪�������ꍇ
    if (CheckNextToken(p) == TokenType::kNumber)
    {
      T_FLOAT value = 0.0f;
      if (!ParseInt(p, &value)) return false;
      state_index = (T_INT8)value;
    }
    std::string value = "";
    if (!ParseIdentifier(p, &value)) return false;
    // �u�����h�X�e�[�g�𖳌��ɂ���
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
    if (!ParseIdentifier(p, &value)) return false;
    T_INT32 src_factor = ParseBlendFactor(value);
    T_INT32 dst_factor = ParseBlendFactor(value);
    T_INT32 asrc_factor = src_factor;
    T_INT32 adst_factor = dst_factor;
    // �A���t�@��Factor�w�肪�������ꍇ
    if (CheckNextToken(p) == TokenType::kComma)
    {
      EatToken(p);
      if (!ParseIdentifier(p, &value)) return false;
      asrc_factor = ParseBlendFactor(value);
      if (!ParseIdentifier(p, &value)) return false;
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
    // �����_�[�^�[�Q�b�g�w�肪�������ꍇ
    if (CheckNextToken(p) == TokenType::kNumber)
    {
      T_FLOAT value = 0.0f;
      if (!ParseInt(p, &value)) return false;
      state_index = (T_INT8)value;
    }
    std::string value = "";
    if (!ParseIdentifier(p, &value)) return false;
    T_INT32 color_op = ParseBlendOp(value);
    T_INT32 alpha_op = color_op;
    // �A���t�@��Factor�w�肪�������ꍇ
    if (CheckNextToken(p) == TokenType::kComma)
    {
      EatToken(p);
      if (!ParseIdentifier(p, &value)) return false;
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
    return true;
  }
  if (identifier == "Stencil")
  {
    dest->render_state_data_.stencil_state_data_.enabled_ = true;
    if (!GetToken(p, TokenType::kBlockBegin)) return false;
    while (CheckNextToken(p) != TokenType::kBlockEnd)
    {
      if (!ParseStencilData(p, &dest->render_state_data_.stencil_state_data_))
      {
        return false;
      }
    }
    EatToken(p);
    return true;
  }
  if (identifier == "CODE_BEGIN")
  {
    std::string end_simbol = "CODE_END";
    std::string program = "";
    while (program.find(end_simbol) == std::string::npos)
    {
      program += (**p);
      ++(*p);
    }
    program.replace(program.length() - end_simbol.length(), end_simbol.length(), "");
    compiler->ConvertHLSL(data, &program);
    compiler->CompileVertexShader(program, &dest->vs_byte_code_);
    compiler->CompilePixelShader(program, &dest->ps_byte_code_);
    return true;
  }
  return false;
}

/*!
 * @brief Pass�̃p�[�X
 * @return false�Ȃ玸�s
 */
bool ParsePass(const char** p, HLSLCompiler* compiler, ShaderData* dest, bool grab)
{
  if (!GetToken(p, TokenType::kBlockBegin)) return false;
  PassData pass_data = PassData();
  while (CheckNextToken(p) != TokenType::kBlockEnd)
  {
    if (!ParsePassData(p, compiler, *dest, &pass_data))
    {
      return false;
    }
  }
  EatToken(p);
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
  while (CheckNextToken(p) != TokenType::kBlockEnd)
  {
    EatToken(p);
  }
  EatToken(p);
  return true;
}

void ShaderCompiler::Parse(const std::string& str, HLSLCompiler* compiler, ShaderData* dest)
{
  const char* p = str.c_str();
  
  bool grab = false;
  while (CheckNextToken(&p) != TokenType::kEOF)
  {
    std::string token = "";
    if (!ParseIdentifier(&p, &token))
    {
      // �G���[
      break;
    }
    if (token == "Shader")
    {
      ParseName(&p, dest);
      continue;
    }
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
