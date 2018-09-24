#include "MeshFactory_Cube.h"

static void CreateFaceVertices(T_UINT32& i, const TVec3f& normal, T_UINT32 format, const TVec3f& scale, T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z, const TVec3f& tile_count, rcMesh* dest)
{
  using namespace Graphics;

  const TVec3f tangent = normal.x == 0.0f && normal.z == 0.0f ? TVec3f::OuterProduct(normal, TVec3f::forward) : TVec3f::OuterProduct(normal, TVec3f::up);
  const TVec3f binormal = TVec3f::OuterProduct(tangent, normal);

  const T_UINT32 xSize = (T_UINT32)fabs(tangent.x  * resolution_x + tangent.y  * resolution_y + tangent.z  * resolution_z);
  const T_UINT32 ySize = (T_UINT32)fabs(binormal.x * resolution_x + binormal.y * resolution_y + binormal.z * resolution_z);
  const T_UINT32 zSize = (T_UINT32)fabs(normal.x   * resolution_x + normal.y   * resolution_y + normal.z   * resolution_z);
  const T_FLOAT xRate = scale.x / resolution_x;
  const T_FLOAT yRate = scale.y / resolution_y;
  const T_FLOAT zRate = scale.z / resolution_z;
  const T_FLOAT xTileCount = fabs(tangent.x  * tile_count.x + tangent.y  * tile_count.y + tangent.z  * tile_count.z);
  const T_FLOAT yTileCount = fabs(binormal.x * tile_count.x + binormal.y * tile_count.y + binormal.z * tile_count.z);
  for (T_UINT32 y = 0; y <= ySize; ++y)
  {
    for (T_UINT32 x = 0; x <= xSize; ++x, ++i)
    {
      if (format & V_ATTR_POSITION)
      {
        TVec3f vertex = TVec3f(x - xSize * 0.5f, y - ySize * 0.5f, zSize * 0.5f);
        vertex = tangent * vertex.x + binormal * vertex.y + normal * vertex.z;
        dest->SetVertex(i, { vertex.x * xRate, vertex.y * yRate, vertex.z * zRate });
      }
      if (format & V_ATTR_NORMAL)
      {
        dest->SetNormal(i, normal);
      }
      if (format & V_ATTR_UV)
      {
        dest->SetUv(i, { (T_FLOAT)x / xSize * xTileCount, (T_FLOAT)y / ySize * yTileCount });
      }
      if (format & V_ATTR_UV2)
      {
        dest->SetUv2(i, { (T_FLOAT)x / xSize, (T_FLOAT)y / ySize });
      }
      if (format & V_ATTR_UV3)
      {
        dest->SetUv3(i, { (T_FLOAT)x / xSize * xTileCount, (T_FLOAT)y / ySize * yTileCount });
      }
      if (format & V_ATTR_UV4)
      {
        dest->SetUv4(i, { (T_FLOAT)x / xSize * xTileCount, (T_FLOAT)y / ySize * yTileCount });
      }
      if (format & V_ATTR_TANGENT)
      {
        dest->SetTangent(i, { tangent.x, tangent.y, tangent.z, 1.0f });
      }
      if (format & V_ATTR_COLOR)
      {
        dest->SetColor(i, TColor::WHITE);
      }
    }
  }
}

static void CreateVertices(T_UINT32 format, const TVec3f& scale, T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z, const TVec3f& tile_count, rcMesh* dest)
{
  T_UINT32 v = 0;
  CreateFaceVertices(v, TVec3f::back, format, scale, resolution_x, resolution_y, resolution_z, tile_count, dest);
  CreateFaceVertices(v, TVec3f::right, format, scale, resolution_x, resolution_y, resolution_z, tile_count, dest);
  CreateFaceVertices(v, TVec3f::forward, format, scale, resolution_x, resolution_y, resolution_z, tile_count, dest);
  CreateFaceVertices(v, TVec3f::left, format, scale, resolution_x, resolution_y, resolution_z, tile_count, dest);
  CreateFaceVertices(v, TVec3f::up, format, scale, resolution_x, resolution_y, resolution_z, tile_count, dest);
  CreateFaceVertices(v, TVec3f::down, format, scale, resolution_x, resolution_y, resolution_z, tile_count, dest);
}

static int SetQuad(T_UINT32 i, T_UINT32 v00, T_UINT32 v10, T_UINT32 v01, T_UINT32 v11, rcMesh* dest)
{
  dest->SetIndex(i, v00);

  dest->SetIndex(i + 1, v01);
  dest->SetIndex(i + 4, v01);

  dest->SetIndex(i + 2, v10);
  dest->SetIndex(i + 3, v10);

  dest->SetIndex(i + 5, v11);

  return i + 6;
}

static void CreateFaceTriangles(T_UINT32& t, T_UINT32& v, const TVec3f& normal, T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z, rcMesh* dest)
{
  const TVec3f tangent = normal.x == 0.0f && normal.z == 0.0f ? TVec3f::OuterProduct(normal, TVec3f::forward) : TVec3f::OuterProduct(normal, TVec3f::up);
  const TVec3f binormal = TVec3f::OuterProduct(tangent, normal);

  const T_UINT32 xSize = (T_UINT32)fabs(tangent.x * resolution_x + tangent.y * resolution_y + tangent.z * resolution_z);
  const T_UINT32 ySize = (T_UINT32)fabs(binormal.x * resolution_x + binormal.y * resolution_y + binormal.z * resolution_z);

  for (T_UINT32 i = 0; i < ySize; ++i, ++v)
  {
    for (T_UINT32 j = 0; j < xSize; ++j, ++v)
    {
      t = SetQuad(t, v, v + 1, v + xSize + 1, v + xSize + 2, dest);
    }
  }
  v += xSize + 1;
}

static void CreateTriangles(T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z, rcMesh* dest)
{
  T_UINT32 t = 0, v = 0;
  CreateFaceTriangles(t, v, TVec3f::back, resolution_x, resolution_y, resolution_z, dest);
  CreateFaceTriangles(t, v, TVec3f::right, resolution_x, resolution_y, resolution_z, dest);
  CreateFaceTriangles(t, v, TVec3f::forward, resolution_x, resolution_y, resolution_z, dest);
  CreateFaceTriangles(t, v, TVec3f::left, resolution_x, resolution_y, resolution_z, dest);
  CreateFaceTriangles(t, v, TVec3f::up, resolution_x, resolution_y, resolution_z, dest);
  CreateFaceTriangles(t, v, TVec3f::down, resolution_x, resolution_y, resolution_z, dest);
}

rcMesh* MeshFactory::Cube::Create(
  T_UINT32 format,
  T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
  T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z,
  T_FLOAT tile_count_x, T_FLOAT tile_count_y, T_FLOAT tile_count_z,
  bool read_only
)
{
  rcMesh* ret = rcMesh::Create();

  const T_UINT32 zFaceVertices = (resolution_x + 1) * (resolution_y + 1);
  const T_UINT32 xFaceVertices = (resolution_y + 1) * (resolution_z + 1);
  const T_UINT32 yFaceVertices = (resolution_x + 1) * (resolution_z + 1);
  const T_UINT32 vertex_count = (xFaceVertices + yFaceVertices + zFaceVertices) * 2;

  const T_UINT32 zFaceQuads = resolution_x * resolution_y;
  const T_UINT32 xFaceQuads = resolution_y * resolution_z;
  const T_UINT32 yFaceQuads = resolution_x * resolution_z;
  const T_UINT32 quads = (xFaceQuads + yFaceQuads + zFaceQuads) * 2;
  const T_UINT32 index_count = quads * 6;

  ret->CreateVerticesWithIndex(
    vertex_count,
    index_count,
    format
  );
  ret->CreateIndices(index_count);

  CreateVertices(format, { scale_x, scale_y, scale_z }, resolution_x, resolution_y, resolution_z, { tile_count_x, tile_count_y, tile_count_z }, ret);
  CreateTriangles(resolution_x, resolution_y, resolution_z, ret);

  ret->CommitChanges(read_only);
  return ret;
}
