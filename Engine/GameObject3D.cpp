#include "GameObject3D.h"
#include "RenderState.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameObject3D::GameObject3D()
{
  this->transform_ = new Transform3D(this);
  this->transform_->Init();
}

GameObject3D::~GameObject3D()
{
  delete this->transform_;
}
