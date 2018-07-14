#pragma once

#include "GameObject.h"
#include "GameComponent.h"
#include "Material.h"

class CommandBuffer;

class Renderer : public GameComponent
{
public:

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
  void UniqueMaterial();
  virtual void Submit(CommandBuffer* buf) const = 0;

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

  inline void SetIndexId(T_UINT8 index_id)
  {
    this->index_id_ = index_id;
  }
  inline T_UINT8 GetIndexId() const
  {
    return this->index_id_;
  }

  inline void AddMaterial(Material& material)
  {
    this->materials_.emplace_back(&material);
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
  inline T_UINT8 GetMaterialCount()
  {
    return (T_UINT8)this->materials_.size();
  }

  inline void SetBillboardingFlag(bool billboarding)
  {
    this->billbording_ = billboarding;
  }

  inline bool IsBillboard() const
  {
    return this->billbording_;
  }
  // =================================================================
  // Data Member
  // =================================================================
protected:
  //フィルタリングに使用
  T_UINT8 layer_id_;
  //ソートに使用
  T_UINT8 index_id_;

  std::vector<Material*> materials_;
  bool billbording_;

};