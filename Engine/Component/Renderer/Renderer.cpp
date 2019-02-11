#include "Renderer.h"

#include <Engine/GameObject/GameObjectRenderState.h>
#include <Engine/GameObject/GameObject.h>
#include <Engine/Component/Camera/Camera.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(Renderer, GameObject* obj)
{
  this->builtin_variable_buffer_ = rcConstantBuffer::Create(
    Shader::ConstantBufferId::kRendererBuiltin,
    sizeof(ShaderBuiltinData)
  );
  return GameComponent::Init(obj);
}

// =================================================================
// Methods
// =================================================================
void Renderer::ReserveDraw(GameObjectRenderState* state)
{
  if (!this->IsEnabled())
  {
    return;
  }
  if (!state->IsTargetedLayer(this->layer_id_))
  {
    return;
  }
  if (!this->HasMaterial())
  {
    return;
  }
  state->AddQueue(this);
}

void Renderer::Draw(GameObjectRenderState* state) const
{
  if (!this->SetStreamSource())
  {
    return;
  }

  this->builtin_variable_.mat_mvp = this->GetObject()->GetTransform()->GetWorldMatrix() * state->GetViewProjMatrix();
  this->builtin_variable_.mat_mv = this->GetObject()->GetTransform()->GetWorldMatrix() * state->GetViewMatrix();
  this->builtin_variable_.mat_t_mv = this->builtin_variable_.mat_mv.Transpose();
  this->builtin_variable_.mat_it_mv = this->builtin_variable_.mat_t_mv.Inverse();
  this->builtin_variable_.obj_to_world = this->GetObject()->GetTransform()->GetWorldMatrix();
  this->builtin_variable_.world_to_obj = this->GetObject()->GetTransform()->GetWorldMatrix().Inverse();
  this->builtin_variable_buffer_->CommitChanges(&this->builtin_variable_);

  //TODO:マルチパスレンダリングになるよう修正する必要がある。
  //レンダリングパス毎にオブジェクトをソートする必要がある。
  const T_UINT8 material_count = this->GetMaterialCount();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    const SharedRef<const rcMaterial>& material = this->GetMaterial(i);
    const SharedRef<rcShader>& shader = material->GetShader();
    this->BeginPass(0, shader);
    material->SetBuffer();
    this->builtin_variable_buffer_->SetBuffer();
    state->SetConstantBuffer();
    Application::GetUpdateEventState().SetConstantBuffer();
    this->DrawSubset(i);
  }
}

//void Renderer::SetDefaultProperties(GameObjectRenderState* state, const SharedRef<rcShader>& shader) const
//{
//  shader->SetVec4f("_CameraPosition", state->GetCamera()->GetObject()->GetTransform()->GetWorldMatrix().GetPosition4d());
//  shader->SetVec3f("_CameraDirection", state->GetCamera()->GetObject()->GetTransform()->GetWorldMatrix().GetDirection3d());
//}

void Renderer::SetMaterial(const SharedRef<rcMaterial>& material, T_UINT16 index)
{
  this->materials_[index] = material;
  this->shared_materials_[index] = material;
}

SharedRef<rcMaterial> Renderer::GetMaterial(T_UINT16 index)
{
  const auto& itr = this->materials_.find(index);
  if (itr != this->materials_.end())
  {
    return itr->second;
  }
  SharedRef<rcMaterial> ret = this->shared_materials_[index]->Clone();
  this->materials_[index] = ret;
  return this->materials_.at(index);
}

SharedRef<const rcMaterial> Renderer::GetMaterial(T_UINT16 index) const
{
  const auto& itr = this->materials_.find(index);
  if (itr != this->materials_.end())
  {
    return itr->second;
  }
  return this->shared_materials_.at(index);
}
