#include "MaterialViewerBehavior.h"
#include <Entity/File/Material/MaterialAssetConverterSetting.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(MaterialViewerBehavior)
{
  this->obj_ = TestMesh::Create();
  return true;
}

// =================================================================
// Methods from AssetViewerBehavior
// =================================================================
void MaterialViewerBehavior::OnStart(Scene* scene)
{
  scene->AddChild(this->obj_);
}

void MaterialViewerBehavior::OnEnd()
{
  this->obj_->RemoveSelf();
}

void MaterialViewerBehavior::OnLoad(T_UINT32 unique_id)
{
  const SharedRef<AssetEntity>& entity = this->GetEntity();
  const SharedRef<Renderer>& renderer = this->obj_->GetComponent<Renderer>();
  const MaterialData* data = nullptr;
  this->edit_view_.Reload();
  if (this->edit_view_.IsMaster())
  {
    data = &this->edit_view_.GetEditData();
  }
  else
  {
    data = entity->GetData<MaterialData>();
  }
  renderer->SetMaterial(this->edit_view_.CreateEditMaterial(*data));
}

void MaterialViewerBehavior::OnUnload()
{
}

void MaterialViewerBehavior::OnUpdate(const ActivityContext& activity_context, AssetConverterContext* context)
{
  this->obj_->EditWithImGUI(activity_context);

  ImGui::Begin(activity_context, u8"ƒ}ƒeƒŠƒAƒ‹Ý’è", 10.0f, 0.0f, 0.35f, 0.25f, 0.65f);
  this->edit_view_.Update();
  if (this->edit_view_.EditWithImGui(this, context))
  {
    CerealIO::Json::Export<MaterialData>(this->GetEntity()->GetMetaData()->GetInputPath().c_str(), &this->edit_view_.GetEditData());
    //this->GetEntity()->GetMetaData()->GetConverterSetting()->SetDirty();
  }
  ImGui::End();
}
