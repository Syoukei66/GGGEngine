#include "GameObject2D.h"
#include "GameObjectRenderState.h"

#include <Engine/Component/Modifier/EntityModifierManager.h>
#include <Engine/GameObject/Transform/Transform2D.h>

// =================================================================
// Constructor / Destructor
// =================================================================
GG_INIT_FUNC_IMPL(GameObject2D)
{
  return GameObject2D::Init("GameObject2D");
}

GG_INIT_FUNC_IMPL_1(GameObject2D, const std::string& name)
{
  this->transform_ = new Transform2D(this);
  this->transform_->Init();
  return GameObject::Init(name);
}

GG_DESTRUCT_FUNC_IMPL(GameObject2D)
{
  delete this->transform_;
  return true;
}

// =================================================================
// Methods
// =================================================================
void GameObject2D::RegisterEntityModifier(EntityModifierRoot* root)
{
  root->OnAttached(this);
}

void GameObject2D::UnregisterEntityModifier(EntityModifierRoot* root)
{
  if (root->GetTargetEntity() != this)
  {
    return;
  }
  root->OnDetached();
}

void GameObject2D::ClearEntityModifiers()
{
  EntityModifierManager::ClearModifiersWithTargetEntity(this);
}
