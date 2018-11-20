#include "GameObject3D.h"
#include "GameObjectRenderState.h"

#include <Engine/GameObject/Transform/Transform3D.h>
#include <Asset/Material/Material.h>

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
