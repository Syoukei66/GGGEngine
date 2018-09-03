#pragma once

#include "GameComponent.h"
#include "../Asset/Material.h"

class GameObjectRenderState;
class GameObject;

class Renderer : public GameComponent
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Renderer(GameObject* entity);
  virtual ~Renderer() {}

  // =================================================================
  // Method
  // =================================================================
public:
  void ReserveDraw(GameObjectRenderState* state);
  void UniqueMaterial();
  
  void Draw(GameObjectRenderState* state) const;

protected:
  virtual bool SetStreamSource() const = 0;
  virtual void SetProperties(rcMaterial* material) const = 0;
  virtual void DrawSubset(T_UINT8 submesh_index) const = 0;

private:
  void SetDefaultProperties(GameObjectRenderState* state, rcMaterial* material) const;

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

  inline void AddMaterial(rcMaterial& material)
  {
    this->materials_.emplace_back(&material);
  }
  inline void SetMaterial(rcMaterial& material)
  {
    if (this->materials_.size() == 0)
    {
      this->materials_.emplace_back(nullptr);
    }
    this->materials_[0] = &material;
  }
  inline void SetMaterial(T_UINT16 index, rcMaterial& material)
  {
    this->materials_[index] = &material;
  }
  inline rcMaterial* GetMaterial(T_UINT16 index = 0) const
  {
    return this->materials_[index];
  }
  inline T_UINT16 GetMaterialCount()
  {
    return (T_UINT16)this->materials_.size();
  }

  inline GameObject* GetEntity()
  {
    return this->entity_;
  }

  inline const GameObject* GetEntity() const
  {
    return this->entity_;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  GameObject* entity_;
  T_UINT8 layer_id_;
  std::vector<rcMaterial*> materials_;

};