#include "FileLoader.h"

// =================================================================
// Constructor / Destructor
// =================================================================
FileLoader::FileLoader(const std::string& category, const std::string& path)
  : ResourceLoader(category)
  , path_(path)
  , reference_count_(0)
{}

// =================================================================
// Methods
// =================================================================
void FileLoader::Load()
{
  if (this->IsLoaded())
  {
    return;
  }
  this->LoadProcess(this->path_);
}

void FileLoader::Unload()
{
  if (!this->IsLoaded())
  {
    return;
  }
  this->UnloadProcess();
}

void FileLoader::Retain()
{
  this->reference_count_++;
}

void FileLoader::Release()
{
  this->reference_count_--;
}
