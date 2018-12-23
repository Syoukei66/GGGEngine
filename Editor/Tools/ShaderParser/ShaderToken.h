#pragma once

#include <Asset/Shader/Shader.h>
#include <Core/Constants/ShaderUtils.h>

namespace GGGShaderParser
{

#define SHADER_TOKEN_PARSER(Name)\
static T_INT32 Parse##Name(const std::string& token)\
{\
  for (T_FIXED_UINT8 i = 0; i < static_cast<T_FIXED_UINT8>(Shader::##Name##::DATANUM); ++i)\
  {\
    if (token == Name##Tokens[i])\
    {\
      return i;\
    }\
  }\
  return -1;\
}

/*!
 * @brief �g�ݍ��ݕϐ�
 */
const std::string BuiltinVariableTokens[static_cast<T_FIXED_UINT8>(Shader::BuiltinVariable::DATANUM)] =
{
  "_MatMVP",
  "_MatMV",
  "_MatV",
  "_MatP",
  "_ObjToWorld",
  "_WorldToObj",

  "_Time",
  "_SinTime",
  "_CosTime",
  "_DeltaTime",
};

SHADER_TOKEN_PARSER(BuiltinVariable);

/*!
 * @brief �p�X�̃��C�g���[�h
 */
const std::string LightModeTokens[static_cast<T_FIXED_UINT8>(Shader::LightMode::DATANUM)] =
{
  "Always",
  "ForwardBase",
  "ForwardAdd",
  "Deferred",
  "ShadowCaster",
  "MotionVector",
};

SHADER_TOKEN_PARSER(LightMode);

/*!
 * @brief �J�����O���[�h
 */
const std::string CullModeTokens[static_cast<T_FIXED_UINT8>(Shader::CullMode::DATANUM)] =
{
  "Back",
  "Front",
  "Off",
};

SHADER_TOKEN_PARSER(CullMode);

/*!
 * @brief Z�o�b�t�@�������݃��[�h
 */
const std::string ZWriteTokens[static_cast<T_FIXED_UINT8>(Shader::ZWrite::DATANUM)] =
{
  "On",
  "Off",
};

SHADER_TOKEN_PARSER(ZWrite);

/*!
 * @brief Z�o�b�t�@�������݃��[�h
 */
const std::string ComparasionFuncTokens[static_cast<T_FIXED_UINT8>(Shader::ComparasionFunc::DATANUM)] =
{
  "Less",
  "Greater",
  "kLEqual",
  "kGEqual",
  "kEqual",
  "kNotEqual",
  "kAlways",
};

SHADER_TOKEN_PARSER(ComparasionFunc);

/*!
 * @brief �u�����h���[�h�W��
 */
const std::string BlendFactorTokens[static_cast<T_FIXED_UINT8>(Shader::BlendFactor::DATANUM)] =
{
  "One",
  "Zero",
  "SrcColor",
  "SrcAlpha",
  "DstColor",
  "DstAlpha",
  "InvSrcColor",
  "InvSrcAlpha",
  "InvDstColor",
  "InvDstAlpha",
};

SHADER_TOKEN_PARSER(BlendFactor);

/*!
 * @brief �u�����h���[�h���Z�q
 */
const std::string BlendOpTokens[static_cast<T_FIXED_UINT8>(Shader::BlendOp::DATANUM)] =
{
  "Add",
  "Sub",
  "RevSub",
  "Min",
  "Max",
};

SHADER_TOKEN_PARSER(BlendOp);

/*!
 * @brief �X�e���V���e�X�g�ʉߎ��̑���
 */
const std::string StencilOperationTokens[static_cast<T_FIXED_UINT8>(Shader::StencilOperation::DATANUM)] =
{
  "Keep",
  "Zero",
  "Replace",
  "IncrSaturate",
  "DecrSaturate",
  "Invert",
  "IncrWrap",
  "DecrWrap",
};

SHADER_TOKEN_PARSER(StencilOperation);

/*!
 * @brief �ϐ��̃^�C�v
 */
const std::string VariableTypeTokens[static_cast<T_FIXED_UINT8>(Shader::VariableType::DATANUM)] =
{
  "bool",
  "int",
  "uint",
  "float",
  "color",
};

SHADER_TOKEN_PARSER(VariableType);

/*!
 * @brief �J���[�̃^�C�v
 */
const std::string ColorTypeTokens[static_cast<T_FIXED_UINT8>(Shader::ColorType::DATANUM)] =
{
  "Color",
  "ColorHDR",
};

SHADER_TOKEN_PARSER(ColorType);

/*!
 * @brief �T���v���[�̃^�C�v
 */
const std::string SamplerTypeTokens[static_cast<T_FIXED_UINT8>(Shader::SamplerType::DATANUM)] =
{
  "sampler2D",
  "samplerCube",
  "sampler3D",
};

SHADER_TOKEN_PARSER(SamplerType);

/*!
 * @brief �f�t�H���g�e�N�X�`���̃^�C�v
 */
const std::string DefaultTextureTypeTokens[static_cast<T_FIXED_UINT8>(Shader::DefaultTextureType::DATANUM)] =
{
  "white",
  "black",
  "gray",
};

SHADER_TOKEN_PARSER(DefaultTextureType);

/*!
 * @brief RenderQueue�̃^�C�v
 */
const std::string RenderQueueTokens[static_cast<T_FIXED_UINT8>(Shader::RenderQueue::DATANUM)] =
{
  "BackGround",
  "Geometry",
  "AlphaTest",
  "Transparent",
  "Overlay",
};

SHADER_TOKEN_PARSER(RenderQueue);

/*!
 * @brief �`��^�C�v
 */
const std::string RenderTypeTokens[static_cast<T_FIXED_UINT8>(Shader::RenderType::DATANUM)] =
{
  "Opaque",
  "Transparent",
  "TransparentCutout",
  "Background",
  "Overlay",
};

SHADER_TOKEN_PARSER(RenderType);

}
