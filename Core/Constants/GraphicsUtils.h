#pragma once

namespace Graphics
{

/*!
 * @brief RenderBufferのピクセルフォーマット
 */
enum class PixelFormat : T_UINT32
{
  FORMAT_D16,
  FORMAT_D24S8,
  FORMAT_D32,
  FORMAT_R8G8B8A8,
  FORMAT_R16G16B16A16,
  FORMAT_R16G16B16A16F,

  FORMAT_DATANUM,
};

/*!
 * @brief RenderQueueの一覧
 */
enum RenderQueue
{
  RQ_GEOMETRY_BEGIN,

  RQ_BACKGROUND = RQ_GEOMETRY_BEGIN,
  RQ_GEOMETRY,
  RQ_ALPHA_TEST,
  RQ_GEOMETRY_LAST,

  RQ_TRANSPARENT = RQ_GEOMETRY_LAST,
  RQ_TRANSPARENT_LAST,

  RQ_OVERLAY,

  RQ_DATANUM,
};

/*!
 * @brief ブレンドモード
 */
enum BlendMode
{
  BL_ZERO,
  BL_ONE,
  BL_SRCCLR,
  BL_INVSRCCLR,
  BL_SRCALPHA,
  BL_INVSRCALPHA,
  BL_DSTCLR,
  BL_INVDSTCLR,
  BL_DSTALPHA,
  BL_INVDSTALPHA,
  BL_NOBLEND,

  BL_DATANUM = BL_NOBLEND,
};

static const BlendMode BLEND_DEFAULT_SRC = BL_SRCALPHA;
static const BlendMode BLEND_DEFAULT_DST = BL_INVSRCALPHA;

static const BlendMode BLEND_ADD_SRC = BL_SRCALPHA;
static const BlendMode BLEND_ADD_DST = BL_ONE;

static const BlendMode BLEND_SUB_SRC = BL_SRCALPHA;
static const BlendMode BLEND_SUB_DST = BL_ONE;

static const BlendMode BLEND_MUL_SRC = BL_DSTCLR;
static const BlendMode BLEND_MUL_DST = BL_INVSRCALPHA;

static const BlendMode BLEND_SCREEN_SRC = BL_ONE;
static const BlendMode BLEND_SCREEN_DST = BL_INVSRCALPHA;

}