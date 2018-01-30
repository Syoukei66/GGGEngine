#pragma once

#include "GameObjectRenderState.h"
#include "GameComponent.h"
#include "Material.h"

class Renderer : public GameComponent
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Renderer();

  // =================================================================
  // Method
  // =================================================================
public:
  void Draw(GameObjectRenderState* state);
  void UniqueMaterial();

protected:
  virtual void EditProperty(T_UINT8 material_index, T_UINT8 pass_index, Material* material) = 0;
  virtual void DrawSubset(T_UINT8 material_index, T_UINT8 pass_index) = 0;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline void SetLayerId(T_UINT8 layer_id)
  {
    this->layer_id_ = layer_id;
  }
  inline T_UINT8 GetLayerId() const
  {
    return this->layer_id_;
  }

  inline void AddMaterial(Material& material)
  {
    this->materials_.push_back(&material);
  }
  void SetMaterial(Material& material);
  inline void SetMaterial(T_UINT16 index, Material& material)
  {
    this->materials_[index] = &material;
  }
  inline Material* GetMaterial(T_UINT16 index = 0) const
  {
    return this->materials_[index];
  }
  inline T_UINT16 GetMaterialCount()
  {
    return (T_UINT16)this->materials_.size();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT8 layer_id_;
  std::vector<Material*> materials_;

};