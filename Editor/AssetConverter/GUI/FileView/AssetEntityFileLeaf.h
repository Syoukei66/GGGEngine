#pragma once

#include <Entity/AssetEntity.h>

class AssetEntityFileLeaf : public GGObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(AssetEntityFileLeaf);
  GG_CREATE_FUNC_1(AssetEntityFileLeaf, const SharedRef<AssetEntity>&);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<AssetEntity> GetEntity()
  {
    return this->entity_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<AssetEntity> entity_;

};
