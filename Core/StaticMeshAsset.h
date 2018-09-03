#pragma once

#include "Asset.h"
#include "StaticMesh.h"

class StaticMeshAsset : public Asset<StaticMeshAsset, rcStaticMesh>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  StaticMeshAsset(const std::string& path)
    : Asset(path)
  {}

  // =================================================================
  // Methods
  // =================================================================
protected:
  rcStaticMesh* LoadProcess(const std::string& path) override
  {
    StaticMeshData* data = StaticMeshData::Deserealize(path);
    rcStaticMesh* ret = rcStaticMesh::Create(*data);
    delete data;
    return ret;
  }

};
