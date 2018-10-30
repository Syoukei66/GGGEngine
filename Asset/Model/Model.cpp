#include "Model.h"

#include <Asset/Mesh/Mesh.h>
#include <Asset/Material/Material.h>

// =================================================================
// GGG Statement
// =================================================================
void rcModel::Init(const ModelData& data)
{
  this->mesh_ = AssetManager::Load<rcMesh>(data.mesh_unique_id_);
  const T_UINT8 submesh_count = this->mesh_->GetSubmeshCount();
  this->materials_.resize(submesh_count);
  for (T_UINT32 i = 0; i < submesh_count; ++i)
  {
    this->materials_[i] = AssetManager::Load<rcMaterial>(data.material_unique_ids_[i]);
  }
}
