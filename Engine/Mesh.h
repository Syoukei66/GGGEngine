#pragma once

#include <vector>

#include "SubMesh.h"

class Mesh
{
public:
  static Mesh* CreateWithMeshData(const MeshData& data);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Mesh();
  ~Mesh();

  // =================================================================
  // Method
  // =================================================================
public:
  void AddSubset(SubMesh* mesh);
  void DrawSubset(T_UINT16 index) const;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline T_UINT16 GetSubMeshCount() const
  {
    return this->sub_meshes_.size();
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