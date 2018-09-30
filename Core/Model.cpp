#include "Model.h"
#include "AssetManager.h"

// =================================================================
// Factory Method
// =================================================================
rcModel* rcModel::CreateFromFile(const char* path)
{
  return rcModel::Create(ModelData::Deserialize(path));
}

rcModel* rcModel::Create(const ModelData* data)
{
  rcModel* ret = new rcModel(data);
  ret->Resource::Init();
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcModel::rcModel(const ModelData* data)
{
  this->mesh_ = AssetManager::GetAsset<rcMesh>(data->mesh_unique_id_)->CreateFromFile();
  T_UINT32 submesh_count = this->mesh_->GetSubmeshCount();
  this->materials_ = new rcMaterial*[submesh_count]();
  for (T_UINT32 i = 0; i < submesh_count; ++i)
  {
    this->materials_[i] = AssetManager::GetAsset<rcMaterial>(data->material_unique_ids_[i])->CreateFromFile();
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
