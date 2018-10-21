#include "MeshFactory_Sprite.h"
#include "GraphicsConstants.h"

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
enum { SPRITE_VERTEX_INDICES_COUNT = 6 };
static const T_UINT16 PLANE_VERTEX_INDEXES[SPRITE_VERTEX_INDICES_COUNT] =
{
  0, 2, 1,
  3, 1, 2,
};

static const T_UINT16 PLANE_VERTEX_TEX_INDEXES[SPRITE_VERTEX_INDICES_COUNT] =
{
  0, 2, 1,
  3, 1, 2,
};

enum { SPRITE_VERTEXES_COUNT = 4 * SPRITE_SURFS_COUNT };
static bool SPRITE_VERTEXES_INITIALIZED = false;
static TVec3f SPRITE_VERTEXES[SPRITE_VERTEXES_COUNT];
static TVec2f SPRITE_UVS[SPRITE_VERTEXES_COUNT];
static T_UINT16 SPRITE_INDICES[SPRITE_VERTEX_INDICES_COUNT];

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
    for (T_UINT16 i = 0; i < SPRITE_VERTEX_INDICES_COUNT; ++i)
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
      SPRITE_INDICES[i] = temp[vertexIndex][vertexTexIndex];
    }
    SPRITE_VERTEXES_INITIALIZED = true;
  }
}

MeshData* MeshFactory::Sprite::Create()
{
  Initialize();
  MeshData* ret = new MeshData();
  using namespace Graphics;
  ret->vertex_count_ = SPRITE_VERTEXES_COUNT;
  ret->vertex_format_ = Graphics::V_FORMAT_PU;
  ret->vertex_size_ = CalcVertexSize(ret->vertex_format_);
  ret->data_ = new unsigned char[ret->vertex_count_ * ret->vertex_size_]();
  unsigned char* p = ret->data_;
  for (T_UINT32 i = 0; i < SPRITE_VERTEXES_COUNT; ++i)
  {
    SetVertexPosition(SPRITE_VERTEXES[i], &p);
    SetVertexUv(SPRITE_UVS[i], &p);
  }
  ret->index_count_ = SPRITE_VERTEX_INDICES_COUNT;
  ret->indices_ = new T_UINT32[ret->index_count_]();
  for (T_UINT32 i = 0; i < SPRITE_VERTEX_INDICES_COUNT; ++i)
  {
    ret->indices_[i] = SPRITE_INDICES[i];
  }

  ret->submesh_count_ = 1;
  ret->submesh_index_counts_ = new T_UINT32[ret->submesh_count_];
  ret->submesh_index_counts_[0] = ret->index_count_;
  ret->submesh_polygon_counts_ = new T_UINT32[ret->submesh_count_];
  ret->submesh_polygon_counts_[0] = PRIMITIVE_SURF_NUM(PRIMITIVE_TRIANGLES, SPRITE_VERTEX_INDICES_COUNT);
  return ret;
}
