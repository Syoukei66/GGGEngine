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
  DefaultMeshAssetEntity(AssetInfo* info, MeshData* data, T_UINT32 default_unique_id);
  ~DefaultMeshAssetEntity();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const MeshData* GetData() const
  {
    return this->data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  MeshData* data_;
  T_UINT32 default_unique_id_;

};
