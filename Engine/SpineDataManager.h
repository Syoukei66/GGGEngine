#pragma once

#include <spine\SkeletonData.h>

#include "NativeType.h"
#include "EngineAttachmentLoader.h"
#include "SpineData.h"

class SpineDataManager
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  SpineDataManager();
  ~SpineDataManager();

  // =================================================================
  // Methods
  // =================================================================
public:
  void Init(T_UINT8 size);
  void Register(T_UINT8 id, const char* path);
  void Uninit();

  void Load();
  void Unload();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline T_UINT8 GetDataCount() const
  {
    return this->size_;
  }
  inline const SpineData* GetData(T_UINT8 id) const
  {
    return this->datas_[id];
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  bool is_already_loaded_;
  T_UINT8 size_;
  char** paths_;
  SpineData** datas_;
};