#pragma once

#include <Asset/Shader/Shader.h>
#include <Core/Constants/ShaderUtils.h>

namespace GGGShaderParser
{

#define SHADER_TOKEN_PARSER(Name)\
T_INT32 Parse##Name(const std::string& token)\
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
 * @brief 組み込み変数
 */
const char* BuiltinVariableTokens[static_cast<T_FIXED_UINT8>(Shader::BuiltinVariable::DATANUM)] =
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
 * @brief パスのライトモード
 */
const char* LightModeTokens[static_cast<T_FIXED_UINT8>(Shader::LightMode::DATANUM)] =
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
 * @brief カリングモード
 */
const char* CullModeTokens[static_cast<T_FIXED_UINT8>(Shader::CullMode::DATANUM)] =
{
  "Back",
  "Front",
  "Off",
};

SHADER_TOKEN_PARSER(CullMode);

/*!
 * @brief Zバッファ書き込みモード
 */
const char* ZWriteTokens[static_cast<T_FIXED_UINT8>(Shader::ZWrite::DATANUM)] =
{
  "On",
  "Off",
};

SHADER_TOKEN_PARSER(ZWrite);

/*!
 * @brief Zバッファ書き込みモード
 */
const char* ComparasionFuncTokens[static_cast<T_FIXED_UINT8>(Shader::ComparasionFunc::DATANUM)] =
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
 * @brief ブレンドモード係数
 */
const char* BlendFactorTokens[static_cast<T_FIXED_UINT8>(Shader::BlendFactor::DATANUM)] =
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
 * @brief ブレンドモード演算子
 */
const char* BlendOpTokens[static_cast<T_FIXED_UINT8>(Shader::BlendOp::DATANUM)] =
{
  "Add",
  "Sub",
  "RevSub",
  "Min",
  "Max",
};

SHADER_TOKEN_PARSER(BlendOp);

/*!
 * @brief ステンシルテスト通過時の操作
 */
const char* StencilOperationTokens[static_cast<T_FIXED_UINT8>(Shader::StencilOperation::DATANUM)] =
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
 * @brief 変数のタイプ
 */
const char* VariableTypeTokens[static_cast<T_FIXED_UINT8>(Shader::VariableType::DATANUM)] =
{
  "bool",
  "int",
  "uint",
  "float",
  "color",
};

SHADER_TOKEN_PARSER(VariableType);

/*!
 * @brief カラーのタイプ
 */
const char* ColorTypeTokens[static_cast<T_FIXED_UINT8>(Shader::ColorType::DATANUM)] =
{
  "Color",
  "ColorHDR",
};

SHADER_TOKEN_PARSER(ColorType);

/*!
 * @brief サンプラーのタイプ
 */
const char* SamplerTypeTokens[static_cast<T_FIXED_UINT8>(Shader::SamplerType::DATANUM)] =
{
  "sampler2D",
  "samplerCube",
  "sampler3D",
};

SHADER_TOKEN_PARSER(SamplerType);

/*!
 * @brief デフォルトテクスチャのタイプ
 */
const char* DefaultTextureTypeTokens[static_cast<T_FIXED_UINT8>(Shader::DefaultTextureType::DATANUM)] =
{
  "white",
  "black",
  "gray",
};

SHADER_TOKEN_PARSER(DefaultTextureType);

/*!
 * @brief RenderQueueのタイプ
 */
const char* RenderQueueTokens[static_cast<T_FIXED_UINT8>(Shader::RenderQueue::DATANUM)] =
{
  "BackGround",
  "Geometry",
  "AlphaTest",
  "Transparent",
  "Overlay",
};

SHADER_TOKEN_PARSER(RenderQueue);

/*!
 * @brief 描画タイプ
 */
const char* RenderTypeTokens[static_cast<T_FIXED_UINT8>(Shader::RenderType::DATANUM)] =
{
  "Opaque",
  "Transparent",
  "TransparentCutout",
  "Background",
  "Overlay",
};

SHADER_TOKEN_PARSER(RenderType);




void ParseTag(PassData& data)
{
}

}
