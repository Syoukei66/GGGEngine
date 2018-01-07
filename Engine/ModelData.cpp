#include "ModelData.h"
#include "Director.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ModelData::ModelData(const std::string& path)
  : path_(path)
  , native_model_(nullptr)
{ 
}

ModelData::~ModelData()
{
  this->Unload();
}

// =================================================================
// Methods
// =================================================================
void ModelData::Load()
{
  if (this->IsLoaded())
  {
    return;
  }
  const AssetPath* asset_path = &Director::GetInstance()->GetEngineOption()->asset_path;
  char directory_path_cstr[256] = {};
  asset_path->GetModelPath(this->path_.c_str(), directory_path_cstr);
  this->native_model_ = INativeModel::Create(directory_path_cstr, this->path_.c_str());
}

void ModelData::Unload()
{
  if (!this->IsLoaded())
  {
    return;
  }
  delete this->native_model_;
  this->native_model_ = nullptr;
}
