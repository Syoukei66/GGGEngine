#include "VertexBufferObject_Primitive3D_Triangle.h"

enum { TRIANGLE_VERTEXES_COUNT = 3 };
static const Vertex::VC TRIANGLE_VERTEXES[TRIANGLE_VERTEXES_COUNT] =
{
  {  -0.5f,  0.5f,  0.0f }, //0
  {   0.5f,  0.5f,  0.0f }, //1
  {  -0.5f, -0.5f,  0.0f }, //2
};

enum { TRIANGLE_INDEXES_COUNT = 3 };
static const T_UINT16 TRIANGLE_INDEXES[TRIANGLE_INDEXES_COUNT] =
{
  0, 1, 2
};

VertexBufferObject_Primitive3D_Triangle::VertexBufferObject_Primitive3D_Triangle()
{
}

void VertexBufferObject_Primitive3D_Triangle::OnInit()
{
}

void VertexBufferObject_Primitive3D_Triangle::OnUpdateCoord(GameObject* entity)
{
}

T_UINT32 VertexBufferObject_Primitive3D_Triangle::GetVertexesCount() const
{
  return TRIANGLE_INDEXES_COUNT;
}

const void* VertexBufferObject_Primitive3D_Triangle::GetVertexes() const
{
  return TRIANGLE_VERTEXES;
}

const T_UINT16* VertexBufferObject_Primitive3D_Triangle::GetIndexes() const
{
  return TRIANGLE_INDEXES;
}

INativeProcess_Graphics::PrimitiveType VertexBufferObject_Primitive3D_Triangle::GetPrimitiveType()
{
  return INativeProcess_Graphics::PRIMITIVE_TRIANGLES;
}

Vertex::VertexType VertexBufferObject_Primitive3D_Triangle::GetVertexType()
{
  return Vertex::VERTEX_TYPE_VC;
}
