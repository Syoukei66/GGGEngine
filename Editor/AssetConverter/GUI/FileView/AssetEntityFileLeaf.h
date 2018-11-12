#pragma once

#include <Entity/AssetEntity.h>

class AssetEntityFileLeaf : public GGObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT_NAME(AssetEntityFileLeaf);
  GG_CREATE_FUNC_1(AssetEntityFileLeaf, AssetEntity*);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE AssetEntity* GetEntity()
  {
    return this->entity_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetEntity* entity_;

};
