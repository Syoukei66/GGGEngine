#include "Model.h"

// =================================================================
// Constructor / Destructor
// =================================================================
rcModel::rcModel(rcMesh* mesh, rcMaterial** materials)
  : mesh_(mesh)
  , materials_(materials)
{
  this->mesh_->Retain();
  T_UINT8 material_count = this->GetMaterialCount();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    this->materials_[i]->Retain();
  }
}

rcModel::~rcModel()
{
  T_UINT8 material_count = this->GetMaterialCount();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    this->materials_[i]->Release();
  }
  this->mesh_->Release();
}
