#include "MeshData_Sprite.h"

enum { SPRITE_VERTEX_COORDS_COUNT = 4 };
static TVec2f SPRITE_VERTEX_COORDS[SPRITE_VERTEX_COORDS_COUNT] =
{
  { -0.5f, -0.5f }, //0 âEè„
  { -0.5f,  0.5f }, //1 âEâ∫
  { 0.5f, -0.5f }, //2 ç∂â∫
  { 0.5f,  0.5f }, //3 ç∂è„
};

enum { SPRITE_VERTEX_TEX_COORDS_COUNT = SPRITE_VERTEX_COORDS_COUNT };
static TVec2f SPRITE_VERTEX_TEX_COORDS[SPRITE_VERTEX_TEX_COORDS_COUNT] =
{
  { 0.0f, 0.0f },
  { 0.0f, 1.0f },
  { 1.0f, 0.0f },
  { 1.0f, 1.0f },
};

enum { SPRITE_SURFS_COUNT = 1 };
enum { SPRITE_TRIANGLES_COUNT = 2 * SPRITE_SURFS_COUNT };
enum { SPRITE_VERTEX_INDEXES_COUNT = 6 };
static const T_UINT16 PLANE_VERTEX_INDEXES[SPRITE_VERTEX_INDEXES_COUNT] =
{
  0, 1, 2,
  1, 3, 2,
};

static const T_UINT16 PLANE_VERTEX_TEX_INDEXES[SPRITE_VERTEX_INDEXES_COUNT] =
{
  0, 1, 2,
  1, 3, 2,
};

enum { SPRITE_VERTEXES_COUNT = 4 * SPRITE_SURFS_COUNT };
static bool SPRITE_VERTEXES_INITIALIZED = false;
static Vertex::VCT SPRITE_VERTEXES[SPRITE_VERTEXES_COUNT];
static T_UINT16 SPRITE_INDEXES[SPRITE_VERTEX_INDEXES_COUNT];

MeshData_Sprite::MeshData_Sprite()
{
  if (!SPRITE_VERTEXES_INITIALIZED)
  {
    T_INT16 temp[SPRITE_VERTEX_COORDS_COUNT][SPRITE_VERTEX_TEX_COORDS_COUNT] = {};
    T_UINT16 index = 0;
    for (T_UINT16 i = 0; i < SPRITE_VERTEX_COORDS_COUNT; ++i)
    {
      for (T_UINT16 j = 0; j < SPRITE_VERTEX_TEX_COORDS_COUNT; ++j)
      {
        temp[i][j] = -1;
      }
    }
    for (T_UINT16 i = 0; i < SPRITE_VERTEX_INDEXES_COUNT; ++i)
    {
      T_UINT16 vertexIndex = PLANE_VERTEX_INDEXES[i];
      T_UINT16 vertexTexIndex = PLANE_VERTEX_TEX_INDEXES[i];
      TVec2f coord = SPRITE_VERTEX_COORDS[vertexIndex];
      TVec2f uv = SPRITE_VERTEX_TEX_COORDS[vertexTexIndex];
      if (temp[vertexIndex][vertexTexIndex] == -1)
      {
        SPRITE_VERTEXES[index].coord[0] = coord.x;
        SPRITE_VERTEXES[index].coord[1] = coord.y;
        SPRITE_VERTEXES[index].uv[0] = uv.x;
        SPRITE_VERTEXES[index].uv[1] = uv.y;
        temp[vertexIndex][vertexTexIndex] = index;
        index++;
      }
      SPRITE_INDEXES[i] = temp[vertexIndex][vertexTexIndex];
    }
    SPRITE_VERTEXES_INITIALIZED = true;
  }
}

T_UINT16 MeshData_Sprite::GetVertexesCount() const
{
  return SPRITE_VERTEXES_COUNT;
}

void MeshData_Sprite::SetupVertex(void* dest) const
{
  for (T_UINT16 i = 0; i < SPRITE_VERTEXES_COUNT; ++i)
  {
    ((Vertex::VCT*)dest)[i] = SPRITE_VERTEXES[i];
  }
}

T_UINT16 MeshData_Sprite::GetIndicesCount() const
{
  return SPRITE_VERTEX_INDEXES_COUNT;
}

const T_UINT16* MeshData_Sprite::GetIndices() const
{
  return SPRITE_INDEXES;
}

INativeProcess_Graphics::PrimitiveType MeshData_Sprite::GetPrimitiveType() const
{
  return INativeProcess_Graphics::PRIMITIVE_TRIANGLES;
}

Vertex::VertexType MeshData_Sprite::GetVertexType() const
{
  return Vertex::VERTEX_TYPE_VCT;
}
