#include "Renderer.h"

#include "EngineInitializeSetting.h"
#include "GameObjectRenderState.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Renderer::Renderer(GameObject* entity)
  : entity_(entity)
  , layer_id_(EngineInitializeSetting::GetInstance().GetDefaultLayerId())
{
}

// =================================================================
// Method
// =================================================================
void Renderer::ReserveDraw(GameObjectRenderState* state)
{
  if (!state->IsTargetedLayer(this->layer_id_))
  {
    return;
  }
  Material* const material = this->GetMaterial();
  if (!material)
  {
    return;
  }
  if (material->GetZTestLevel() > 0)
  {
    state->AddZCheckOrder(material->GetZTestLevel(), this);
    return;
  }
  this->Draw(state);
}

void Renderer::UniqueMaterial()
{
  T_UINT8 material_count = this->GetMaterialCount();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    this->materials_[i] = this->materials_[i]->InitialClone();
  }
}

// =================================================================
// setter/getter
// =================================================================
void Renderer::SetMaterial(Material& material)
{
  if (this->materials_.size() == 0)
  {
    this->materials_.emplace_back(nullptr);
  }
  this->materials_[0] = &material;
}
