#pragma once

namespace Shader
{

static const char* MAIN_TEXTURE_NAME = "_MainTex";

/*!
 * @brief �g�ݍ��ݕϐ�
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
 * @brief �p�X�̃��C�g���[�h
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
 * @brief �J�����O���[�h
 */
enum class CullMode : T_FIXED_UINT8
{
  kBack,
  kFront,
  kOff,

  DATANUM,
};

/*!
 * @brief Z�o�b�t�@�������݃��[�h
 */
enum class ZWrite : T_FIXED_UINT8
{
  kOn,
  kOff,

  DATANUM,
};

/*!
 * @brief ��r�֐�
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
 * @brief �u�����h���[�h�W��
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
 * @brief �u�����h���[�h���Z�q
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
 * @brief �X�e���V���e�X�g�ʉߎ��̑���
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
 * @brief �ϐ��̃^�C�v
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
 * @brief �ϐ��̃^�C�v
 */
enum class ColorType : T_FIXED_UINT8
{
  kColor,
  kColorHDR,

  DATANUM,
};

/*!
 * @brief �T���v���[�̃^�C�v
 */
enum class SamplerType : T_FIXED_UINT8
{
  kSampler2D,
  kSamplerCube,
  kSampler3D,

  DATANUM,
};

/*!
 * @brief �f�t�H���g�e�N�X�`���̃^�C�v
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
 * @brief RenderQueue�̃^�C�v
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
 * @brief �`��^�C�v
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
 * @brief �R���X�^���g�o�b�t�@��ID
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
 * @brief �e�N�X�`���̃t�B���^�����O���[�h
 */
enum class TextureFilter : T_FIXED_UINT8
{
  kPoint,
  kBilinear,
  kTrilinear,

  DATANUM,
};

/*!
 * @brief �e�N�X�`���̃A�h���b�V���O���[�h�B
 * 0~1�͈̔͊O��UV���W���ǂ��������邩
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
 * @brief �e�N�X�`���̎���
 */
enum class TextureDimension : T_FIXED_UINT8
{
  kTex2D,
  kTex3D,
  kCube,

  DATANUM,
};

/*!
 * @brief �e�N�X�`���̃t�H�[�}�b�g
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
 * @brief �e�N�X�`���̃t�H�[�}�b�g����s�N�Z��������̃T�C�Y���v�Z
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
 * @brief �}�e���A���̃v���p�e�B�̃^�C�v
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
 * @brief �����ŗ^����ꂽ�o�b�t�@�T�C�Y��
 * �A���C�����g���l�������l�ɕϊ�����
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
 * @brief �A���C�����g���l�����ăo�b�t�@��i�߂�
 */
static T_UINT32 AlignmentBufferBegin(T_UINT32 current, T_UINT32 move)
{
  // size��16�̔{���̃f�[�^���^����ꂽ���A���C�����g�������s��
  if (move % 16 == 0)
  {
    current = AlignmentBufferSize(current);
  }
  return current;
}

} // namespace Shader