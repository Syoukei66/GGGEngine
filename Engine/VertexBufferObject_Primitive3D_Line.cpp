#include "VertexBufferObject_Primitive3D_Line.h"

enum { LINE_VERTEXES_COUNT = 2 };
static const Vertex::VC LINE_VERTEXES[LINE_VERTEXES_COUNT] =
{
  { 0.0f, -0.5f,  0.0f },
  { 0.0f,  0.5f,  0.0f },
};

enum { LINE_INDEXES_COUNT = 2 };
static const T_UINT16 LINE_INDEXES[LINE_INDEXES_COUNT] =
{
  0, 1
};

VertexBufferObject_Primitive3D_Line::VertexBufferObject_Primitive3D_Line()
{
}

void VertexBufferObject_Primitive3D_Line::OnInit()
{
}

void VertexBufferObject_Primitive3D_Line::OnUpdateCoord(GameObject* entity)
{
}

T_UINT32 VertexBufferObject_Primitive3D_Line::GetVertexesCount() const
{
  return LINE_INDEXES_COUNT;
}

const void* VertexBufferObject_Primitive3D_Line::GetVertexes() const
{
  return LINE_VERTEXES;
}

const T_UINT16* VertexBufferObject_Primitive3D_Line::GetIndexes() const
{
  return LINE_INDEXES;
}

INativeProcess_Graphics::PrimitiveType VertexBufferObject_Primitive3D_Line::GetPrimitiveType()
{
  return INativeProcess_Graphics::PRIMITIVE_LINES;
}

Vertex::VertexType VertexBufferObject_Primitive3D_Line::GetVertexType()
{
  return Vertex::VERTEX_TYPE_VC;
}
