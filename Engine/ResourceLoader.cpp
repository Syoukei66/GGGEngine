#include "ResourceLoader.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ResourceLoader::ResourceLoader(const std::string& category, const std::string& path)
  : category_(category)
  , path_(path)
{}

// =================================================================
// Methods
// =================================================================
void ResourceLoader::Load()
{
  if (this->IsLoaded())
  {
    return;
  }
  this->LoadProcess(this->path_);
}

void ResourceLoader::Unload()
{
  if (!this->IsLoaded())
  {
    return;
  }
  this->UnloadProcess();
}