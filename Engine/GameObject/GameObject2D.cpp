#include "GameObject2D.h"
#include "GameObjectRenderState.h"

#include <Engine/Component/Modifier/EntityModifierManager.h>
#include <Engine/GameObject/Transform/Transform2D.h>

// =================================================================
// Constructor / Destructor
// =================================================================
GameObject2D::GameObject2D()
{
  this->transform_ = new Transform2D(this);
  this->transform_->Init();
}

GameObject2D::~GameObject2D()
{
  delete this->transform_;
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
