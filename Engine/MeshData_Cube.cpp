#include "MeshData_Cube.h"

enum { CUBE_VERTEX_COORDS_COUNT = 8 };
static TVec3f CUBE_VERTEX_COORDS[CUBE_VERTEX_COORDS_COUNT] =
{
  {  0.5f,  0.5f, -0.5f },  //0
  {  0.5f, -0.5f, -0.5f },  //1
  { -0.5f, -0.5f, -0.5f },  //2
  { -0.5f,  0.5f, -0.5f },  //3

  {  0.5f,  0.5f,  0.5f },  //4
  {  0.5f, -0.5f,  0.5f },  //5
  { -0.5f, -0.5f,  0.5f },  //6
  { -0.5f,  0.5f,  0.5f },  //7
};

enum { CUBE_VERTEX_TEX_COORDS_COUNT = 13 };
static TVec2f CUBE_VERTEX_TEX_COORDS[CUBE_VERTEX_TEX_COORDS_COUNT] =
{
  { 0.75f, 0.00f }, //0
  { 0.50f, 0.00f }, //1

  { 0.25f, 0.00f }, //2
  { 0.50f, 0.25f }, //3

  { 0.25f, 0.25f }, //4
  { 0.50f, 0.50f }, //5

  { 0.75f, 0.25f }, //6
  { 0.00f, 0.25f }, //7

  { 0.25f, 0.50f }, //8
  { 0.00f, 0.50f }, //9

  { 0.00f, 0.00f }, //10
  { 1.00f, 0.25f }, //11

  { 1.00f, 0.00f }, //12
};

enum { CUBE_SURFS_COUNT = 6 };
enum { CUBE_NORMAL_COORDS_COUNT = CUBE_SURFS_COUNT };
static TVec3f CUBE_NORMAL_COORDS[CUBE_NORMAL_COORDS_COUNT] =
{
  { 0.0f,  0.0f, -1.0f },  //前
  { 0.0f,  0.0f,  1.0f },  //後ろ
  { 1.0f,  0.0f,  0.0f },  //上
  { 0.0f, -1.0f,  0.0f },  //右

  { -1.0f,  0.0f,  0.0f },  //下
  { 0.0f,  1.0f,  0.0f },  //左
};

enum { CUBE_TRIANGLES_COUNT = 2 * CUBE_SURFS_COUNT };
enum { CUBE_VERTEX_INDEXES_COUNT = 3 * CUBE_TRIANGLES_COUNT };
static const T_UINT16 CUBE_VERTEX_INDEXES[CUBE_VERTEX_INDEXES_COUNT] =
{
  1, 3, 0, //前
  7, 5, 4, //後ろ
  4, 1, 0, //上
  5, 2, 1, //右
  2, 7, 3, //下
  0, 7, 4, //左

  1, 2, 3, //前
  7, 6, 5, //後ろ
  4, 5, 1, //上
  5, 6, 2, //右
  2, 6, 7, //下
  0, 3, 7, //左
};

static const T_UINT16 CUBE_VERTEX_TEX_INDEXES[CUBE_VERTEX_INDEXES_COUNT] =
{
  4,  5,  3, //前
  0, 11, 12, //後ろ
  0,  3,  6, //上
  1,  4,  3, //右
  7,  8,  4, //下
  2,  7,  4, //左

  4,  8,  5, //前
  0,  6, 11, //後ろ
  0,  1,  3, //上
  1,  2,  4, //右
  7,  9,  8, //下
  2, 10,  7, //左
};

static const T_UINT16 CUBE_NORMAL_INDEXES[CUBE_VERTEX_INDEXES_COUNT] =
{
  0, 0, 0, //前
  1, 1, 1, //後ろ
  2, 2, 2, //上
  3, 3, 3, //右
  4, 4, 4, //下
  5, 5, 5, //左

  0, 0, 0, //前
  1, 1, 1, //後ろ
  2, 2, 2, //上
  3, 3, 3, //右
  4, 4, 4, //下
  5, 5, 5, //左
};

enum { CUBE_VERTEXES_COUNT = 4 * CUBE_SURFS_COUNT };
static bool CUBE_VERTEXES_INITIALIZED = false;
static Vertex::VNCT CUBE_VERTEXES[CUBE_VERTEXES_COUNT];
static T_UINT16 CUBE_INDEXES[CUBE_VERTEX_INDEXES_COUNT];

static void Initialize()
{
  if (!CUBE_VERTEXES_INITIALIZED)
  {
    T_INT16 temp[CUBE_VERTEX_COORDS_COUNT][CUBE_VERTEX_TEX_COORDS_COUNT][CUBE_NORMAL_COORDS_COUNT] = {};
    T_UINT16 index = 0;
    for (T_UINT16 i = 0; i < CUBE_VERTEX_COORDS_COUNT; ++i)
    {
      for (T_UINT16 j = 0; j < CUBE_VERTEX_TEX_COORDS_COUNT; ++j)
      {
        for (T_UINT16 k = 0; k < CUBE_NORMAL_COORDS_COUNT; ++k)
        {
          temp[i][j][k] = -1;
        }
      }
    }
    for (T_UINT16 i = 0; i < CUBE_VERTEX_INDEXES_COUNT; ++i)
    {
      T_UINT16 vertexIndex = CUBE_VERTEX_INDEXES[i];
      T_UINT16 vertexTexIndex = CUBE_VERTEX_TEX_INDEXES[i];
      T_UINT16 normalIndex = CUBE_NORMAL_INDEXES[i];
      TVec3f coord = CUBE_VERTEX_COORDS[vertexIndex];
      TVec2f uv = CUBE_VERTEX_TEX_COORDS[vertexTexIndex];
      TVec3f normal = CUBE_NORMAL_COORDS[normalIndex].Normalized();
      if (temp[vertexIndex][vertexTexIndex][normalIndex] == -1)
      {
        CUBE_VERTEXES[index].coord[0] = coord.x;
        CUBE_VERTEXES[index].coord[1] = coord.y;
        CUBE_VERTEXES[index].coord[2] = coord.z;
        CUBE_VERTEXES[index].uv[0] = uv.x;
        CUBE_VERTEXES[index].uv[1] = uv.y;
        CUBE_VERTEXES[index].normal[0] = normal.x;
        CUBE_VERTEXES[index].normal[1] = normal.y;
        CUBE_VERTEXES[index].normal[2] = normal.z;
        temp[vertexIndex][vertexTexIndex][normalIndex] = index;
        index++;
      }
      CUBE_INDEXES[i] = temp[vertexIndex][vertexTexIndex][normalIndex];
    }
    CUBE_VERTEXES_INITIALIZED = true;
  }
}

T_UINT16 MeshData_Cube::GetVertexesCount() const
{
  Initialize();
  return CUBE_VERTEXES_COUNT;
}

void MeshData_Cube::SetupVertex(void* dest) const
{
  Initialize();
  for (T_UINT16 i = 0; i < CUBE_VERTEXES_COUNT; ++i)
  {
    ((Vertex::VNCT*)dest)[i] = CUBE_VERTEXES[i];
  }
}

T_UINT16 MeshData_Cube::GetIndicesCount() const
{
  Initialize();
  return CUBE_VERTEX_INDEXES_COUNT;
}

const T_UINT16* MeshData_Cube::GetIndices() const
{
  Initialize();
  return CUBE_INDEXES;
}

INativeProcess_Graphics::PrimitiveType MeshData_Cube::GetPrimitiveType() const
{
  Initialize();
  return INativeProcess_Graphics::PRIMITIVE_TRIANGLES;
}

Vertex::VertexType MeshData_Cube::GetVertexType() const
{
  Initialize();
  return Vertex::VERTEX_TYPE_VNCT;
}