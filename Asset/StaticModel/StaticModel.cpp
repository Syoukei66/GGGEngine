#include "StaticModel.h"

#include <Asset/Mesh/Mesh.h>
#include <Asset/Material/Material.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(rcStaticModel, const StaticModelData& data)
{
  this->mesh_ = rcMesh::Create(data.mesh_);
  for (T_FIXED_UINT32 material_unique_id : data.material_unique_ids_)
  {
    this->materials_.emplace_back(AssetManager::Load<rcMaterial>(material_unique_id));
  }
  return true;
}
