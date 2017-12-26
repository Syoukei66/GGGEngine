#pragma once

#include <set>
#include "NativeType.h"

struct ResourceLoadOrder
{
  ResourceLoadOrder()
    : load_palette_id()
    , particle_load(false)
    , spine_load(false)
    , model_load(false)
  {}
  std::set<T_UINT8> load_palette_id;
  bool particle_load;
  bool spine_load;
  bool model_load;
};

class ResourceLoadOrderBuilder
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ResourceLoadOrderBuilder();

  // =================================================================
  // Method
  // =================================================================
public:
  inline ResourceLoadOrderBuilder* TexturePalette(T_UINT8 palette_id)
  {
    this->order_.load_palette_id.insert(palette_id);
    return this;
  }

  inline ResourceLoadOrderBuilder* ParticleData()
  {
    this->order_.particle_load = true;
    return this;
  }

  inline ResourceLoadOrderBuilder* SpineData()
  {
    this->order_.spine_load = true;
    return this;
  }

  inline ResourceLoadOrderBuilder* ModelData()
  {
    this->order_.model_load = true;
    return this;
  }

  inline const ResourceLoadOrder& GetOrder()
  {
    return this->order_;
  }

private:
  ResourceLoadOrder order_;
};