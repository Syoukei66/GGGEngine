#pragma once

#include "ResourceLoader.h"
#include "Mesh.h"

class MeshResource
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  MeshResource(const MeshData& data);
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
  inline Mesh& GetContents() const
  {
    NATIVE_ASSERT(this->mesh_, "メッシュがロードされていません");
    return *this->mesh_;
  }

private:
  const MeshData& data_;
  Mesh* mesh_;
};