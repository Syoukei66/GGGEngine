#include "VertexBufferObject_Primitive3D_Plane.h"

enum { PLANE_VERTEX_COORDS_COUNT = 4 };
static TVec2f PLANE_VERTEX_COORDS[PLANE_VERTEX_COORDS_COUNT] =
{
  { -0.5f, -0.5f }, //0 âEè„
  { -0.5f,  0.5f }, //1 âEâ∫
  {  0.5f, -0.5f }, //2 ç∂â∫
  {  0.5f,  0.5f }, //3 ç∂è„
};

enum { PLANE_VERTEX_TEX_COORDS_COUNT = PLANE_VERTEX_COORDS_COUNT };
static TVec2f PLANE_VERTEX_TEX_COORDS[PLANE_VERTEX_TEX_COORDS_COUNT] =
{
  { 0.0f, 0.0f },
  { 0.0f, 1.0f },
  { 1.0f, 0.0f },
  { 1.0f, 1.0f },
};

enum { PLANE_SURFS_COUNT = 1 };
enum { PLANE_TRIANGLES_COUNT = 2 * PLANE_SURFS_COUNT };
enum { PLANE_VERTEX_INDEXES_COUNT = 6 };
static const T_UINT16 PLANE_VERTEX_INDEXES[PLANE_VERTEX_INDEXES_COUNT] =
{
  0, 1, 2,
  1, 3, 2,
};

static const T_UINT16 PLANE_VERTEX_TEX_INDEXES[PLANE_VERTEX_INDEXES_COUNT] =
{
  0, 1, 2,
  1, 3, 2,
};

enum { PLANE_VERTEXES_COUNT = 4 * PLANE_SURFS_COUNT };
static bool PLANE_VERTEXES_INITIALIZED = false;
static Vertex::VCT PLANE_VERTEXES[PLANE_VERTEXES_COUNT];
static T_UINT16 PLANE_INDEXES[PLANE_VERTEX_INDEXES_COUNT];

VertexBufferObject_Primitive3D_Plane::VertexBufferObject_Primitive3D_Plane()
{
  if (!PLANE_VERTEXES_INITIALIZED)
  {
    T_INT16 temp[PLANE_VERTEX_COORDS_COUNT][PLANE_VERTEX_TEX_COORDS_COUNT] = {};
    T_UINT16 index = 0;
    for (T_UINT16 i = 0; i < PLANE_VERTEX_COORDS_COUNT; ++i)
    {
      for (T_UINT16 j = 0; j < PLANE_VERTEX_TEX_COORDS_COUNT; ++j)
      {
        temp[i][j] = -1;
      }
    }
    for (T_UINT16 i = 0; i < PLANE_VERTEX_INDEXES_COUNT; ++i)
    {
      T_UINT16 vertexIndex = PLANE_VERTEX_INDEXES[i];
      T_UINT16 vertexTexIndex = PLANE_VERTEX_TEX_INDEXES[i];
      TVec2f coord = PLANE_VERTEX_COORDS[vertexIndex];
      TVec2f uv = PLANE_VERTEX_TEX_COORDS[vertexTexIndex];
      if (temp[vertexIndex][vertexTexIndex] == -1)
      {
        PLANE_VERTEXES[index].coord[0] = coord.x;
        PLANE_VERTEXES[index].coord[1] = coord.y;
        PLANE_VERTEXES[index].uv[0] = uv.x;
        PLANE_VERTEXES[index].uv[1] = uv.y;
        temp[vertexIndex][vertexTexIndex] = index;
        index++;
      }
      PLANE_INDEXES[i] = temp[vertexIndex][vertexTexIndex];
    }
    PLANE_VERTEXES_INITIALIZED = true;
  }
}

void VertexBufferObject_Primitive3D_Plane::OnInit()
{
}

void VertexBufferObject_Primitive3D_Plane::OnUpdateCoord(GameObject* entity)
{
}

T_UINT32 VertexBufferObject_Primitive3D_Plane::GetVertexesCount() const
{
  return PLANE_VERTEX_INDEXES_COUNT;
}

const void* VertexBufferObject_Primitive3D_Plane::GetVertexes() const
{
  return PLANE_VERTEXES;
}

const T_UINT16* VertexBufferObject_Primitive3D_Plane::GetIndexes() const
{
  return PLANE_INDEXES;
}

INativeProcess_Graphics::PrimitiveType VertexBufferObject_Primitive3D_Plane::GetPrimitiveType()
{
  return INativeProcess_Graphics::PRIMITIVE_TRIANGLES;
}

Vertex::VertexType VertexBufferObject_Primitive3D_Plane::GetVertexType()
{
  return Vertex::VERTEX_TYPE_VCT;
}
