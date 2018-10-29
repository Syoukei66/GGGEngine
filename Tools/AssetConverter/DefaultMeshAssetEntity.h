#pragma once

#include <Core/MeshData.h>
#include "AssetEntity.h"

class DefaultMeshAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_DEFAULT_MESH)
    // =================================================================
    // Constructor / Destructor
    // =================================================================
public:
  DefaultMeshAssetEntity(AssetInfo* info, MeshData* data);
  ~DefaultMeshAssetEntity();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE const MeshData* GetData() const
  {
    return this->data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  MeshData* data_;

};
