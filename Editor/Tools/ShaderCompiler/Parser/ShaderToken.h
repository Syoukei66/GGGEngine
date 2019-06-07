#pragma once

#include <Asset/Shader/Shader.h>
#include <Core/Constants/ShaderUtils.h>

namespace GGGShaderParser
{
/*!
 * @brief 組み込み変数
 */
static const std::string BuiltinVariableTokens[static_cast<T_FIXED_UINT8>(Shader::BuiltinVariable::DATANUM)] =
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

/*!
 * @brief パスのライトモード
 */
static const std::string LightModeTokens[static_cast<T_FIXED_UINT8>(Shader::LightMode::DATANUM)] =
{
  "Always",
  "ForwardBase",
  "ForwardAdd",
  "Deferred",
  "ShadowCaster",
  "MotionVector",
};

/*!
 * @brief カリングモード
 */
static const std::string CullModeTokens[static_cast<T_FIXED_UINT8>(Shader::CullMode::DATANUM)] =
{
  "Back",
  "Front",
  "Off",
};

/*!
 * @brief Zバッファ書き込みモード
 */
static const std::string ZWriteTokens[static_cast<T_FIXED_UINT8>(Shader::ZWrite::DATANUM)] =
{
  "On",
  "Off",
};

/*!
 * @brief Zバッファ書き込みモード
 */
static const std::string ComparasionFuncTokens[static_cast<T_FIXED_UINT8>(Shader::ComparasionFunc::DATANUM)] =
{
  "Less",
  "Greater",
  "LEqual",
  "GEqual",
  "Equal",
  "NotEqual",
  "Always",
  "Never",
};

/*!
 * @brief ブレンドモード係数
 */
static const std::string BlendFactorTokens[static_cast<T_FIXED_UINT8>(Shader::BlendFactor::DATANUM)] =
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

/*!
 * @brief ブレンドモード演算子
 */
static const std::string BlendOpTokens[static_cast<T_FIXED_UINT8>(Shader::BlendOp::DATANUM)] =
{
  "Add",
  "Sub",
  "RevSub",
  "Min",
  "Max",
};

/*!
 * @brief ステンシルテスト通過時の操作
 */
static const std::string StencilOperationTokens[static_cast<T_FIXED_UINT8>(Shader::StencilOperation::DATANUM)] =
{
  "Keep",
  "Zero",
  "Replace",
  "IncrSat",
  "DecrSat",
  "Invert",
  "IncrWrap",
  "DecrWrap",
};

/*!
 * @brief 変数のタイプ
 */
static const std::string VariableTypeTokens[static_cast<T_FIXED_UINT8>(Shader::VariableType::DATANUM)] =
{
  "bool",
  "int",
  "uint",
  "float",
  "color",
};

/*!
 * @brief カラーのタイプ
 */
static const std::string ColorTypeTokens[static_cast<T_FIXED_UINT8>(Shader::ColorType::DATANUM)] =
{
  "Color",
  "ColorHDR",
};

/*!
 * @brief サンプラーのタイプ
 */
static const std::string SamplerTypeTokens[static_cast<T_FIXED_UINT8>(Shader::SamplerType::DATANUM)] =
{
  "sampler2D",
  "samplerCube",
  "sampler3D",
};

/*!
 * @brief デフォルトテクスチャのタイプ
 */
static const std::string DefaultTextureTypeTokens[static_cast<T_FIXED_UINT8>(Shader::DefaultTextureType::DATANUM)] =
{
  "white",
  "black",
  "gray",
  "bump",
};

/*!
 * @brief RenderQueueのタイプ
 */
static const std::string RenderQueueTokens[static_cast<T_FIXED_UINT8>(Shader::RenderQueue::DATANUM)] =
{
  "BackGround",
  "Geometry",
  "AlphaTest",
  "Transparent",
  "Overlay",
};

/*!
 * @brief 描画タイプ
 */
static const std::string RenderTypeTokens[static_cast<T_FIXED_UINT8>(Shader::RenderType::DATANUM)] =
{
  "Opaque",
  "Transparent",
  "TransparentCutout",
  "Background",
  "Overlay",
};
}
