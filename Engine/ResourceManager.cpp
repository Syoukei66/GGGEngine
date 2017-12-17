#include "ResourceManager.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ResourceManager::ResourceManager()
  : entity_modifier_manager_(nullptr)
  , texture_palette_manager_(nullptr)
  , particle_data_manager_(nullptr)
  , spine_data_manager_(nullptr)
  , model_data_manager_(nullptr)
{
}

ResourceManager::~ResourceManager()
{
  delete this->texture_palette_manager_;
}

void ResourceManager::Init(EntityModifierAllocateOption* option)
{
  this->entity_modifier_manager_ = new EntityModifierManager(option);
  this->texture_palette_manager_ = new TexturePaletteManager();
  this->particle_data_manager_ = new ParticleDataManager();
  this->spine_data_manager_ = new SpineDataManager();
  this->model_data_manager_ = new ModelDataManager();
}

void ResourceManager::Uninit()
{
  delete this->entity_modifier_manager_;
  delete this->texture_palette_manager_;
  delete this->particle_data_manager_;
  delete this->spine_data_manager_;
  delete this->model_data_manager_;

  this->entity_modifier_manager_ = nullptr;
  this->texture_palette_manager_ = nullptr;
  this->particle_data_manager_ = nullptr;
  this->spine_data_manager_ = nullptr;
  this->model_data_manager_ = nullptr;
}

void ResourceManager::Update(T_UINT32 millisecond_elapsed)
{
  this->entity_modifier_manager_->OnUpdate(1);
}

// =================================================================
// Method
// =================================================================
void ResourceManager::RealizeResources(const ResourceLoadOrder& order, IResourceLoadingListener* listener)
{
  for (std::set<T_UINT8>::iterator itr = order.load_palette_id.begin(); itr != order.load_palette_id.end(); ++itr)
  {
    this->texture_palette_manager_->ReserveLoad(*itr);
  }

  listener->OnLoadingInit();

  this->particle_data_manager_->Load();
  this->spine_data_manager_->Load();
  this->texture_palette_manager_->PreRealize(listener);

  listener->OnLoadingStarted();

  this->particle_data_manager_->Load();
  this->spine_data_manager_->Load();
  this->texture_palette_manager_->Realize(listener);

  listener->OnLoadingFinished();
}
