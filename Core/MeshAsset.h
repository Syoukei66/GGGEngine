#pragma once

#include "Asset.h"
#include "Mesh.h"

class MeshAsset : public BaseAsset<MeshAsset, rcMesh>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  MeshAsset(const std::string& path)
    : BaseAsset(path)
  {}

  // =================================================================
  // Methods
  // =================================================================
protected:
  rcMesh* LoadProcess(const std::string& path) override
  {
    MeshData* data = MeshData::Deserialize(path);
    rcMesh* ret = rcMesh::Create(data);
    delete data;
    return ret;
  }

};
