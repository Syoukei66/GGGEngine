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

}