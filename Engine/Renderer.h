#pragma once

#include "GameObjectRenderState.h"
#include "Material.h"

class Renderer
{
  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Draw(GameObjectRenderState* state) = 0;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline void AddMaterial(Material& material)
  {
    this->materials_.push_back(&material);
  }
  void SetMaterial(Material& material);
  inline void SetMaterial(T_UINT16 index, Material& material)
  {
    this->materials_[index] = &material;
  }
  inline Material& SetMaterial(T_UINT16 index = 0) const
  {
    return *this->materials_[index];
  }
  inline T_UINT16 GetMaterialCount()
  {
    return this->materials_.size();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::vector<Material*> materials_;

};