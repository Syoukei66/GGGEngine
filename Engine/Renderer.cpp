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

void Renderer::Draw(GameObjectRenderState* state)
{
  const T_UINT8 material_count = this->materials_.size();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    Material* material = this->materials_[i];
    T_UINT8 pass_count = material->Begin();
    for (T_UINT8 j = 0; j < pass_count; ++j)
    {
      material->BeginPass(j);
      material->SetDefaultProperties(state);
      this->EditProperty(i, j, material);
      material->CommitChanges();
      this->DrawSubset(i, j);
      material->EndPass();
    }
    material->End();
  }
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
    this->materials_.push_back(nullptr);
  }
  this->materials_[0] = &material;
}
