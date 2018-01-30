#include "Shape.h"

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void Shape::Init()
{
  GameObject2D::Init();
  this->GetVbo()->Init();
}

void Shape::Update()
{
  IVertexBufferObject* vbo = this->GetVbo();
  vbo->UpdateCoord(this);
  GameObject2D::Update();
}

// =================================================================
// Method
// =================================================================
void Shape::OnVertexCoordChanged()
{
  this->GetVbo()->OnVertexCoordDirty();
}

// =================================================================
// setter/getter
// =================================================================
void Shape::SetSize(const TSizef & size)
{
  if (this->size_ == size)
  {
    return;
  }
  this->size_ = size;
  this->OnVertexCoordChanged();
}

void Shape::SetSize(T_FLOAT width, T_FLOAT height)
{
  if (this->size_.width == width && this->size_.height == height)
  {
    return;
  }
  this->size_.width = width;
  this->size_.height = height;
  this->OnVertexCoordChanged();
}

void Shape::SetWidth(T_FLOAT width)
{
  if (this->size_.width == width)
  {
    return;
  }
  this->size_.width = width;
  this->OnVertexCoordChanged();
}

void Shape::SetHeight(T_FLOAT height)
{
  if (this->size_.height == height)
  {
    return;
  }
  this->size_.height = height;
  this->OnVertexCoordChanged();
}
