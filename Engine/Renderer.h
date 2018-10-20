#pragma once

#include "GameComponent.h"
#include "../Core/Material.h"

class GameObjectRenderState;
class GameObject;

class Renderer : public GameComponent
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Renderer(GameObject* entity);
  virtual ~Renderer();

  // =================================================================
  // Method
  // =================================================================
public:
  void ReserveDraw(GameObjectRenderState* state);

  void Draw(GameObjectRenderState* state) const;

protected:
  virtual bool SetStreamSource() const = 0;
  virtual void SetProperties(const SharedRef<rcShader>& shader) const = 0;
  virtual void DrawSubset(T_UINT8 submesh_index) const = 0;

private:
  void SetDefaultProperties(GameObjectRenderState* state, const SharedRef<rcShader>& shader) const;

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

  void SetMaterial(const SharedRef<rcMaterial>& material, T_UINT16 index = 0);
  inline void SetSharedMaterial(const SharedRef<const rcMaterial>& material, T_UINT16 index = 0)
  {
    this->shared_materials_[index] = material;
  }

  SharedRef<rcMaterial> GetMaterial(T_UINT16 index = 0);
  SharedRef<const rcMaterial> GetMaterial(T_UINT16 index = 0) const;
  inline SharedRef<const rcMaterial> GetSharedMaterial(T_UINT16 index = 0) const
  {
    return this->shared_materials_.at(index);
  }

  inline bool HasMaterial() const
  {
    return this->shared_materials_.size() > 0 || this->materials_.size() > 0;
  }

  inline T_UINT8 GetMaterialCount() const
  {
    return (T_UINT8)this->shared_materials_.size();
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
  std::unordered_map<T_UINT32, SharedRef<const rcMaterial>> shared_materials_;
  std::unordered_map<T_UINT32, SharedRef<rcMaterial>> materials_;

};