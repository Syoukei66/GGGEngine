#include "CharacterModel.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(rcCharacterModel, const CharacterModelData& data)
{
  this->name_ = data.name_;
  this->root_node_ = data.root_node_;

  const size_t mesh_count = data.mesh_datas_.size();
  for (const CharacterMeshData& mesh_data : data.mesh_datas_)
  {
    this->meshes_.emplace_back(rcDynamicMesh::Create(mesh_data.data_));
  }
  for (T_FIXED_UINT32 mesh_material_index : data.mesh_material_indices_)
  {
    this->mesh_material_indices_.emplace_back(mesh_material_index);
  }
  for (T_FIXED_UINT32 material_unique_id : data.material_unique_ids_)
  {
    this->materials_.emplace_back(AssetManager::Load<rcMaterial>(material_unique_id));
  }
  return true;
}
