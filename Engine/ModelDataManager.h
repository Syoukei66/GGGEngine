#pragma once

#include "ModelData.h"
#include "ResourcePool.h"

class ModelDataManager : public ResourcePool<T_UINT8, ModelData>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelDataManager();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
protected:
  virtual ModelData* PreLoadProcess(const T_UINT8& key) override;
  virtual ModelData* LoadProcess(const T_UINT8& key, ModelData* value) override;
  virtual void PreUnloadProcess(const T_UINT8& key, ModelData* value) override;
  virtual void UnloadProcess(const T_UINT8& key, ModelData* value) override;

  // =================================================================
  // Methods
  // =================================================================
public:
  void RegisterPath(T_UINT8 id, const char* path);

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::map<T_UINT8, std::string> paths_;
};
