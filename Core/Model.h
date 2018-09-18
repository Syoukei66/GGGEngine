#pragma once

#include "Resource.h"

template <class Mesh_, class Material_>
class rcModel : public Resource
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcModel(Mesh_* mesh, Material_** materials)
    : mesh_(mesh)
    , materials_ (materials)
  {
    this->mesh_->Retain();
    T_UINT8 material_count = this->GetMaterialCount();
    for (T_UINT8 i = 0; i < material_count; ++i)
    {
      this->materials_[i]->Retain();
    }
  }

  virtual ~rcModel()
  {
    T_UINT8 material_count = this->GetMaterialCount();
    for (T_UINT8 i = 0; i < material_count; ++i)
    {
      this->materials_[i]->Release();
    }
    this->mesh_->Release();
  }

  // =================================================================
  // Methods
  // =================================================================
public:


  // =================================================================
  // Getter / Setter
  // =================================================================
protected:
  inline Mesh_* GetMesh()
  {
    return this->mesh_;
  }

  inline const Mesh_* GetMesh() const
  {
    return this->mesh_;
  }

  inline T_UINT8 GetSubmeshCount() const
  {
    return this->mesh_->GetSubmeshCount();
  }

  inline Material_* GetMaterial(T_UINT8 index)
  {
    return this->materials_[index];
  }

  inline const Material_* GetMaterial(T_UINT8 index) const
  {
    return this->materials_[index];
  }

  inline T_UINT8 GetMaterialCount() const
  {
    return this->mesh_->GetSubmeshCount();
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  Mesh_* mesh_;
  Material_** materials_;

};


