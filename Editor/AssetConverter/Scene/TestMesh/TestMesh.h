#pragma once

#include <Engine/Component/Renderer/MeshRenderer.h>

class TestMesh : public GameObject3D
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(TestMesh);
  GG_CREATE_FUNC(TestMesh);

  // =================================================================
  // Methods
  // =================================================================
public:
  void EditWithImGUI();

private:
  void Load();
  void Unload();
  void UpdateMesh();

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<MeshRenderer> mesh_renderer_;

  T_INT32 mesh_mode_;
  std::vector<SharedRef<rcMesh>> meshes_;

};