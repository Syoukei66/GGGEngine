#pragma once

namespace Shader
{

static const char* MAIN_TEXTURE_NAME = "_MainTex";

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
  kNever,

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

static size_t GetVariableTypeSize(VariableType type)
{
  switch (type)
  {
  case Shader::VariableType::kBool:
    return sizeof(bool);
  case Shader::VariableType::kInt:
    return sizeof(T_FIXED_INT32);
  case Shader::VariableType::kUint:
    return sizeof(T_FIXED_UINT32);
  case Shader::VariableType::kFloat:
    return sizeof(T_FIXED_FLOAT);
  case Shader::VariableType::kColor:
    return sizeof(T_FIXED_FLOAT) * 4;
  }
  return 0;
}

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
  kBump,

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
  kTimeBuiltin,
  kProperty,

  DATANUM,
};

/*!
 * @brief テクスチャのフィルタリングモード
 */
enum class TextureFilter : T_FIXED_UINT8
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
enum class TextureAddress : T_FIXED_UINT8
{
  kWrap,
  kMirror,
  kClamp,
  kBorder,
  kMirrorOnce,

  DATANUM,
};

/*!
 * @brief テクスチャの次元
 */
enum class TextureDimension : T_FIXED_UINT8
{
  kTex2D,
  kTex3D,
  kCube,

  DATANUM,
};

/*!
 * @brief テクスチャのフォーマット
 */
enum class TextureFormat : T_FIXED_UINT8
{
  kRGB,
  kRGB_Compressed,
  kRGB_HighQualityCompressed,
  kRGBA,
  kRGBA_Compressed,
  kRGBA_HighQualityCompressed,
  kHDR,
  kHDR_Compressed,
  kHDR_HighQualityCompressed,
  kDepth,
  kDepth_Low,
  kDepthStencil,
  kDepthStencil_Low,
  kHeightMap,
  kHeightMap_Low,
  kHeightMap_High,

  DATANUM,
};

/*!
 * @brief テクスチャのフォーマットからピクセル当たりのサイズを計算
 */
static T_FIXED_UINT8 GetBytePerPixel(Shader::TextureFormat type)
{
  switch (type)
  {
  case Shader::TextureFormat::kHeightMap_Low:
    return 1;

  case Shader::TextureFormat::kDepth_Low:
  case Shader::TextureFormat::kHeightMap:
    return 2;

  case Shader::TextureFormat::kRGB:
  case Shader::TextureFormat::kRGB_Compressed:
    return 3;

  case Shader::TextureFormat::kRGBA:
  case Shader::TextureFormat::kRGBA_Compressed:
  case Shader::TextureFormat::kDepth:
  case Shader::TextureFormat::kDepthStencil_Low:
  case Shader::TextureFormat::kHeightMap_High:
    return 4;

  case Shader::TextureFormat::kDepthStencil:
    return 8;

  case Shader::TextureFormat::kHDR:
  case Shader::TextureFormat::kHDR_Compressed:
    return 12;
  }
  return 0;
}

/*!
 * @brief マテリアルのプロパティのタイプ
 */
enum class MaterialPropertyType : T_FIXED_UINT8
{
  kBool,
  kInt,
  kUint,
  kFloat,
  kColor,
  kTexture,

  DATANUM,
};

static MaterialPropertyType GetMaterialPropertyType(VariableType type)
{
  switch (type)
  {
  case Shader::VariableType::kBool:
    return MaterialPropertyType::kBool;
  case Shader::VariableType::kInt:
    return MaterialPropertyType::kInt;
  case Shader::VariableType::kUint:
    return MaterialPropertyType::kUint;
  case Shader::VariableType::kFloat:
    return MaterialPropertyType::kFloat;
  case Shader::VariableType::kColor:
    return MaterialPropertyType::kColor;
  }
  return MaterialPropertyType::DATANUM;
}

static size_t GetMaterialPropertySize(MaterialPropertyType type)
{
  switch (type)
  {
  case Shader::MaterialPropertyType::kBool:
    return sizeof(bool);
  case Shader::MaterialPropertyType::kInt:
    return sizeof(T_FIXED_INT32);
  case Shader::MaterialPropertyType::kUint:
    return sizeof(T_FIXED_UINT32);
  case Shader::MaterialPropertyType::kFloat:
    return sizeof(T_FIXED_FLOAT);
  case Shader::MaterialPropertyType::kColor:
    return sizeof(TColor);
  }
  return 0;
}

/*!
 * @brief 引数で与えられたバッファサイズを
 * アライメントを考慮した値に変換する
 */
static T_UINT32 AlignmentBufferSize(T_UINT32 size)
{
  if (size % 16 != 0)
  {
    size += 16 - size % 16;
  }
  return size;
}

/*!
 * @brief アライメントを考慮してバッファを進める
 */
static T_UINT32 AlignmentBufferBegin(T_UINT32 current, T_UINT32 move)
{
  // sizeが16の倍数のデータが与えられた時アライメント処理を行う
  if (move % 16 == 0)
  {
    current = AlignmentBufferSize(current);
  }
  return current;
}

} // namespace Shader