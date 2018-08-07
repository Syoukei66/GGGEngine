#pragma once

#include <vector>
#include "../Asset/StaticModelData.h"
#include "StaticMesh.h"
#include "Material.h"

#include "GameObject3D.h"

class StaticModelResource
{
public:
  StaticModelResource(StaticModelData* data);
  ~StaticModelResource();

public:
  GameObject3D* CreateGameObject();

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

  inline const Material* GetMaterial(T_UINT8 index) const
  {
    return this->materials_[index];
  }

  inline const Material* GetMaterialWithSubmeshIndex(T_UINT8 index) const
  {
    return this->materials_[this->data_->submesh_material_indices_[index]];
  }

  inline T_UINT8 GetMaterialCount() const
  {
    return this->data_->material_count_;
  }

private:
  StaticModelData* data_;
  INativeVertexBuffer* vertex_buffer_;
  std::vector<INativeIndexBuffer*> index_buffers_;
  StaticMesh mesh_;
  std::vector<Material*> materials_;

};