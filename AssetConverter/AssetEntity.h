#pragma once

#include "AssetInfo.h"

#define ENTITY_ID(id) public:\
static inline T_UINT32 ID()\
{\
  return id;\
}

class AssetEntity
{
protected:
  enum EntityID
  {
    ID_RAW,
  };

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetEntity(AssetInfo* info)
    : info_(info)
  {
  }
  virtual ~AssetEntity()
  {
    delete this->info_;
  }

  // =================================================================
  // Methods
  // =================================================================
public:

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline AssetInfo* GetInfo() const
  {
    return this->info_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetInfo* info_;

};