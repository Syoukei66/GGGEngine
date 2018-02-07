#pragma once

#include <vector>
#include "SubMesh.h"

class Mesh
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Mesh();
  Mesh(const MeshData& data);
  ~Mesh();

  // =================================================================
  // Method
  // =================================================================
public:
  void AddSubMesh(SubMesh* mesh);
  void DrawSubMesh(T_UINT16 index) const;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline T_UINT16 GetSubMeshCount() const
  {
    return (T_UINT16)this->sub_meshes_.size();
  }

  inline SubMesh* GetSubMesh(T_UINT16 index) const
  {
    return this->sub_meshes_[index];
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::vector<SubMesh*> sub_meshes_;
};