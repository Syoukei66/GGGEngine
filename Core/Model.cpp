#include "Model.h"
#include "AssetManager.h"

// =================================================================
// Factory Method
// =================================================================
UniqueResource<rcModel> rcModel::CreateFromFile(const char* path)
{
  ModelData* data = ModelData::Deserialize(path);
  UniqueResource<rcModel> ret = rcModel::Create(data);
  delete data;
  return ret;
}

UniqueResource<rcModel> rcModel::Create(const ModelData* data)
{
  rcModel* ret = new rcModel(data);
  ret->Resource::Init();
  return UniqueResource<rcModel>(ret);
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcModel::rcModel(const ModelData* data)
{
  this->mesh_ = AssetManager::Load<rcMesh>(data->mesh_unique_id_);
  T_UINT8 submesh_count = this->mesh_->GetSubmeshCount();
  this->materials_ = new SharedRef<rcMaterial>[submesh_count]();
  for (T_UINT32 i = 0; i < submesh_count; ++i)
  {
    this->materials_[i] = AssetManager::Load<rcMaterial>(data->material_unique_ids_[i]);
  }
}

rcModel::~rcModel()
{
  delete[] this->materials_;
}
