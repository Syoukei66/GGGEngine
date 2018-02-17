#pragma once

#include <string>
#include "NativeType.h"
#include "ResourceLoader.h"

class FileLoader : public ResourceLoader
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  FileLoader(const std::string& category, const std::string& path);
  virtual ~FileLoader() {}

  // =================================================================
  // Methods
  // =================================================================
public:
  void Load() override;
  void Unload() override;

  void Retain();
  void Release();

protected:
  virtual void LoadProcess(const std::string& path) = 0;
  virtual void UnloadProcess() = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual bool IsLoaded() const = 0;

  inline const std::string& GetPath() const
  {
    return this->path_;
  }

  inline T_INT16 GetReferenceCount() const
  {
    return this->reference_count_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const std::string path_;
  T_INT16 reference_count_;

};