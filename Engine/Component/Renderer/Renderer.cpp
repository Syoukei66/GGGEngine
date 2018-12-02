#include "Renderer.h"

#include <Engine/GameObject/GameObjectRenderState.h>
#include <Engine/GameObject/GameObject.h>
#include <Engine/Component/Camera/Camera.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(Renderer, GameObject* obj)
{
  return GameComponent::Init(obj);
}

// =================================================================
// Methods
// =================================================================
void Renderer::ReserveDraw(GameObjectRenderState* state)
{
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
  //TODO:マルチパスレンダリングが間違えてるので要修正
  const T_UINT8 material_count = this->GetMaterialCount();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    const SharedRef<const rcMaterial>& material = this->GetMaterial(i);
    const SharedRef<rcShader>& shader = material->GetShader();
    if (!shader)
    {
      continue;
    }
    shader->SetTexture("_MainTex", material->GetMainTexture());
    material->SetProperties(shader);
    if (!this->SetInputFormat(shader))
    {
      return;
    }
    T_UINT8 pass_count = shader->Begin();
    for (T_UINT8 j = 0; j < pass_count; ++j)
    {
      shader->BeginPass(j);
      this->SetDefaultProperties(state, shader);
      shader->CommitChanges();
      this->DrawSubset(i);
      shader->EndPass();
    }
    shader->End();
  }
}

void Renderer::SetDefaultProperties(GameObjectRenderState* state, const SharedRef<rcShader>& shader) const
{
  this->SetProperties(shader);

  //rcMaterialをゲーム内処理から独立させる為、こちら側でプロパティの設定を行う
  shader->SetMatrix("_World", state->GetWorldMatrix());
  shader->SetMatrix("_WorldViewProj", state->GetWorldMatrix() * state->GetViewProjMatrix());

  shader->SetVec4f("_CameraPosition", state->GetCamera()->GetObject()->GetTransform()->GetWorldMatrix().GetPosition4d());
  shader->SetVec3f("_CameraDirection", state->GetCamera()->GetObject()->GetTransform()->GetWorldMatrix().GetDirection3d());
}

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
