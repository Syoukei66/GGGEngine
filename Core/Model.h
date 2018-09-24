#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Resource.h"

class rcModel : public Resource
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcModel(rcMesh* mesh, rcMaterial** materials);
  virtual ~rcModel();

  // =================================================================
  // Methods
  // =================================================================
public:


  // =================================================================
  // Getter / Setter
  // =================================================================
protected:
  inline rcMesh* GetMesh()
  {
    return this->mesh_;
  }

  inline const rcMesh* GetMesh() const
  {
    return this->mesh_;
  }

  inline T_UINT8 GetSubmeshCount() const
  {
    return this->mesh_->GetSubmeshCount();
  }

  inline rcMaterial* GetMaterial(T_UINT8 index)
  {
    return this->materials_[index];
  }

  inline const rcMaterial* GetMaterial(T_UINT8 index) const
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
  rcMesh* mesh_;
  rcMaterial** materials_;

};
