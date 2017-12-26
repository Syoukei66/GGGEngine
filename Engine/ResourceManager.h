#pragma once

#include "EntityModifierManager.h"
#include "TexturePaletteManager.h"
#include "ParticleDataManager.h"
#include "SpineDataManager.h"
#include "ModelDataManager.h"

#include "ResourceLoadOrder.h"

class ResourceManager
{
public:
  static ResourceManager* GetInstance()
  {
    static ResourceManager self;
    return &self;
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
private:
  ResourceManager();

public:
  ~ResourceManager();

  // =================================================================
  // Method
  // =================================================================
public:
  void Init(EntityModifierAllocateOption* option);
  void Uninit();
  void Update(T_UINT32 millisecond_elapsed);
  void RealizeResources(const ResourceLoadOrder& order, IResourceLoadingListener* listener);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline EntityModifierManager* GetEntityModifierManager()
  {
    return this->entity_modifier_manager_;
  }

  inline TexturePaletteManager* GetTexturePaletteManager()
  {
    return this->texture_palette_manager_;
  }

  inline ParticleDataManager* GetParticleDataManager()
  {
    return this->particle_data_manager_;
  }
  
  inline SpineDataManager* GetSpineDataManager()
  {
    return this->spine_data_manager_;
  }

  inline ModelDataManager* GetModelDataManager()
  {
    return this->model_data_manager_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  EntityModifierManager* entity_modifier_manager_;

  TexturePaletteManager* texture_palette_manager_;
  ParticleDataManager* particle_data_manager_;
  SpineDataManager* spine_data_manager_;
  ModelDataManager* model_data_manager_;
};
