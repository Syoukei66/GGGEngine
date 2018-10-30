#pragma once

#include <Entity/AssetEntity.h>

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
  inline const MeshData* GetData() const
  {
    return this->data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  MeshData* data_;

};
