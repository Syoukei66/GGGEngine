#include "MeshFactory_Plane.h"

Mesh* MeshFactory::Plane::Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y,
  T_UINT32 resolution_x, T_UINT32 resolution_y,
  T_FLOAT tile_count_x, T_FLOAT tile_count_y,
  bool readonly
)
{
  Mesh* ret = new Mesh();
  const T_UINT32 vertex_count = (resolution_x + 1) * (resolution_y + 1);
  const T_UINT32 index_count = resolution_x * resolution_y * 6;

  using namespace GraphicsConstants;
  ret->CreateVerticesWithIndex(
    vertex_count,
    index_count,
    format
  );
  ret->CreateIndices(index_count);

  for (T_UINT32 i = 0, y = 0; y <= resolution_y; ++y)
  {
    for (T_UINT32 x = 0; x <= resolution_x; ++x, ++i)
    {
      if (format & V_ATTR_POSITION)
      {
        ret->SetVertex(i, { 
          ((T_FLOAT)x - resolution_x * 0.5f) * scale_x / resolution_x,
          0.0f,
          ((T_FLOAT)y - resolution_y * 0.5f) * scale_y / resolution_y
        });
      }
      if (format & V_ATTR_NORMAL)
      {
        ret->SetNormal(i, { 0.0f, 1.0f, 0.0f });
      }
      if (format & V_ATTR_UV)
      {
        ret->SetUv(i, {(T_FLOAT)x / resolution_x * tile_count_x, (T_FLOAT)y / resolution_y * tile_count_y});
      }
      if (format & V_ATTR_UV2)
      {
        ret->SetUv2(i, { (T_FLOAT)x / resolution_x, (T_FLOAT)y / resolution_y });
      }
      if (format & V_ATTR_UV3)
      {
        ret->SetUv3(i, { (T_FLOAT)x / resolution_x * tile_count_x, (T_FLOAT)y / resolution_y * tile_count_y });
      }
      if (format & V_ATTR_UV4)
      {
        ret->SetUv4(i, { (T_FLOAT)x / resolution_x * tile_count_x, (T_FLOAT)y / resolution_y * tile_count_y });
      }
      if (format & V_ATTR_TANGENT)
      {
        ret->SetTangent(i, { 1.0f, 0.0f, 0.0f, -1.0f });
      }
      if (format & V_ATTR_COLOR)
      {
        ret->SetColor(i, TColor::WHITE);
      }
    }
  }

  for (T_UINT32 ti = 0, vi = 0, y = 0; y < resolution_y; ++y, ++vi)
  {
    for (T_UINT32 x = 0; x < resolution_x; ++x, ti += 6, ++vi)
    {
      ret->SetIndex(ti, vi);

      ret->SetIndex(ti + 2, vi + 1);
      ret->SetIndex(ti + 3, vi + 1);

      ret->SetIndex(ti + 4, vi + resolution_x + 1);
      ret->SetIndex(ti + 1, vi + resolution_x + 1);

      ret->SetIndex(ti + 5, vi + resolution_x + 2);
    }
  }
  ret->CommitChanges(readonly);
  return ret;
}
