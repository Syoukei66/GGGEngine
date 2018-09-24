#pragma once

#include "Asset.h"
#include "Mesh.h"

class MeshAsset : public Asset<MeshAsset, rcMesh>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  MeshAsset(const std::string& path)
    : Asset(path)
  {}

  // =================================================================
  // Methods
  // =================================================================
protected:
  rcMesh* LoadProcess(const std::string& path) override
  {
    MeshData* data = MeshData::Deserealize(path);
    rcMesh* ret = rcMesh::Create(data);
    delete data;
    return ret;
  }

};
