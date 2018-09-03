#pragma once

#include <unordered_map>
#include <string>
#include "NativeType.h"
#include "Geometry.h"
#include "TextureRegion.h"

class rcTextureAtlas : public Resource
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static rcTextureAtlas* CreateWithAtlasFile(const char* path);
  static rcTextureAtlas* Create(const rcTexture* texture);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcTextureAtlas(const rcTexture* texture);
  virtual ~rcTextureAtlas();

  // =================================================================
  // Method
  // =================================================================
public:
  void Register(const std::string& path, rcTextureRegion* region);

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline rcTextureRegion* GetTextureRegion(const std::string& path)
  {
    return this->region_map_[path];
  }
  inline const rcTextureRegion* GetTextureRegion(const std::string& path) const
  {
    return this->region_map_.at(path);
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const rcTexture* texture_;
  std::unordered_map<std::string, rcTextureRegion*> region_map_;
};
