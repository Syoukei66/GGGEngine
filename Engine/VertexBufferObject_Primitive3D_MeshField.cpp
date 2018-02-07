#include "VertexBufferObject_Primitive3D_MeshField.h"

// =================================================================
// Constructor / Destructor
// =================================================================
VertexBufferObject_Primitive3D_MeshField::VertexBufferObject_Primitive3D_MeshField(T_FLOAT width, T_FLOAT height, T_UINT16 x_num, T_UINT16 y_num)
{
  //Vertex
  this->vertexes_count_ = x_num * y_num * 4;

  T_FLOAT ux = width / x_num;
  T_FLOAT uy = height / y_num;

  this->vertexes_ = new Vertex::VNCT[this->vertexes_count_];
  for (T_UINT16 y = 0; y < y_num; ++y)
  {
    for (T_UINT16 x = 0; x < x_num; ++x)
   {
      T_UINT16 i = y * x_num * 4 + x * 4;
      Vertex::VNCT* v0 = &this->vertexes_[i + 0];
      Vertex::VNCT* v1 = &this->vertexes_[i + 1];
      Vertex::VNCT* v2 = &this->vertexes_[i + 2];
      Vertex::VNCT* v3 = &this->vertexes_[i + 3];

      v0->coord[0] = x * ux - width * 0.5f;
      v0->coord[1] = y * uy - height * 0.5f;
      v0->normal[0] = 0.0f;
      v0->normal[1] = 0.0f;
      v0->normal[2] = -1.0f;
      v0->uv[0] = 1.0f;
      v0->uv[1] = 1.0f;

      v1->coord[0] = x * ux - width * 0.5f;
      v1->coord[1] = y * uy + uy - height * 0.5f;
      v1->normal[0] = 0.0f;
      v1->normal[1] = 0.0f;
      v1->normal[2] = -1.0f;
      v1->uv[0] = 1.0f;
      v1->uv[1] = 0.0f;

      v2->coord[0] = x * ux + ux - width * 0.5f;
      v2->coord[1] = y * uy - height * 0.5f;
      v2->normal[0] = 0.0f;
      v2->normal[1] = 0.0f;
      v2->normal[2] = -1.0f;
      v2->uv[0] = 0.0f;
      v2->uv[1] = 1.0f;

      v3->coord[0] = x * ux + ux - width * 0.5f;
      v3->coord[1] = y * uy + uy - height * 0.5f;
      v3->normal[0] = 0.0f;
      v3->normal[1] = 0.0f;
      v3->normal[2] = -1.0f;
      v3->uv[0] = 0.0f;
      v3->uv[1] = 0.0f;
    }
  }

  //Index
  this->indexes_count_ = x_num * y_num * 4 + (y_num - 1) * 2;
  this->indexes_ = new T_UINT16[this->indexes_count_];

  T_UINT16 step = 0;
  for (T_UINT16 y = 0; y < y_num; ++y)
  {
    T_UINT16 i = (x_num * 4 + 2) * y;

    for (T_UINT16 x = 0; x < x_num; ++x)
    {
      //
      this->indexes_[i + x * 4 + 0] = (i - step) + x * 4 + 0;
      this->indexes_[i + x * 4 + 1] = (i - step) + x * 4 + 1;
      this->indexes_[i + x * 4 + 2] = (i - step) + x * 4 + 2;
      this->indexes_[i + x * 4 + 3] = (i - step) + x * 4 + 3;
    }

    if (y != y_num - 1)
    {
      //現在の段の最後と次の段の先頭のインデックスを取る
      this->indexes_[i + x_num * 4 + 0] = this->indexes_[i + x_num * 4 - 1];
      this->indexes_[i + x_num * 4 + 1] = (x_num * 4 + 2) * (y + 1) - (step + 2);
      //縮退用に余分にとったインデックスを記録しておく
      step += 2;
    }
  }
}

VertexBufferObject_Primitive3D_MeshField::~VertexBufferObject_Primitive3D_MeshField()
{
  delete[] this->vertexes_;
  delete[] this->indexes_;
}

void VertexBufferObject_Primitive3D_MeshField::OnInit()
{
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void VertexBufferObject_Primitive3D_MeshField::OnUpdateCoord(GameObject* entity)
{
}

T_UINT32 VertexBufferObject_Primitive3D_MeshField::GetVertexesCount() const
{
  return this->indexes_count_;
}

const void* VertexBufferObject_Primitive3D_MeshField::GetVertexes() const
{
  return this->vertexes_;
}

const T_UINT16* VertexBufferObject_Primitive3D_MeshField::GetIndexes() const
{
  return this->indexes_;
}

INativeProcess_Graphics::PrimitiveType VertexBufferObject_Primitive3D_MeshField::GetPrimitiveType()
{
  return INativeProcess_Graphics::PRIMITIVE_TRIANGLESTRIP;
}

Vertex::VertexType VertexBufferObject_Primitive3D_MeshField::GetVertexType()
{
  return Vertex::VERTEX_TYPE_VNCT;
}
