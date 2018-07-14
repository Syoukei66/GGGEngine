#include "GameObject2D.h"
#include "RenderState.h"
#include "EntityModifier.h"
#include "EntityModifierManager.h"

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
// Method
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
  EntityModifierManager::GetInstance().ClearModifiersWithTargetEntity(this);
}
