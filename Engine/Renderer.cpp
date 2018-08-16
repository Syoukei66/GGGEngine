#include "Renderer.h"

#include "EngineInitializeSetting.h"
#include "GameObjectRenderState.h"
#include "Camera.h"
#include "GameObject.h"

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
  state->AddQueue(this);
}

void Renderer::UniqueMaterial()
{
  T_UINT8 material_count = this->GetMaterialCount();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    this->materials_[i] = this->materials_[i]->InitialClone();
  }
}

void Renderer::Draw(GameObjectRenderState* state) const
{
  if (!this->SetStreamSource())
  {
    return;
  }
  //TODO:マルチパスレンダリングが間違えてるので要修正
  const T_UINT8 material_count = this->materials_.size();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    Material* material = this->materials_[i];
    T_UINT8 pass_count = material->Begin();
    for (T_UINT8 j = 0; j < pass_count; ++j)
    {
      material->BeginPass(j);
      this->SetDefaultProperties(state, material);
      material->CommitChanges();
      this->DrawSubset(i);
      material->EndPass();
    }
    material->End();
  }
}

void Renderer::SetDefaultProperties(GameObjectRenderState* state, Material* material) const
{
  this->SetProperties(material);

  rcShader* shader = material->GetShader();
  material->SetProperties(shader);

  //Materialをゲーム内処理から独立させる為、こちら側でプロパティの設定を行う
  shader->SetTexture("_MainTex", material->GetMainTexture());
  shader->SetBool("_IsBillbord", material->IsBillboard());

  shader->SetMatrix("_World", state->GetWorldMatrix());
  shader->SetMatrix("_WorldViewProj", state->GetWorldMatrix() * state->GetViewProjMatrix());

  shader->SetVec4f("_CameraPosition", state->GetCamera()->GetEntity()->GetWorldMatrix().GetPosition4d());
  shader->SetVec3f("_CameraDirection", state->GetCamera()->GetEntity()->GetWorldMatrix().GetDirection3d());
}
