#include "MeshFactory_RoundedCube.h"
#include <math.h>

enum Axis
{
  AXIS_X,
  AXIS_Y,
  AXIS_Z,
};

static void SetVertex(
  T_INT32 format,
  Axis axis, T_INT32 i,
  T_INT32 x, T_INT32 y, T_INT32 z,
  T_FLOAT u, T_FLOAT v,
  T_INT32 resolution_x,
  T_INT32 resolution_y,
  T_INT32 resolution_z,
  T_FLOAT scale_x,
  T_FLOAT scale_y,
  T_FLOAT scale_z,
  T_FLOAT tile_count_x,
  T_FLOAT tile_count_y,
  T_FLOAT tile_count_z,
  T_INT32 roundness,
  const UniqueRef<rcDynamicMesh>& mesh
)
{
  using namespace Vertex;

  TVec3f vertex = TVec3f((T_FLOAT)x, (T_FLOAT)y, (T_FLOAT)z);
  TVec3f inner = vertex;

  if (x < roundness)
  {
    inner.x = (T_FLOAT)roundness;
  }
  else if (x > resolution_x - roundness)
  {
    inner.x = (T_FLOAT)resolution_x - roundness;
  }
  if (y < roundness)
  {
    inner.y = (T_FLOAT)roundness;
  }
  else if (y > resolution_y - roundness)
  {
    inner.y = (T_FLOAT)resolution_y - roundness;
  }
  if (z < roundness)
  {
    inner.z = (T_FLOAT)roundness;
  }
  else if (z > resolution_z - roundness)
  {
    inner.z = (T_FLOAT)resolution_z - roundness;
  }

  TVec3f normal = (vertex - inner).Normalized();
  vertex = inner + normal * (T_FLOAT)roundness;

  T_FLOAT vx = x * (2.0f / resolution_x) - 1.0f;
  T_FLOAT vy = y * (2.0f / resolution_y) - 1.0f;
  T_FLOAT vz = z * (2.0f / resolution_z) - 1.0f;
  T_FLOAT x2 = vx * vx;
  T_FLOAT y2 = vy * vy;
  T_FLOAT z2 = vz * vz;
  TVec3f s;
  TVec3f f;
  f.x = sqrtf(1.0f - y2 / 2.0f - z2 / 2.0f + y2 * z2 / 3.0f);
  f.y = sqrtf(1.0f - x2 / 2.0f - z2 / 2.0f + x2 * z2 / 3.0f);
  f.z = sqrtf(1.0f - x2 / 2.0f - y2 / 2.0f + x2 * y2 / 3.0f);

  if (format & V_ATTR_POSITION)
  {
    mesh->SetVertex(i, TVec3f(
      ((vertex.x / resolution_x) - 0.5f) * scale_x, 
      ((vertex.y / resolution_y) - 0.5f) * scale_y,
      ((vertex.z / resolution_z) - 0.5f) * scale_z
      ));
  }
  if (format & V_ATTR_NORMAL)
  {
    mesh->SetNormal(i, normal);
  }
  if (format & V_ATTR_UV)
  {
    if (axis == AXIS_X)
    {
      mesh->SetUv(i, { u * tile_count_x * (f.z - 0.5f) * 2.0f, v * tile_count_x * (f.y - 0.5f) * 2.0f });
    }
    else if (axis == AXIS_Y)
    {
      mesh->SetUv(i, { u * tile_count_y * (f.x - 0.5f) * 2.0f, v * tile_count_y * (f.z - 0.5f) * 2.0f });
    }
    else if (axis == AXIS_Z)
    {
      mesh->SetUv(i, { u * tile_count_z * (f.x - 0.5f) * 2.0f, v * tile_count_z * (f.y - 0.5f) * 2.0f });
    }
  }
  if (format & V_ATTR_UV2)
  {
    if (axis == AXIS_X)
    {
      mesh->SetUv(i, { (T_FLOAT)u * tile_count_x, (T_FLOAT)v * tile_count_x });
    }
    else if (axis == AXIS_Y)
    {
      mesh->SetUv(i, { (T_FLOAT)u * tile_count_y, (T_FLOAT)v * tile_count_y });
    }
    else if (axis == AXIS_Z)
    {
      mesh->SetUv(i, { (T_FLOAT)u * tile_count_z, (T_FLOAT)v * tile_count_z });
    }
  }
  if (format & V_ATTR_UV3)
  {
    if (axis == AXIS_X)
    {
      mesh->SetUv(i, { u * (f.z - 0.5f) * 2.0f, v * (f.y - 0.5f) * 2.0f });
    }
    else if (axis == AXIS_Y)
    {
      mesh->SetUv(i, { u * (f.x - 0.5f) * 2.0f, v * (f.z - 0.5f) * 2.0f });
    }
    else if (axis == AXIS_Z)
    {
      mesh->SetUv(i, { u * (f.x - 0.5f) * 2.0f, v * (f.y - 0.5f) * 2.0f });
    }
  }
  if (format & V_ATTR_UV4)
  {
    if (axis == AXIS_X)
    {
      mesh->SetUv(i, { (T_FLOAT)u, (T_FLOAT)v });
    }
    else if (axis == AXIS_Y)
    {
      mesh->SetUv(i, { (T_FLOAT)u, (T_FLOAT)v });
    }
    else if (axis == AXIS_Z)
    {
      mesh->SetUv(i, { (T_FLOAT)u, (T_FLOAT)v });
    }
  }
}

static void CreateVertices(
  T_INT32 format,
  T_INT32 resolution_x,
  T_INT32 resolution_y,
  T_INT32 resolution_z,
  T_FLOAT scale_x,
  T_FLOAT scale_y,
  T_FLOAT scale_z,
  T_FLOAT tile_count_x,
  T_FLOAT tile_count_y,
  T_FLOAT tile_count_z,
  T_INT32 roundness,
  const UniqueRef<rcDynamicMesh>& mesh
)
{
  T_INT32 cornerVertices = 8;
  T_INT32 innerresolution_x = resolution_x - 1;
  T_INT32 innerresolution_y = resolution_y - 1;
  T_INT32 innerresolution_z = resolution_z - 1;
  T_INT32 edgeVertices = (innerresolution_x + innerresolution_y + innerresolution_z) * 4;
  T_INT32 faceVertices = (
    innerresolution_x * innerresolution_y +
    innerresolution_x * innerresolution_z +
    innerresolution_y * innerresolution_z
    ) * 2;
  mesh->CreateVertices(cornerVertices + edgeVertices + faceVertices, format);

  T_INT32 v = 0;
  for (T_INT32 y = 0; y <= resolution_y; ++y)
  {
    for (T_INT32 x = 0; x <= resolution_x; ++x)
    {
      SetVertex(
        format,
        AXIS_Z,
        v++,
        x, y, 0,
        1.0f - (T_FLOAT)x / resolution_x, (T_FLOAT)y / resolution_y,
        resolution_x, resolution_y, resolution_z,
        scale_x, scale_y, scale_z,
        tile_count_x, tile_count_y, tile_count_z,
        roundness,
        mesh
      );
    }
    for (T_INT32 z = 1; z <= resolution_z; z++)
    {
      SetVertex(
        format,
        AXIS_X,
        v++,
        resolution_x, y, z,
        1.0f - (T_FLOAT)(z - 1) / (resolution_z - 1), (T_FLOAT)y / resolution_y,
        resolution_x, resolution_y, resolution_z,
        scale_x, scale_y, scale_z,
        tile_count_x, tile_count_y, tile_count_z,
        roundness,
        mesh
      );
    }
    for (T_INT32 x = resolution_x - 1; x >= 0; x--)
    {
      SetVertex(
        format,
        AXIS_Z,
        v++,
        x, y, resolution_z,
        (T_FLOAT)(x) / (resolution_x - 1), (T_FLOAT)y / resolution_y,
        resolution_x, resolution_y, resolution_z,
        scale_x, scale_y, scale_z,
        tile_count_x, tile_count_y, tile_count_z,
        roundness,
        mesh
      );
    }
    for (T_INT32 z = resolution_z - 1; z > 0; z--)
    {
      SetVertex(
        format,
        AXIS_X,
        v++,
        0, y, z,
        (T_FLOAT)(z - 1) / (resolution_z - 2), (T_FLOAT)y / resolution_y,
        resolution_x, resolution_y, resolution_z,
        scale_x, scale_y, scale_z,
        tile_count_x, tile_count_y, tile_count_z,
        roundness,
        mesh
      );
    }
  }
  for (T_INT32 z = 1; z < resolution_z; z++)
  {
    for (T_INT32 x = 1; x < resolution_x; x++)
    {
      SetVertex(
        format,
        AXIS_Y,
        v++,
        x, resolution_y, z,
        (T_FLOAT)(x - 1) / (resolution_x - 1), (T_FLOAT)(z - 1) / (resolution_z - 1),
        resolution_x, resolution_y, resolution_z,
        scale_x, scale_y, scale_z,
        tile_count_x, tile_count_y, tile_count_z,
        roundness,
        mesh
      );
    }
  }
  for (T_INT32 z = 1; z < resolution_z; z++)
  {
    for (T_INT32 x = 1; x < resolution_x; x++)
    {
      SetVertex(
        format,
        AXIS_Y,
        v++,
        x, 0, z,
        (T_FLOAT)(x - 1) / (resolution_x - 1), (T_FLOAT)(z - 1) / (resolution_z - 1),
        resolution_x, resolution_y, resolution_z,
        scale_x, scale_y, scale_z,
        tile_count_x, tile_count_y, tile_count_z,
        roundness,
        mesh
      );
    }
  }
}

static T_INT32 SetQuad(T_INT32 i, T_INT32 v00, T_INT32 v10, T_INT32 v01, T_INT32 v11, const UniqueRef<rcDynamicMesh>& mesh)
{
  mesh->SetIndex(i, v00);

  mesh->SetIndex(i + 1, v01);
  mesh->SetIndex(i + 4, v01);

  mesh->SetIndex(i + 2, v10);
  mesh->SetIndex(i + 3, v10);

  mesh->SetIndex(i + 5, v11);
  return i + 6;
}

static T_INT32 CreateTopFace(
  T_INT32 t, T_INT32 ring,
  T_INT32 resolution_x, T_INT32 resolution_y, T_INT32 resolution_z,
  const UniqueRef<rcDynamicMesh>& mesh
)
{
  T_INT32 v = ring * resolution_y;
  for (T_INT32 x = 0; x < resolution_x - 1; x++, v++)
  {
    t = SetQuad(t, v, v + 1, v + ring - 1, v + ring, mesh);
  }
  t = SetQuad(t, v, v + 1, v + ring - 1, v + 2, mesh);

  //列の最初と最後を保持しておく
  //vMidは内側で、処理中にインクリメントされる
  T_INT32 vMin = ring * (resolution_y + 1) - 1;
  T_INT32 vMid = vMin + 1;
  T_INT32 vMax = v + 2;
  for (T_INT32 z = 1; z < resolution_z - 1; z++, vMin--, vMid++, vMax++)
  {
    t = SetQuad(t, vMin, vMid, vMin - 1, vMid + resolution_x - 1, mesh);
    for (T_INT32 x = 1; x < resolution_x - 1; x++, vMid++)
    {
      t = SetQuad(t, vMid, vMid + 1, vMid + resolution_x - 1, vMid + resolution_x, mesh);
    }
    t = SetQuad(t, vMid, vMax, vMid + resolution_x - 1, vMax + 1, mesh);
  }
  T_INT32 vTop = vMin - 2;
  t = SetQuad(t, vMin, vMid, vTop + 1, vTop, mesh);
  for (T_INT32 x = 1; x < resolution_x - 1; x++, vTop--, vMid++)
  {
    t = SetQuad(t, vMid, vMid + 1, vTop, vTop - 1, mesh);
  }
  t = SetQuad(t, vMid, vTop - 2, vTop, vTop - 1, mesh);
  return t;
}

static T_INT32 CreateBottomFace(
  T_INT32 t, T_INT32 ring,
  T_INT32 resolution_x, T_INT32 resolution_y, T_INT32 resolution_z,
  const UniqueRef<rcDynamicMesh>& mesh
)
{
  T_INT32 v = 1;
  T_INT32 vMid = mesh->GetVertexCount() - (resolution_x - 1) * (resolution_z - 1);
  t = SetQuad(t, ring - 1, vMid, 0, 1, mesh);
  for (T_INT32 x = 1; x < resolution_x - 1; x++, v++, vMid++)
  {
    t = SetQuad(t, vMid, vMid + 1, v, v + 1, mesh);
  }
  t = SetQuad(t, vMid, v + 2, v, v + 1, mesh);

  T_INT32 vMin = ring - 2;
  vMid -= resolution_x - 2;
  T_INT32 vMax = v + 2;
  for (T_INT32 z = 1; z < resolution_z - 1; z++, vMin--, vMid++, vMax++)
  {
    t = SetQuad(t, vMin, vMid + resolution_x - 1, vMin + 1, vMid, mesh);
    for (T_INT32 x = 1; x < resolution_x - 1; x++, vMid++)
    {
      t = SetQuad(t, vMid + resolution_x - 1, vMid + resolution_x, vMid, vMid + 1, mesh);
    }
    t = SetQuad(t, vMid + resolution_x - 1, vMax + 1, vMid, vMax, mesh);
  }
  T_INT32 vTop = vMin - 1;
  t = SetQuad(t, vTop + 1, vTop, vTop + 2, vMid, mesh);
  for (T_INT32 x = 1; x < resolution_x - 1; x++, vTop--, vMid++)
  {
    t = SetQuad(t, vTop, vTop - 1, vMid, vMid + 1, mesh);
  }
  t = SetQuad(t, vTop, vTop - 1, vMid, vTop - 2, mesh);
  return t;
}

static void CreateTriangles(
  T_INT32 resolution_x, T_INT32 resolution_y, T_INT32 resolution_z,
  const UniqueRef<rcDynamicMesh>& mesh
)
{
  const T_INT32 quads = (
    resolution_x * resolution_y +
    resolution_x * resolution_z +
    resolution_y * resolution_z
    ) * 2;
  mesh->AddIndices(quads * 6);
  T_INT32 ring = (resolution_x + resolution_z) * 2;
  T_INT32 t = 0, v = 0;

  for (T_INT32 y = 0; y < resolution_y; y++, v++)
  {
    for (T_INT32 q = 0; q < ring - 1; q++, v++)
    {
      t = SetQuad(t, v, v + 1, v + ring, v + ring + 1, mesh);
    }
    t = SetQuad(t, v, v - ring + 1, v + ring, v + 1, mesh);
  }

  t = CreateTopFace(t, ring, resolution_x, resolution_y, resolution_z, mesh);
  t = CreateBottomFace(t, ring, resolution_x, resolution_y, resolution_z, mesh);
}

UniqueRef<rcDynamicMesh> MeshFactory::CubeSphere::Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z,
  T_FLOAT tile_count_x, T_FLOAT tile_count_y, T_FLOAT tile_count_z,
  T_UINT32 roundness
)
{
  UniqueRef<rcDynamicMesh> mesh = rcDynamicMesh::Create();
  CreateVertices(
    format, 
    resolution_x, resolution_y, resolution_z,
    scale_x, scale_y, scale_z,
    tile_count_x, tile_count_y, tile_count_z,
    roundness,
    mesh
  );
  CreateTriangles(resolution_x, resolution_y, resolution_z, mesh);

  if (format & Vertex::V_ATTR_TANGENT)
  {
    mesh->RecalculateTangents();
  }
  return mesh;
}
