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
  static UniqueResource<rcTextureAtlas> CreateFromFile(const char* path);
  static UniqueResource<rcTextureAtlas> Create(const SharedRef<const rcTexture>& texture);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcTextureAtlas(const SharedRef<const rcTexture>& texture);
  virtual ~rcTextureAtlas();

  // =================================================================
  // Method
  // =================================================================
public:
  void Register(const std::string& path, const SharedRef<rcTextureRegion>& region);

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline virtual const char* GetResourceName() override
  {
    return "TextureAtlas";
  }
  inline SharedRef<rcTextureRegion> GetTextureRegion(const std::string& path)
  {
    return this->region_map_[path];
  }
  inline SharedRef<const rcTextureRegion> GetTextureRegion(const std::string& path) const
  {
    return this->region_map_.at(path);
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  SharedRef<const rcTexture> texture_;
  std::unordered_map<std::string, SharedRef<rcTextureRegion>> region_map_;
};
