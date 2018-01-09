#define _CRT_SECURE_NO_WARNINGS
#include "ParticleDataManager.h"
#include "Director.h"
#include "ParticleDataLoader.h"
#include "TextureAtlasLoader.h"

ParticleDataManager::ParticleDataManager()
{}

ParticleDataManager::~ParticleDataManager()
{}

void ParticleDataManager::Init(T_UINT8 size, const char* atlas_path)
{
  this->is_already_loaded_ = false;
  this->size_ = size;
  this->atlas_path_ = atlas_path;
  this->paths_ = new char*[size]();
  this->datas_ = new ParticleData*[size]();
  for (T_UINT8 i = 0; i < size; ++i)
  {
    this->paths_[i] = nullptr;
    this->datas_[i] = nullptr;
  }
}

void ParticleDataManager::Register(T_UINT8 id, const char* path)
{
  this->paths_[id] = new char[strlen(path) + 1]();
  strcpy(this->paths_[id], path);
}

void ParticleDataManager::Uninit()
{
  for (T_UINT8 i = 0; i < this->size_; ++i)
  {
    if (this->datas_[i])
    {
      delete this->datas_[i];
    }
    if (this->paths_[i])
    {
      delete[] this->paths_[i];
    }
  }
  delete[] this->datas_;
  delete[] this->paths_;
  this->size_ = 0;
  this->datas_ = nullptr;
  this->paths_ = nullptr;
  this->atlas_path_ = nullptr;
}

void ParticleDataManager::Load()
{
  //if (this->is_already_loaded_)
  //{
  //  return;
  //}
  //this->is_already_loaded_ = true;
  //char atlas_path[256] = {};
  //Director::GetInstance()->GetEngineOption()->asset_path.GetParticlePath("", atlas_path);
  //TextureAtlasLoader loader = TextureAtlasLoader();
  //this->texture_atlas_ = loader.Load(atlas_path, this->atlas_path_);


  //for (T_UINT8 i = 0; i < this->size_; ++i)
  //{
  //  char particle_path[256] = {};
  //  Director::GetInstance()->GetEngineOption()->asset_path.GetParticlePath(this->paths_[i], particle_path);
  //  const ParticleDataLoader* loader = ParticleDataLoader::DynamicLoad(particle_path);
  //  //TODO: Atlas‚ð‚È‚ñ‚Æ‚©‚µ‚Ä“Ç‚Ýž‚Ü‚¹‚é
  //  this->datas_[i] = loader->GetContents();
  //}
}

void ParticleDataManager::Unload()
{
  if (!this->is_already_loaded_)
  {
    return;
  }
  for (T_UINT8 i = 0; i < this->size_; ++i)
  {
    delete this->datas_[i];
    this->datas_[i] = nullptr;
  }
  this->is_already_loaded_ = false;
}
