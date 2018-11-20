#include "CharacterModel.h"

#include <Asset/Mesh/Mesh.h>
#include <Asset/Material/Material.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(rcCharacterModel, const CharacterModelData& data)
{
  this->root_node_ = data.root_node_;

  const size_t mesh_count = data.mesh_unique_ids_.size();

  for (T_FIXED_UINT32 mesh_unique_id : data.mesh_unique_ids_)
  {
    this->meshes_.emplace_back(AssetManager::Load<rcMesh>(mesh_unique_id));
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
