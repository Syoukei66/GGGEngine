#pragma once

#include "ParticleData.h"
#include "TextureAtlas.h"

#include "FileResource.h"

class ParticleDataLoader : public FileResource<ParticleData>
{
public:
  static const ParticleDataLoader* DynamicLoad(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ParticleDataLoader(const char* path);

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual ParticleData* NativeLoadProcess(const std::string& path) override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline void SetTextureAtlas(TextureAtlas* atlas)
  {
    this->atlas_ = atlas;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  TextureAtlas* atlas_;

};