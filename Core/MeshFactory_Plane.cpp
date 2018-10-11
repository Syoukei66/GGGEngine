#include "MeshFactory_Plane.h"
#include "GraphicsConstants.h"

MeshData* MeshFactory::Plane::Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y,
  T_UINT32 resolution_x, T_UINT32 resolution_y,
  T_FLOAT tile_count_x, T_FLOAT tile_count_y
)
{
  MeshData* ret = new MeshData();

  using namespace Graphics;
  ret->vertex_count_ = (resolution_x + 1) * (resolution_y + 1);
  ret->vertex_format_ = format;
  ret->vertex_size_ = CalcVertexSize(format);
  ret->data_ = new unsigned char[ret->vertex_size_]();
  unsigned char* p = ret->data_;

  for (T_UINT32 i = 0, y = 0; y <= resolution_y; ++y)
  {
    for (T_UINT32 x = 0; x <= resolution_x; ++x, ++i)
    {
      if (format & V_ATTR_POSITION)
      {
        SetVertexPosition({
          ((T_FLOAT)x - resolution_x * 0.5f) * scale_x / resolution_x,
          0.0f,
          ((T_FLOAT)y - resolution_y * 0.5f) * scale_y / resolution_y
          }, 
          &p);
      }
      if (format & V_ATTR_NORMAL)
      {
        SetVertexNormal({ 0.0f, 1.0f, 0.0f }, &p);
      }
      if (format & V_ATTR_UV)
      {
        SetVertexUv({ (T_FLOAT)x / resolution_x * tile_count_x, (T_FLOAT)y / resolution_y * tile_count_y }, &p);
      }
      if (format & V_ATTR_UV2)
      {
        SetVertexUv2({ (T_FLOAT)x / resolution_x, (T_FLOAT)y / resolution_y }, &p);
      }
      if (format & V_ATTR_UV3)
      {
        SetVertexUv3({ (T_FLOAT)x / resolution_x * tile_count_x, (T_FLOAT)y / resolution_y * tile_count_y }, &p);
      }
      if (format & V_ATTR_UV4)
      {
        SetVertexUv4({ (T_FLOAT)x / resolution_x * tile_count_x, (T_FLOAT)y / resolution_y * tile_count_y }, &p);
      }
      if (format & V_ATTR_TANGENT)
      {
        SetVertexTangent({ 1.0f, 0.0f, 0.0f, -1.0f }, &p);
      }
      if (format & V_ATTR_COLOR)
      {
        SetVertexColor(TColor::WHITE, &p);
      }
    }
  }

  ret->polygon_count_ = resolution_x * resolution_y * 2;
  ret->index_count_ = ret->polygon_count_ * 3;
  ret->indices_ = new T_UINT32[ret->index_count_]();
  for (T_UINT32 ti = 0, vi = 0, y = 0; y < resolution_y; ++y, ++vi)
  {
    for (T_UINT32 x = 0; x < resolution_x; ++x, ti += 6, ++vi)
    {
      ret->indices_[ti] = vi;

      ret->indices_[ti + 2] = vi + 1;
      ret->indices_[ti + 3] = vi + 1;

      ret->indices_[ti + 4] = vi + resolution_x + 1;
      ret->indices_[ti + 1] = vi + resolution_x + 1;

      ret->indices_[ti + 5] = vi + resolution_x + 2;
    }
  }

  ret->submesh_count_ = 1;
  ret->submesh_index_counts_ = new T_UINT32[ret->submesh_count_];
  ret->submesh_index_counts_[0] = ret->index_count_;

  return ret;
}
