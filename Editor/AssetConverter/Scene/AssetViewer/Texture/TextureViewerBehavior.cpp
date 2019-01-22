#include "TextureViewerBehavior.h"
#include <Engine/GameObject/Transform/Transform3D.h>

enum MeshMode
{
  kQuad,
  kHugeQuad,
  kShpere,
  kHugeSphere,
  kSkyDome,
  kPlane,
};

static const std::vector<const char*> MESH_MODES = std::vector<const char*>
{
  u8"Quad",
  u8"HugeQuad",
  u8"Sphere",
  u8"HugeSphere",
  u8"SkyDome",
  u8"Plane",
};

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(TextureViewerBehavior)
{
  this->obj_ = GameObject3D::Create();
  this->mesh_renderer_ = this->obj_->AddComponent<MeshRenderer>();
  return true;
}

// =================================================================
// Methods from AssetViewerBehavior
// =================================================================
void TextureViewerBehavior::OnStart(Scene* scene)
{
  scene->AddChild(this->obj_);
}

void TextureViewerBehavior::OnEnd()
{
  this->obj_->RemoveSelf();
}

SharedRef<rcDynamicMesh> CreateMesh(T_UINT32 mode)
{
  T_UINT32 format = Vertex::V_FORMAT_PU;
  switch (mode)
  {
  case kQuad:
    return MeshFactory::Plane::Create(format, 1.0f, 1.0f);
  case kHugeQuad:
    return MeshFactory::Plane::Create(format, 100.0f, 100.0f, 100, 100, 100, 100);
  case kShpere:
    return MeshFactory::UVSphere::Create(format, 1.0f);
  case kHugeSphere:
    return MeshFactory::UVSphere::Create(format, 10.0f, 10);
  case kSkyDome:
    return MeshFactory::UVSphere::Create(format, 100.0f, 1, 1, true);
  case kPlane:
    return MeshFactory::Plane::Create(format, 100.0f, 100.0f, 100, 100, 100, 100, TVec3f::right, TVec3f::back);
  }
  return nullptr;
}

void TextureViewerBehavior::OnLoad(T_UINT32 unique_id)
{
  const T_UINT32 mesh_count = MESH_MODES.size();
  for (T_UINT32 i = 0; i < mesh_count; ++i)
  {
    const SharedRef<rcDynamicMesh>& mesh = CreateMesh(i);
    mesh->CommitChanges();
    this->meshes_.emplace_back(mesh);
  }
  this->mesh_renderer_->SetMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_UNLIT));
  this->mesh_renderer_->GetMaterial()->SetMainTexture(AssetManager::Load<rcTexture>(unique_id));
  this->UpdateMesh();
}

void TextureViewerBehavior::OnUnload()
{
  this->mesh_renderer_->SetMesh(nullptr);
  this->mesh_renderer_->SetMaterial(nullptr);
}

void TextureViewerBehavior::OnUpdate()
{
  ImGui::SetNextWindowPos(ImVec2(1000, 20), ImGuiCond_Once);
  ImGui::SetNextWindowSize(ImVec2(200, 400), ImGuiCond_Once);
  ImGui::Begin(u8"メッシュ設定");
  ImGui::Combo(u8"メッシュタイプ", &this->mesh_mode_, MESH_MODES.data(), MESH_MODES.size());
  if (ImGui::Button(u8"適用"))
  {
    this->UpdateMesh();
  }
  ImGui::End();
}

void TextureViewerBehavior::UpdateMesh()
{
  this->mesh_renderer_->SetMesh(this->meshes_[this->mesh_mode_]);
}
