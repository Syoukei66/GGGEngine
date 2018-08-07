#include "MeshFactory_Sprite.h"
#include "../Common/GraphicsConstants.h"

enum { SPRITE_VERTEX_COORDS_COUNT = 4 };
static TVec2f SPRITE_VERTEX_COORDS[SPRITE_VERTEX_COORDS_COUNT] =
{
  { -0.5f, 0.5f }, //0 ç∂è„
  { -0.5f,-0.5f }, //1 ç∂â∫
  { 0.5f, 0.5f }, //2 âEè„
  { 0.5f,-0.5f }, //3 âEâ∫
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
  0, 2, 1,
  3, 1, 2,
};

static const T_UINT16 PLANE_VERTEX_TEX_INDEXES[SPRITE_VERTEX_INDEXES_COUNT] =
{
  0, 2, 1,
  3, 1, 2,
};

enum { SPRITE_VERTEXES_COUNT = 4 * SPRITE_SURFS_COUNT };
static bool SPRITE_VERTEXES_INITIALIZED = false;
static TVec3f SPRITE_VERTEXES[SPRITE_VERTEXES_COUNT];
static TVec2f SPRITE_UVS[SPRITE_VERTEXES_COUNT];
static T_UINT16 SPRITE_INDEXES[SPRITE_VERTEX_INDEXES_COUNT];

static void Initialize()
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
        SPRITE_VERTEXES[index].x = coord.x;
        SPRITE_VERTEXES[index].y = coord.y;
        SPRITE_VERTEXES[index].z = 0.0f;
        SPRITE_UVS[index].x = uv.x;
        SPRITE_UVS[index].y = uv.y;
        temp[vertexIndex][vertexTexIndex] = index;
        index++;
      }
      SPRITE_INDEXES[i] = temp[vertexIndex][vertexTexIndex];
    }
    SPRITE_VERTEXES_INITIALIZED = true;
  }
}

Mesh* MeshFactory::Sprite::Create(bool readonly)
{
  Initialize();
  Mesh* ret = new Mesh();
  using namespace Graphics;
  ret->CreateVertices(
    SPRITE_VERTEXES_COUNT,
    PRIMITIVE_SURF_NUM(PRIMITIVE_TRIANGLES, SPRITE_VERTEX_INDEXES_COUNT),
    Graphics::V_FORMAT_PU
  );
  ret->CreateIndices(SPRITE_VERTEX_INDEXES_COUNT);
  for (T_UINT32 i = 0; i < SPRITE_VERTEXES_COUNT; ++i)
  {
    ret->SetVertex(i, SPRITE_VERTEXES[i]);
    ret->SetUv(i, SPRITE_UVS[i]);
  }
  for (T_UINT32 i = 0; i < SPRITE_VERTEX_INDEXES_COUNT; ++i)
  {
    ret->SetIndex(i, SPRITE_INDEXES[i]);
  }
  ret->CommitChanges(readonly);
  return ret;
}
