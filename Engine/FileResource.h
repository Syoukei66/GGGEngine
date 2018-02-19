#pragma once

#include "NativeAssert.h"
#include "FileLoader.h"
#include "ResourcePool.h"

template<class T>
class FileResource : public FileLoader
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  FileResource(const char* category, const char* path)
    : FileLoader(category, path)
    , obj_(nullptr)
  {}
  virtual ~FileResource()
  {
    delete this->obj_;
  }

  // =================================================================
  // Methods
  // =================================================================
public:
  void LoadProcess(const std::string& path) override
  {
    this->obj_ = this->NativeLoadProcess(path);
  }
  void UnloadProcess()
  {
    delete this->obj_;
    this->obj_ = nullptr;
  }

protected:
  virtual T* NativeLoadProcess(const std::string& path) = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline bool IsLoaded() const override
  {
    return this->obj_;
  }
  inline T* GetContents() const
  {
#ifdef _DEBUG
    NATIVE_ASSERT(this->obj_, "リソースがロードされていません");
#endif
    return this->obj_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T* obj_;
};