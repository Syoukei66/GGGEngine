#pragma once

#include "NativeType.h"

namespace GraphicsConstants
{

enum RenderQueue
{
  RQ_GEOMETRY_BEGIN,
  RQ_BACKGROUND = RQ_GEOMETRY_BEGIN,
  RQ_GEOMETRY,
  RQ_ALPHA_TEST,
  RQ_GEOMETRY_LAST,
  RQ_TRANSPARENT = RQ_GEOMETRY_LAST,
  RQ_OVERLAY,

  RQ_DATANUM,
};

enum TextureFormat
{
  TEX_FORMAT_D16,
  TEX_FORMAT_R8G8B8A8,
  TEX_FORMAT_R16G16B16A16,
  TEX_FORMAT_R16G16B16A16F,

  TEX_FORMAT_DATANUM,
};

enum VertexAttribute
{
  V_ATTR_POSITION = 1 << 0,
  V_ATTR_NORMAL = 1 << 1,
  V_ATTR_UV = 1 << 2,
  V_ATTR_UV2 = 1 << 3,
  V_ATTR_UV3 = 1 << 4,
  V_ATTR_UV4 = 1 << 5,
  V_ATTR_TANGENT = 1 << 6,
  V_ATTR_COLOR = 1 << 7,
  //V_ATTR_BINDPOSE = 1 << 8,
  //V_ATTR_BINDWEIGHT = 1 << 9,
  //V_ATTR_BOUND = 1 << 10,
};

enum { V_ATTR_DATANUM = 8 };

enum VertexFormat
{
  V_FORMAT_P = V_ATTR_POSITION,
  V_FORMAT_PN = V_ATTR_POSITION | V_ATTR_NORMAL,
  V_FORMAT_PU = V_ATTR_POSITION | V_ATTR_UV,
  V_FORMAT_PNU = V_ATTR_POSITION | V_ATTR_NORMAL | V_ATTR_UV,

  V_FORMAT_PC = V_ATTR_POSITION | V_ATTR_COLOR,
  V_FORMAT_PNC = V_ATTR_POSITION | V_ATTR_NORMAL | V_ATTR_COLOR,
  V_FORMAT_PUC = V_ATTR_POSITION | V_ATTR_UV | V_ATTR_COLOR,
  V_FORMAT_PNUC = V_ATTR_POSITION | V_ATTR_NORMAL | V_ATTR_UV | V_ATTR_COLOR,

  V_FORMAT_PNT = V_ATTR_POSITION | V_ATTR_NORMAL | V_ATTR_TANGENT,
  V_FORMAT_PNUT = V_ATTR_POSITION | V_ATTR_NORMAL | V_ATTR_UV | V_ATTR_TANGENT,
  V_FORMAT_PNTC = V_ATTR_POSITION | V_ATTR_NORMAL | V_ATTR_TANGENT | V_ATTR_COLOR,
  V_FORMAT_PNUTC = V_ATTR_POSITION | V_ATTR_NORMAL | V_ATTR_UV | V_ATTR_TANGENT | V_ATTR_COLOR,
};

static const T_UINT32 VERTEX_ATTRIBUTE_SIZE(T_UINT32 attr)
{
  static T_UINT32 SIZES[V_ATTR_DATANUM] =
  {
    sizeof(T_FLOAT) * 3,  // POSITION
    sizeof(T_FLOAT) * 3,  // NORMAL
    sizeof(T_FLOAT) * 2,  // UV
    sizeof(T_FLOAT) * 2,  // UV2
    sizeof(T_FLOAT) * 2,  // UV3
    sizeof(T_FLOAT) * 2,  // UV4
    sizeof(T_FLOAT) * 4,  // TANGENTS
    sizeof(T_UINT32),     // COLOR
  };
  T_UINT32 index = 0;
  while (attr > 1)
  {
    attr >>= 1;
    ++index;
  }
  return SIZES[index];
};

enum PrimitiveType
{
  PRIMITIVE_POINTS,
  PRIMITIVE_LINES,
  PRIMITIVE_LINESTRIP,
  PRIMITIVE_TRIANGLES,
  PRIMITIVE_TRIANGLESTRIP,
  PRIMITIVE_TRIANGLEFAN,

  PRIMITIVE_DATANUM,
};

static T_UINT32 PRIMITIVE_SURF_NUM(PrimitiveType type, T_UINT32 vertex_count)
{
  if (type == PRIMITIVE_POINTS)
  {
    return vertex_count;
  }
  if (type == PRIMITIVE_LINES)
  {
    return vertex_count;
  }
  if (type == PRIMITIVE_LINESTRIP)
  {
    return vertex_count;
  }
  if (type == PRIMITIVE_TRIANGLES)
  {
    return vertex_count / 3;
  }
  if (type == PRIMITIVE_TRIANGLESTRIP)
  {
    return vertex_count - 2;
  }
  if (type == PRIMITIVE_TRIANGLEFAN)
  {
    return vertex_count - 2;
  }
  return vertex_count;
}

}