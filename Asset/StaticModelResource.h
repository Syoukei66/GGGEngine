#pragma once

#include <vector>
#include "../Asset/StaticModelData.h"
#include "../Asset/StandardMaterial.h"
#include "StaticMesh.h"

class StaticModelResource
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static StaticModelResource* Create(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  StaticModelResource(StaticModelData* data);
  ~StaticModelResource();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const INativeVertexBuffer* GetVertexBuffer() const
  {
    return this->vertex_buffer_;
  }

  inline const INativeIndexBuffer* GetIndexBuffer(T_UINT8 index) const
  {
    return this->index_buffers_[index];
  }

  inline T_UINT8 GetSubmeshCount() const
  {
    return this->data_->submesh_count_;
  }

  inline const StaticMesh* GetMesh() const
  {
    return &this->mesh_;
  }

  inline const StandardMaterial* GetMaterial(T_UINT8 index) const
  {
    return this->materials_[index];
  }

  inline const StandardMaterial* GetMaterialWithSubmeshIndex(T_UINT8 index) const
  {
    return this->materials_[this->data_->submesh_material_indices_[index]];
  }

  inline T_UINT8 GetMaterialCount() const
  {
    return this->data_->material_count_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  StaticModelData* data_;
  INativeVertexBuffer* vertex_buffer_;
  std::vector<INativeIndexBuffer*> index_buffers_;
  StaticMesh mesh_;
  std::vector<StandardMaterial*> materials_;

};