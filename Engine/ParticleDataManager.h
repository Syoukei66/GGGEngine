#pragma once

#include <vector>
#include "TextureAtlas.h"
#include "ParticleData.h"

/*
  TODO:ResourceŠÇ—•û–@‚Ì•ÏX–¢‘Î‰ž
*/
class ParticleDataManager
{
public:
  ParticleDataManager();
  ~ParticleDataManager();

public:
  void Init(T_UINT8 size, const char* atlas_path);
  void Register(T_UINT8 id, const char* path);
  void Uninit();

  void Load();
  void Unload();

public:
  inline T_UINT8 GetDataCount() const
  {
    return this->size_;
  }
  inline const ParticleData* GetData(T_UINT8 id) const
  {
    return this->datas_[id];
  }

private:
  bool is_already_loaded_;
  const char* atlas_path_;
  TextureAtlas* texture_atlas_;
  T_UINT8 size_;
  char** paths_;
  ParticleData** datas_;
};
