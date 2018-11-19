#pragma once

namespace Vertex
{

/*!
 * @brief 頂点バッファの属性
 */
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

/*!
 * @brief 頂点バッファの属性あたりのサイズ
 */
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

/*!
 * @brief 頂点バッファの属性から頂点サイズを計算する
 */
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

/*!
 * @brief インデックスバッファの属性
 */
enum class IndexFormat : T_UINT8
{
  INDEX_FMT_16,
  INDEX_FMT_32,

  INDEX_FMT_DATANUM,
};

static T_UINT8 INDEX_FORMAT_SIZES[static_cast<T_UINT8>(IndexFormat::INDEX_FMT_DATANUM)] =
{
  (T_UINT8)sizeof(T_FIXED_INT16),
  (T_UINT8)sizeof(T_FIXED_INT32),
};

/*!
 * @brief プリミティブの種類
 */
enum class PrimitiveType : T_UINT32
{
  POINTS,
  LINES,
  LINESTRIP,
  TRIANGLES,
  TRIANGLESTRIP,
  TRIANGLEFAN,

  DATANUM,
};

static T_UINT32 PRIMITIVE_SURF_NUM(PrimitiveType type, T_UINT32 vertex_count)
{
  if (type == PrimitiveType::POINTS)
  {
    return vertex_count;
  }
  if (type == PrimitiveType::LINES)
  {
    return vertex_count;
  }
  if (type == PrimitiveType::LINESTRIP)
  {
    return vertex_count;
  }
  if (type == PrimitiveType::TRIANGLES)
  {
    return vertex_count / 3;
  }
  if (type == PrimitiveType::TRIANGLESTRIP)
  {
    return vertex_count - 2;
  }
  if (type == PrimitiveType::TRIANGLEFAN)
  {
    return vertex_count - 2;
  }
  return vertex_count;
}

} // namespace Vertex


#include <Core/Application/Application.h>

// 二重インクルード防止の為、処理が必要な部分を分けた
namespace Vertex
{

static GG_INLINE void SetVertexPosition(const TVec3f& pos, unsigned char** dest)
{
  T_FLOAT* p = (T_FLOAT*)(*dest);
  p[0] = pos.x;
  p[1] = pos.y;
  p[2] = pos.z;
  (*dest) += V_ATTRSIZE_POSITION;
}

static GG_INLINE void SetVertexNormal(const TVec3f& norm, unsigned char** dest)
{
  T_FLOAT* p = (T_FLOAT*)(*dest);
  p[0] = norm.x;
  p[1] = norm.y;
  p[2] = norm.z;
  (*dest) += V_ATTRSIZE_NORMAL;
}

static GG_INLINE void SetVertexUv(const TVec2f& uv, unsigned char** dest)
{
  T_FLOAT* p = (T_FLOAT*)(*dest);
  p[0] = uv.x;
  p[1] = uv.y;
  (*dest) += V_ATTRSIZE_UV;
}

static GG_INLINE void SetVertexUv2(const TVec2f& uv, unsigned char** dest)
{
  T_FLOAT* p = (T_FLOAT*)(*dest);
  p[0] = uv.x;
  p[1] = uv.y;
  (*dest) += V_ATTRSIZE_UV2;
}

static GG_INLINE void SetVertexUv3(const TVec2f& uv, unsigned char** dest)
{
  T_FLOAT* p = (T_FLOAT*)(*dest);
  p[0] = uv.x;
  p[1] = uv.y;
  (*dest) += V_ATTRSIZE_UV3;
}

static GG_INLINE void SetVertexUv4(const TVec2f& uv, unsigned char** dest)
{
  T_FLOAT* p = (T_FLOAT*)(*dest);
  p[0] = uv.x;
  p[1] = uv.y;
  (*dest) += V_ATTRSIZE_UV4;
}

static GG_INLINE void SetVertexTangent(const TVec4f& tangent, unsigned char** dest)
{
  T_FLOAT* p = (T_FLOAT*)(*dest);
  p[0] = tangent.x;
  p[1] = tangent.y;
  p[2] = tangent.z;
  p[3] = tangent.w;
  (*dest) += V_ATTRSIZE_TANGENT;
}

static GG_INLINE void SetVertexColor(const TColor& color, unsigned char** dest)
{
  T_UINT32* p = (T_UINT32*)(*dest);
  Application::GetPlatform()->GetGraphicsAPI()->PackColor4u8(
    &p[0],
    (T_UINT8)(color.data[0] * 255),
    (T_UINT8)(color.data[1] * 255),
    (T_UINT8)(color.data[2] * 255),
    (T_UINT8)(color.data[3] * 255)
  );
  (*dest) += V_ATTRSIZE_COLOR;
}

static GG_INLINE void SetVertexBoneWeights(const T_FLOAT* bone_weight, unsigned char** dest)
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

static GG_INLINE void SetIndexIndex16(T_UINT32 index, unsigned char** dest)
{
  T_FIXED_UINT16* p = (T_FIXED_UINT16*)(*dest);
  (*p) = (T_FIXED_UINT16)index;
  (*dest) += INDEX_FORMAT_SIZES[static_cast<T_UINT8>(IndexFormat::INDEX_FMT_16)];
  return;
}

static GG_INLINE void SetIndexIndex32(T_UINT32 index, unsigned char** dest)
{
  T_FIXED_UINT32* p = (T_FIXED_UINT32*)(*dest);
  (*p) = (T_FIXED_UINT32)index;
  (*dest) += INDEX_FORMAT_SIZES[static_cast<T_UINT8>(IndexFormat::INDEX_FMT_32)];
  return;
}


static GG_INLINE void SetVertexPosition(const TVec3f& pos, T_UINT32 format, unsigned char** dest)
{
  if (format & V_ATTR_POSITION)
  {
    SetVertexPosition(pos, dest);
  }
}

static GG_INLINE void SetVertexNormal(const TVec3f& norm, T_UINT32 format, unsigned char** dest)
{
  if (format & V_ATTR_NORMAL)
  {
    SetVertexNormal(norm, dest);
  }
}

static GG_INLINE void SetVertexUv(const TVec2f& uv, T_UINT32 format, unsigned char** dest)
{
  if (format & V_ATTR_UV)
  {
    SetVertexUv(uv, dest);
  }
}

static GG_INLINE void SetVertexUv2(const TVec2f& uv2, T_UINT32 format, unsigned char** dest)
{
  if (format & V_ATTR_UV2)
  {
    SetVertexUv(uv2, dest);
  }
}

static GG_INLINE void SetVertexUv3(const TVec2f& uv3, T_UINT32 format, unsigned char** dest)
{
  if (format & V_ATTR_UV3)
  {
    SetVertexUv(uv3, dest);
  }
}

static GG_INLINE void SetVertexUv4(const TVec2f& uv4, T_UINT32 format, unsigned char** dest)
{
  if (format & V_ATTR_UV4)
  {
    SetVertexUv(uv4, dest);
  }
}

static GG_INLINE void SetVertexTangent(const TVec4f& tangent, T_UINT32 format, unsigned char** dest)
{
  if (format & V_ATTR_TANGENT)
  {
    SetVertexTangent(tangent, dest);
  }
}

static GG_INLINE void SetVertexColor(const TColor& color, T_UINT32 format, unsigned char** dest)
{
  if (format & V_ATTR_COLOR)
  {
    SetVertexColor(color, dest);
  }
}

static GG_INLINE void SetVertexBoneWeights(const T_FLOAT* bone_weight, T_UINT32 format, unsigned char** dest)
{
  if (format & V_ATTR_BONE_WEIGHTS)
  {
    SetVertexBoneWeights(bone_weight, dest);
  }
}

static GG_INLINE void SetIndexIndex(T_UINT32 index, IndexFormat format, unsigned char** dest)
{
  if (format == IndexFormat::INDEX_FMT_16)
  {
    SetIndexIndex16(index, dest);
    return;
  }
  if (format == IndexFormat::INDEX_FMT_32)
  {
    SetIndexIndex32(index, dest);
    return;
  }
}

} // namespace Vertex
