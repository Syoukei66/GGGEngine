#include "TestMesh.h"

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
    return MeshFactory::UVSphere::Create(format, 10.0f);
  case kSkyDome:
    return MeshFactory::UVSphere::Create(format, 1000.0f, 16, 32, true);
  case kPlane:
    return MeshFactory::Plane::Create(format, 100.0f, 100.0f, 100, 100, 100, 100, TVec3f::right, TVec3f::back);
  }
  return nullptr;
}
// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(TestMesh)
{
  const T_UINT32 mesh_count = (T_UINT32)MESH_MODES.size();
  for (T_UINT32 i = 0; i < mesh_count; ++i)
  {
    const SharedRef<rcDynamicMesh>& mesh = CreateMesh(i);
    mesh->CommitChanges();
    this->meshes_.emplace_back(mesh);
  }
  this->mesh_renderer_ = this->AddComponent<MeshRenderer>();
  this->UpdateMesh();
  return GameObject::Init();
}

// =================================================================
// Methods
// =================================================================
void TestMesh::EditWithImGUI(const ActivityContext& context)
{
  ImGui::Begin(context, u8"���b�V���ݒ�", 10.0f, 0.75f, 0.0f, 0.25f, 0.2f);
  ImGui::Combo(u8"���b�V���^�C�v", &this->mesh_mode_, MESH_MODES.data(), MESH_MODES.size());
  if (ImGui::Button(u8"�K�p"))
  {
    this->UpdateMesh();
  }
  ImGui::End();
}

void TestMesh::Load()
{
}

void TestMesh::Unload()
{
  this->mesh_renderer_->SetMaterial(nullptr);
}

void TestMesh::UpdateMesh()
{
  this->mesh_renderer_->SetMesh(this->meshes_[this->mesh_mode_]);
}
