#pragma once

#include <string>
#include "NativeModel.h"

class ModelData
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelData(const std::string& path);
  ~ModelData();

  // =================================================================
  // Methods
  // =================================================================
public:
  void Load();
  void Unload();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline bool IsLoaded() const
  {
    return this->native_model_;
  }
  inline const INativeModel* GetNativeModel() const
  {
    return this->native_model_;
  }
  inline const std::string& GetPath() const
  {
    return this->path_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::string path_;
  INativeModel* native_model_;
};
