#include "Renderer.h"

#include "EngineInitializeSetting.h"
#include "RenderState.h"
#include "CommandBuffer.h"
#include "GameObject.h"
#include "Camera3D.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Renderer::Renderer(GameObject* entity)
  : GameComponent(entity)
  , layer_id_(EngineInitializeSetting::GetInstance().GetDefaultLayerId())
  , index_id_(0)
  , materials_()
  , billbording_(false)
{
}

// =================================================================
// Method
// =================================================================
void Renderer::UniqueMaterial()
{
  T_UINT8 material_count = this->GetMaterialCount();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    this->materials_[i] = this->materials_[i]->InitialClone();
  }
}

void Renderer::ManagedSubmit(CommandBuffer* buf) const
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
  if (this->billbording_)
  {
    const Matrix4x4& world_matrix = this->GetGameObject()->GetWorldMatrix();
    const TVec3f pos = world_matrix.GetPosition3d();
    const TVec3f camera_pos = state->GetViewMatrix().GetPosition3d();
    state->SetWorldMatrix(Matrix4x4::LookAt(pos, camera_pos, world_matrix.GetCameraYVec()));
  }
  else
  {
    state->SetWorldMatrix(this->GetGameObject()->GetWorldMatrix());
  }
  this->Draw(state);
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
