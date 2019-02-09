#include "ShaderViewerBehavior.h"
#include <Engine/GameObject/Transform/Transform3D.h>
#include <Constants/Extensions.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(ShaderViewerBehavior)
{
  this->path_.resize(1024);
  this->obj_ = TestMesh::Create();  return true;
}

// =================================================================
// Methods from AssetViewerBehavior
// =================================================================
void ShaderViewerBehavior::OnStart(Scene* scene)
{
  scene->AddChild(this->obj_);
}

void ShaderViewerBehavior::OnEnd()
{
  this->obj_->RemoveSelf();
}

void ShaderViewerBehavior::OnLoad(T_UINT32 unique_id)
{
  const SharedRef<AssetEntity>& entity = this->GetEntity();
  const ShaderData& data = *entity->GetData<ShaderData>();
  MaterialData material_data = MaterialData();
  MaterialData::CreateWithShader(data.properties_, unique_id, &material_data);
  const SharedRef<Renderer>& renderer = this->obj_->GetComponent<Renderer>();
  renderer->SetMaterial(this->material_edit_view_.CreateEditMaterial(material_data));
}

void ShaderViewerBehavior::OnUnload()
{
}

void ShaderViewerBehavior::OnUpdate(const ActivityContext& activity_context)
{
  this->obj_->EditWithImGUI(activity_context);
  this->material_edit_view_.Update();

  ImGui::Begin(activity_context, u8"マテリアル設定", 10.0f, 0.0f, 0.35f, 0.25f, 0.65f);
  this->material_edit_view_.EditWithImGui();
  ImGui::InputText(u8"出力パス", this->path_.data(), this->path_.size());
  if (ImGui::Button(u8"保存"))
  {
    std::string path = FileUtil::CreateInputPath(std::string(this->path_.data())) + "." + Extensions::MATERIAL;
    FileUtil::PrepareDirectory(path);
    CerealIO::Json::Export<MaterialData>(path.c_str(), &this->material_edit_view_.GetEditData());
  }
  ImGui::End();
}
