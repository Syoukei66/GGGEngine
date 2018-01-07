#include "ModelDataManager.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ModelDataManager::ModelDataManager()
  : ResourcePool("ModelData")
{}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
ModelData* ModelDataManager::PreLoadProcess(const T_UINT8& key)
{
  return new ModelData(this->paths_[key].c_str());
}

ModelData* ModelDataManager::LoadProcess(const T_UINT8& key, ModelData* value)
{
  value->Load();
  return value;
}

void ModelDataManager::PreUnloadProcess(const T_UINT8& key, ModelData* value)
{
}

void ModelDataManager::UnloadProcess(const T_UINT8& key, ModelData* value)
{
  value->Unload();
  delete value;
}

// =================================================================
// Methods
// =================================================================
void ModelDataManager::RegisterPath(T_UINT8 id, const char * path)
{
  this->paths_[id] = path;
}
