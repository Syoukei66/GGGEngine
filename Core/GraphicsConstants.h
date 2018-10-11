#pragma once

#include "NativeType.h"
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Graphics
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
  V_ATTR_BONE_WEIGHTS = 1 << 8,
};

enum VertexAttrSize
{
  V_ATTRSIZE_POSITION = 3 * sizeof(T_FLOAT),
  V_ATTRSIZE_NORMAL = 3 * sizeof(T_FLOAT),
  V_ATTRSIZE_UV = 2 * sizeof(T_FLOAT),
  V_ATTRSIZE_UV2 = 2 * sizeof(T_FLOAT),
  V_ATTRSIZE_UV3 = 2 * sizeof(T_FLOAT),
  V_ATTRSIZE_UV4 = 2 * sizeof(T_FLOAT),
  V_ATTRSIZE_TANGENT = 4 * sizeof(T_FLOAT),
  V_ATTRSIZE_COLOR = 1 * sizeof(T_UINT32),
  V_ATTRSIZE_BONE_WEIGHTS = 8 * sizeof(T_FLOAT),
};

enum { V_ATTR_DATANUM = 8 };

static T_UINT32 CalcVertexSize(T_UINT32 format)
{
  T_UINT32 ret = 0;
  if (format & V_ATTR_POSITION)     ret += V_ATTRSIZE_POSITION;
  if (format & V_ATTR_NORMAL)       ret += V_ATTRSIZE_NORMAL;
  if (format & V_ATTR_UV)           ret += V_ATTRSIZE_UV;
  if (format & V_ATTR_UV2)          ret += V_ATTRSIZE_UV2;
  if (format & V_ATTR_UV3)          ret += V_ATTRSIZE_UV3;
  if (format & V_ATTR_UV4)          ret += V_ATTRSIZE_UV4;
  if (format & V_ATTR_TANGENT)      ret += V_ATTRSIZE_TANGENT;
  if (format & V_ATTR_COLOR)        ret += V_ATTRSIZE_COLOR;
  if (format & V_ATTR_BONE_WEIGHTS) ret += V_ATTRSIZE_BONE_WEIGHTS;
  return ret;
}

inline void SetVertexPosition(const TVec3f& pos, unsigned char** dest)
{
  T_FLOAT* p = (T_FLOAT*)(*dest);
  p[0] = pos.x;
  p[1] = pos.y;
  p[2] = pos.z;
  (*dest) += V_ATTRSIZE_POSITION;
}

inline void SetVertexNormal(const TVec3f& norm, unsigned char** dest)
{
  T_FLOAT* p = (T_FLOAT*)(*dest);
  p[0] = norm.x;
  p[1] = norm.y;
  p[2] = norm.z;
  (*dest) += V_ATTRSIZE_NORMAL;
}

inline void SetVertexUv(const TVec2f& uv, unsigned char** dest)
{
  T_FLOAT* p = (T_FLOAT*)(*dest);
  p[0] = uv.x;
  p[1] = uv.y;
  (*dest) += V_ATTRSIZE_UV;
}

inline void SetVertexUv2(const TVec2f& uv, unsigned char** dest)
{
  T_FLOAT* p = (T_FLOAT*)(*dest);
  p[0] = uv.x;
  p[1] = uv.y;
  (*dest) += V_ATTRSIZE_UV2;
}

inline void SetVertexUv3(const TVec2f& uv, unsigned char** dest)
{
  T_FLOAT* p = (T_FLOAT*)(*dest);
  p[0] = uv.x;
  p[1] = uv.y;
  (*dest) += V_ATTRSIZE_UV3;
}

inline void SetVertexUv4(const TVec2f& uv, unsigned char** dest)
{
  T_FLOAT* p = (T_FLOAT*)(*dest);
  p[0] = uv.x;
  p[1] = uv.y;
  (*dest) += V_ATTRSIZE_UV4;
}

inline void SetVertexTangent(const TVec4f& tangent, unsigned char** dest)
{
  T_FLOAT* p = (T_FLOAT*)(*dest);
  p[0] = tangent.x;
  p[1] = tangent.y;
  p[2] = tangent.z;
  p[3] = tangent.w;
  (*dest) += V_ATTRSIZE_TANGENT;
}

inline void SetVertexColor(const TColor& color, unsigned char** dest)
{
  T_UINT32* p = (T_UINT32*)(*dest);
  p[0] = color.GetPackedColor();
  (*dest) += V_ATTRSIZE_COLOR;
}

inline void SetVertexBoneWeights(const T_FLOAT* bone_weight, unsigned char** dest)
{
  T_FLOAT* p = (T_FLOAT*)(*dest);
  p[0] = bone_weight[0];
  p[1] = bone_weight[1];
  p[2] = bone_weight[2];
  p[3] = bone_weight[3];
  p[4] = bone_weight[4];
  p[5] = bone_weight[5];
  p[6] = bone_weight[6];
  p[7] = bone_weight[7];
  (*dest) += V_ATTRSIZE_BONE_WEIGHTS;
}

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