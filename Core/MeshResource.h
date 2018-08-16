#pragma once

#include "Mesh.h"
#include "MeshBuilder.h"

class MeshResource
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  MeshResource(const MeshBuilder* builder);
  ~MeshResource();

  // =================================================================
  // Methods
  // =================================================================
public:
  void Load();
  void Unload();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline rcCustomMesh& GetContents() const
  {
    NATIVE_ASSERT(this->mesh_, "メッシュがロードされていません");
    return *this->mesh_;
  }

private:
  const MeshBuilder* builder_;
  rcCustomMesh* mesh_;

};