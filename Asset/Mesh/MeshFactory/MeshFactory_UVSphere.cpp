#include "MeshFactory_UVSphere.h"

static T_INT32 SetQuad(T_INT32 i, T_INT32 v00, T_INT32 v10, T_INT32 v01, T_INT32 v11, bool reverse_normal, const UniqueRef<rcDynamicMesh>& mesh)
{
  mesh->SetIndex(i, v00);

  if (reverse_normal)
  {
    mesh->SetIndex(i + 1, v01);
    mesh->SetIndex(i + 4, v01);

    mesh->SetIndex(i + 2, v10);
    mesh->SetIndex(i + 3, v10);
  }
  else
  {
    mesh->SetIndex(i + 1, v10);
    mesh->SetIndex(i + 4, v10);

    mesh->SetIndex(i + 2, v01);
    mesh->SetIndex(i + 3, v01);
  }

  mesh->SetIndex(i + 5, v11);
  return i + 6;
}

UniqueRef<rcDynamicMesh> MeshFactory::UVSphere::Create(
  T_UINT32 format,
  T_FLOAT scale,
  T_UINT32 resolution_x, T_UINT32 resolution_y,
  bool reverse_normal
)
{
  using namespace Vertex;
  UniqueRef<rcDynamicMesh> ret = rcDynamicMesh::Create();
  const T_UINT32 vertex_count = (resolution_x + 1) * (resolution_y + 1);
  const T_UINT32 face_count = resolution_x * resolution_y;

  ret->CreateVertices(vertex_count, format);
  for (T_UINT32 y = 0, vi = 0; y <= resolution_y; ++y)
  {
    const T_FLOAT v = (T_FLOAT)y / (resolution_y);
    for (T_UINT32 x = 0; x <= resolution_x; ++x, ++vi)
    {
      const T_FLOAT u = (T_FLOAT)x / resolution_x;
      TVec3f position;
      float r = cosf(Mathf::PI * (v - 0.5f));
      position.x = r * sinf(Mathf::PI_2 * (u - 0.5f)) * 0.5f * scale;
      position.y = sinf(Mathf::PI * (v - 0.5f)) * 0.5f * scale;
      position.z = r * cosf(Mathf::PI_2 * (u - 0.5f)) * 0.5f * scale;
      if (format & V_ATTR_POSITION)
      {
        ret->SetVertex(vi, position);
      }
      if (format & V_ATTR_NORMAL)
      {
        if (reverse_normal)
        {
          ret->SetNormal(vi, -position.Normalized());
        }
        else
        {
          ret->SetNormal(vi, position.Normalized());
        }
      }
      if (format & V_ATTR_UV)
      {
        ret->SetUv(vi, TVec2f(u, v));
      }
    }
  }

  ret->AddIndices(face_count * 6);
  for (T_UINT32 ti = 0, vi = 0, y = 0; y < resolution_y; ++y, ++vi)
  {
    for (T_UINT32 x = 0; x < resolution_x; ++x, ++vi)
    {
      ti = SetQuad(
        ti,
        vi,
        vi + 1,
        vi + resolution_x + 1,
        vi + resolution_x + 2,
        reverse_normal,
        ret
      );
    }
  }

  if (format & V_ATTR_TANGENT)
  {
    ret->RecalculateTangents();
  }

  return ret;
}
