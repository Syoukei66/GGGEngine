#pragma once

namespace Shader
{
/*!
 * @brief 組み込み変数
 */
enum class BuiltinVariable : T_FIXED_UINT8
{
  kMatrix_MVP,
  kMatrix_MV,
  kMatrix_V,
  kMatrix_P,
  kMatrix_ObjToWorld,
  kMatrix_WorldToObj,

  kMatrix_Time,
  kMatrix_SinTime,
  kMatrix_CosTime,
  kMatrix_DeltaTime,

  DATANUM,
};

/*!
 * @brief パスのライトモード
 */
enum class LightMode : T_FIXED_UINT8
{
  kAlways,
  kForwardBase,
  kForwardAdd,
  kDeferred,
  kShadowCaster,
  kMotionVector,

  DATANUM,
};

/*!
 * @brief カリングモード
 */
enum class CullMode : T_FIXED_UINT8
{
  kBack,
  kFront,
  kOff,

  DATANUM,
};

/*!
 * @brief Zバッファ書き込みモード
 */
enum class ZWrite : T_FIXED_UINT8
{
  kOn,
  kOff,

  DATANUM,
};

/*!
 * @brief 比較関数
 */
enum class ComparasionFunc : T_FIXED_UINT8
{
  kLess,
  kGreater,
  kLEqual,
  kGEqual,
  kEqual,
  kNotEqual,
  kAlways,

  DATANUM,
};

/*!
 * @brief ブレンドモード係数
 */
enum class BlendFactor : T_FIXED_UINT8
{
  kOne,
  kZero,
  kSrcColor,
  kSrcAlpha,
  kDstColor,
  kDstAlpha,
  kInvSrcColor,
  kInvSrcAlpha,
  kInvDstColor,
  kInvDstAlpha,

  DATANUM,
};

/*!
 * @brief ブレンドモード演算子
 */
enum class BlendOp : T_FIXED_UINT8
{
  kAdd,
  kSub,
  kRevSub,
  kMin,
  kMax,

  DATANUM,
};

/*!
 * @brief ステンシルテスト通過時の操作
 */
enum class StencilOperation : T_FIXED_UINT8
{
  kKeep,
  kZero,
  kReplace,
  kIncrSaturate,
  kDecrSaturate,
  kInvert,
  kIncrWrap,
  kDecrWrap,

  DATANUM,
};

/*!
 * @brief 変数のタイプ
 */
enum class VariableType : T_FIXED_UINT8
{
  kBool,
  kInt,
  kUint,
  kFloat,
  kColor,

  DATANUM,
};

/*!
 * @brief 変数のタイプ
 */
enum class ColorType : T_FIXED_UINT8
{
  kColor,
  kColorHDR,

  DATANUM,
};

/*!
 * @brief サンプラーのタイプ
 */
enum class SamplerType : T_FIXED_UINT8
{
  kSampler2D,
  kSamplerCube,
  kSampler3D,

  DATANUM,
};

/*!
 * @brief デフォルトテクスチャのタイプ
 */
enum class DefaultTextureType : T_FIXED_UINT8
{
  kWhite,
  kBlack,
  kGray,

  DATANUM,
};

/*!
 * @brief RenderQueueのタイプ
 */
enum class RenderQueue : T_FIXED_UINT8
{
  kBackGround,
  kGeometry,
  kAlphaTest,
  kTransparent,
  kOverlay,

  DATANUM,
};

/*!
 * @brief 描画タイプ
 */
enum class RenderType : T_FIXED_UINT8
{
  kOpaque,
  kTransparent,
  kTransparentCutout,
  kBackground,
  kOverlay,

  DATANUM,
};

/*!
 * @brief コンスタントバッファのID
 */
enum class ConstantBufferId : T_FIXED_UINT8
{
  kRendererBuiltin,
  kRenderStateBuiltin,
  kProperty,

  DATANUM,
};

/*!
 * @brief テクスチャのフィルタリングモード
 */
enum class TextureFilter
{
  kPoint,
  kBilinear,
  kTrilinear,

  DATANUM,
};

/*!
 * @brief テクスチャのアドレッシングモード。
 * 0~1の範囲外のUV座標をどう処理するか
 */
enum class TextureAddress
{
  kWrap,
  kMirror,
  kClamp,
  kBorder,
  kMirrorOnce,

  DATANUM,
};

} // namespace Shader