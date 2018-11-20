#include "GameObject3D.h"
#include "GameObjectRenderState.h"

#include <Engine/GameObject/Transform/Transform3D.h>
#include <Asset/Material/Material.h>

// =================================================================
// Constructor / Destructor
// =================================================================
GG_INIT_FUNC_IMPL(GameObject3D)
{
  this->transform_ = new Transform3D(this);
  this->transform_->Init();
  return GameObject::Init();
}

GG_DESTRUCT_FUNC_IMPL(GameObject3D)
{
  delete this->transform_;
  return true;
}
