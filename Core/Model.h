#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Resource.h"
#include "ModelData.h"

class rcModel : public Resource
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueResource<rcModel> CreateFromFile(const char* path);
  static UniqueResource<rcModel> Create(const ModelData* data);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcModel(const ModelData* data);
  virtual ~rcModel();

  // =================================================================
  // Methods
  // =================================================================
public:


  // =================================================================
  // Getter / Setter
  // =================================================================
public:
  inline virtual const char* GetResourceName() override
  {
    return "Model";
  }

  inline SharedRef<rcMesh> GetMesh()
  {
    return this->mesh_;
  }

  inline SharedRef<const rcMesh> GetMesh() const
  {
    return this->mesh_;
  }

  inline T_UINT8 GetSubmeshCount() const
  {
    return this->mesh_->GetSubmeshCount();
  }

  inline SharedRef<rcMaterial> GetMaterial(T_UINT8 index)
  {
    return this->materials_[index];
  }

  inline SharedRef<const rcMaterial> GetMaterial(T_UINT8 index) const
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
  SharedRef<rcMesh> mesh_;
  SharedRef<rcMaterial>* materials_;

};
